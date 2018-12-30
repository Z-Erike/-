#include"user.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include<string.h>
#include<graphics.h>
#include <iomanip>
#include<windows.h>
using namespace std;




int user::regisiter()
{//注册程序
	InputBox(ID, 128, _T("请输入账号:"), false);
	

	string temp;
	int flag = 0;
	int i = 0;

	ifstream fin("User.txt", ios::in);//在这个路径下读入文件

	ofstream fout("User.txt", ios::app);//在同一个路径下，如果注册成功则写入文件

	while (std::getline(fin, temp))//每次读一行的数据进入temp中。

	{

		i++;

		if (i % 2 == 0) continue;//访问的是密码这一行，跳出。

		if (!strcmp(ID, temp.c_str())) flag = 1;//flag=1说明用户名已经被注册了

	}

	fin.close();

	if (flag) {
		::MessageBox(NULL, "用户已注册", "错误", MB_SETFOREGROUND);
		return 0;//之前有重复的账户名

	}

	else {//没注册
		InputBox(password, 20, _T("请输入密码:"), false);
		fout << ID << endl;//向文件写入注册者的用户名，然后换一行

		fout << password << endl;//写入密码，换行

		fout.close();
		::MessageBox(NULL, "注册成功", "恭喜", MB_SETFOREGROUND);
		

	}

}

 int user::login()
 {



	 InputBox(ID, 128, _T("登陆请输入账号:"), false);
	 InputBox(password, 20, _T("登陆请输入密码:"), false);

	string temp1;

	string temp2;

	int existname = 0;

	int match = 0;

	int i = 0;

	ifstream fin("User.txt", ios::in);

	while (std::getline(fin, temp1))

	{
		std::getline(fin, temp2);//一次读进去两行，分别是用户名和密码

		if (!strcmp(ID, temp1.c_str())) {//有这个用户名了，接下来看看密码是不是相符的

			existname = 1;

			if (!strcmp(password, temp2.c_str())) {//相符

				match = 1;

				break;

			}

		}

	}

	fin.close();

	if (!existname) {
		::MessageBox(NULL, "未查询到该用户", "错误", MB_SETFOREGROUND);
		return 2;//没有账户名

	}

	else {

		if (match) return 1;
		::MessageBox(NULL, "密码错误", "错误", MB_SETFOREGROUND);
		 return 3;//用户名和密码不匹配

	}

}
 int user::begin()
 {
	 char s1[5];
	 int a,temp1=0,temp2=0;
	 
	 InputBox(s1, 5, _T("1.注册2.登陆3.退出"));
	 sscanf_s(s1, "%d", &a);
	 switch (a)
	 {
		 case 1:
		 {
			 regisiter();
			 break;
		 }
		 case 2:
		 {
			temp2=login();
			break;
		 }
		 case 3:
		 {
			 exit(-1);
			 break;
		 }

	 }
	 if (temp2 == 1&& authority==0)
		 return 1;//登陆成功(普通用户)
	 if (temp2 == 1 && authority == 1)
		 return 1;//登陆成功(管理员)
	 else begin();
 }

	 
 

