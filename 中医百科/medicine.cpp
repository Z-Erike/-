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
void Medicine::output()
{
	settextstyle(20, 0, _T("微软雅黑"));
	RECT r1 = { 2 * Width,2 * HIGH,9 * Width,5 * HIGH };//输出姓名
	RECT r2 = {2*Width,7*HIGH,19*Width,21*HIGH};
	RECT r3 = { 2 * Width,22*HIGH,19 * Width,25*HIGH };
	RECT r4 = { 2 * Width ,26*HIGH,19 * Width,28*HIGH };

	drawtext(name, &r1, NULL);
	drawtext(introduction, &r2, DT_WORDBREAK);
	drawtext(usage, &r3, DT_WORDBREAK);
	drawtext(clash, &r4, DT_WORDBREAK);

}
char *Medicine::get_usage()
{
	return usage;	
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
void Message::Delete(char s[])
{
	ofstream out("data2.txt");
	ifstream in("data.txt");
	char temp[1000];
	while (!in.eof())
	{
		in.getline(temp, sizeof(temp));
		out << temp << endl;
		last->input(in);
		if (last->name[0] == '\0')
			break;
		last->next = new Medicine;
		last = last->next;
	}
	if (strcmp(s, last->name))
	{

	}

	in.close();
}
