#include "medicine.h"

#include <string.h>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <stdlib.h>
#include<conio.h>
#include <graphics.h>

using namespace std;

int Message::maxnum;

extern IMAGE medicine_bg;

Medicine::Medicine(char *Iname, char *Iintroduction, char *Iusage, char *Iclash, char *Ipicture)
{
	strncpy_s(name,Iname, NUM1);
	strncpy_s(introduction, Iintroduction, NUM2);
	strncpy_s(usage, Iusage, NUM1);
	strncpy_s(clash, Iclash, NUM1);
	strncpy_s(picture, Ipicture, NUM1);

}

void Medicine::input(ifstream &in)
{
	in.getline(name, NUM1);
	in.getline(introduction, NUM2);
	in.getline(usage, NUM1);
	in.getline(clash, NUM1);
	in.getline(picture, NUM1);

}
void Medicine::Write_Data()
{
	ofstream out;
	out.open("data.txt",ios::app);
	try{										//该位置很可能会出现问题
		out << name << endl;
		out << introduction << endl;
		out << usage << endl;
		out << clash << endl;
		out << picture << endl;
	}
	catch (...) {//catch(…)能够捕获多种数据类型的异常对象
		throw "file error occurred";
		out.close();
	}
	out.close();

}
char *Medicine::get_name()
{
	return name;
}
void Medicine::Load_image()
{
	cout << picture;
	loadimage(&medicine_bg, picture);
}
char *Medicine::get_usage()
{
	return usage;	
}
void Medicine::output()
{
	settextstyle(20, 0, _T("黑体"));
	RECT r1 = {3*Width,3*HIGH,9*Width,5*HIGH};
	RECT r2 = {3*Width,7*HIGH,19*Width,21*HIGH};
	RECT r3 = { 3 * Width ,22*HIGH,19 * Width ,25*HIGH};
	RECT r4 = { 3 * Width ,26*HIGH,19 * Width,28*HIGH };
	drawtext(name, &r1, DT_WORDBREAK);
	drawtext(introduction, &r2, DT_WORDBREAK);
	drawtext(usage, &r3, DT_WORDBREAK);
	drawtext(clash, &r4, DT_WORDBREAK);



}


Message::Message()
{
	maxnum = 0;
	/*初始化，头尾结点*/
	first = new Medicine;
	first->next = new Medicine;
	last = first->next;
	ifstream in("data.txt"); 
	
	if (in.eof())
	{
		cout << "file is empty" << endl;
	}

	while (!in.eof())
	{
		maxnum++;
		last->input(in);
		if (last->name[0] == '\0')
			break;  
		last->next = new Medicine;
		last = last->next;
	}
	maxnum--;
	in.close();
}
Medicine *Message::find(int m)
{
	int i;
	Medicine *ptr = first;
	for (i = 0; i < m ; i++)
	{
		ptr = ptr->next;
	}
	return ptr;                      //返回找到的数据

}
int Message::get_max()
{
	return maxnum;
}
int Message::Delete(char s[])
{
	int flag=0;
	ofstream out("data2.txt",ios::trunc);
	ifstream in("data.txt");
	Medicine *ptr=first;
	char temp[1000];
	for (int i = 0; i < maxnum; i++)
	{
	
		if (strcmp(ptr->name, s) == 0)
		{
			flag = 1;
			break;
		}
		ptr = ptr->next;
	}
	if (flag==0)
	{
		return 0;
	}
	while (!in.eof())
	{
		
		in.getline(temp, sizeof(temp));
		if (strcmp(s, temp)==0)
		{
			in.getline(temp, sizeof(temp));
			in.getline(temp, sizeof(temp));
			in.getline(temp, sizeof(temp));
			in.getline(temp, sizeof(temp));
			continue;
		}
		out << temp << endl;
	
	}
	out.close();
	in.close();
	fstream in1("data2.txt");
	ofstream out1("data.txt",ios::trunc|ios::out);
	while (!in1.eof())
	{
		in1.getline(temp, sizeof(temp));
		out1 << temp << endl;
	}
	out1.close();
	in1.close();
	return flag;


}
int Message::revise(int n,char s[])
{
	ofstream out("data2.txt", ios::trunc);
	ifstream in("data.txt");
	Medicine *ptr = first;
	int flag = 0;
	char temp[1000],temp1[1000];//temp是用来将data的数据导入data2中的，temp1是用来将记录用户修改的
	for (int i = 0; i < maxnum; i++)
	{
		
		if (strcmp(ptr->name, s) == 0)
		{
			flag = 1;
			break;
		}
		ptr = ptr->next;
	}
	if (flag == 0)
	{
		return 0;
	}
	if (n == 1)	   InputBox(temp1, sizeof(temp1), _T("请输入药材名"));
	if (n == 2)		InputBox(temp1, sizeof(temp1), _T("请输入简介"));
	if (n ==3)      InputBox(temp1, sizeof(temp1), _T("请输入用途"));
	if (n == 4)    InputBox(temp1, sizeof(temp1), _T("请输入禁忌"));
	while (!in.eof())
	{

		in.getline(temp, sizeof(temp));
		
		if (strcmp(s, temp) == 0)
		{
			if (n == 1)
			{
				out << temp1 << endl;
			}
			if (n == 2)
			{
				out << temp<< endl;
				in.getline(temp, sizeof(temp));
				out << temp1 << endl;
			}
			if (n == 3)
			{
				out << temp << endl;
				in.getline(temp, sizeof(temp));
				out << temp << endl;
				in.getline(temp, sizeof(temp));
				out << temp1 << endl;
			}
			if (n == 4)
			{
				out << temp << endl;
				in.getline(temp, sizeof(temp));
				out << temp << endl;
				in.getline(temp, sizeof(temp));
				out << temp << endl;
				in.getline(temp, sizeof(temp));
				out << temp1 << endl;
			}
			continue;
		}
		
		out << temp << endl;

	}

	out.close();
	in.close();
	fstream in1("data2.txt");
	ofstream out1("data.txt", ios::trunc | ios::out);
	while (!in1.eof())
	{
		in1.getline(temp, sizeof(temp));
		out1 << temp << endl;
	}
	out1.close();
	in1.close();
	return flag;


	
}
Medicine *Message::inquiry(char s[])
{
	
	Medicine *ptr=first;

	for (int i = 0; i < maxnum; i++)
	{
		
		if (strcmp(ptr->name,s)==0)
		{
			
			return ptr;
		}
		ptr = ptr->next;
	}
	
	return NULL;
}

