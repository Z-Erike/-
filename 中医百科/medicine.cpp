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
	out.open("book.dat", ios::binary | ios::app);
	try{										//该位置很可能会出现问题
		out.write(name, NUM1);//写入图书的信息
		out.write(introduction, NUM2);
		out.write(usage, NUM1);
		out.write(clash, NUM1);
		out.write(picture, NUM1);
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
	
		if (ptr->name == s)
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
		if (strcmp(s, temp))
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
	int flag = 0;
	Medicine *ptr=first;
	char temp[1000];
	for (int i = 0; i < maxnum; i++)
	{
		
		if (ptr->name == s)
		{
			flag = 1;
			break;
		}
		ptr = ptr->next;
	}
	if (n = 1)
	{
		InputBox(temp, 1000, _T("请输入药材名"));
		strcpy_s(ptr->name, temp);
		flag = 1;
	}
	if (n = 2)
	{
		InputBox(temp, 1000, _T("请输入简介"));
		strcpy_s(ptr->introduction, temp);
		flag = 1;
	}
	if (n = 3)
	{
		InputBox(temp, 1000, _T("请输入用途"));
		strcpy_s(ptr->usage, temp);
		flag = 1;
	}
	if (n = 4)
	{
		InputBox(temp, 1000, _T("请输入禁忌"));
		strcpy_s(ptr->clash, temp);
		flag = 1;
	}
	return flag;

}
Medicine *Message::inquiry(char s[])
{
	int flag = 0;
	Medicine *ptr=first;
	for (int i = 0; i < maxnum; i++)
	{
		
		if (ptr->name == s)
		{
			flag = 1;
			break;
		}
		ptr = ptr->next;
	}
	return ptr;
}

