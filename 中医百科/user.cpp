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
{//ע�����
	InputBox(ID, 128, _T("�������˺�:"), false);
	

	string temp;
	int flag = 0;
	int i = 0;

	ifstream fin("User.txt", ios::in);//�����·���¶����ļ�

	ofstream fout("User.txt", ios::app);//��ͬһ��·���£����ע��ɹ���д���ļ�

	while (std::getline(fin, temp))//ÿ�ζ�һ�е����ݽ���temp�С�

	{

		i++;

		if (i % 2 == 0) continue;//���ʵ���������һ�У�������

		if (!strcmp(ID, temp.c_str())) flag = 1;//flag=1˵���û����Ѿ���ע����

	}

	fin.close();

	if (flag) {
		::MessageBox(NULL, "�û���ע��", "����", MB_SETFOREGROUND);
		return 0;//֮ǰ���ظ����˻���

	}

	else {//ûע��
		InputBox(password, 20, _T("����������:"), false);
		fout << ID << endl;//���ļ�д��ע���ߵ��û�����Ȼ��һ��

		fout << password << endl;//д�����룬����

		fout.close();
		::MessageBox(NULL, "ע��ɹ�", "��ϲ", MB_SETFOREGROUND);
		

	}

}

 int user::login()
 {



	 InputBox(ID, 128, _T("��½�������˺�:"), false);
	 InputBox(password, 20, _T("��½����������:"), false);

	string temp1;

	string temp2;

	int existname = 0;

	int match = 0;

	int i = 0;

	ifstream fin("User.txt", ios::in);

	while (std::getline(fin, temp1))

	{
		std::getline(fin, temp2);//һ�ζ���ȥ���У��ֱ����û���������

		if (!strcmp(ID, temp1.c_str())) {//������û����ˣ����������������ǲ��������

			existname = 1;

			if (!strcmp(password, temp2.c_str())) {//���

				match = 1;

				break;

			}

		}

	}

	fin.close();

	if (!existname) {
		::MessageBox(NULL, "δ��ѯ�����û�", "����", MB_SETFOREGROUND);
		return 2;//û���˻���

	}

	else {

		if (match) return 1;
		::MessageBox(NULL, "�������", "����", MB_SETFOREGROUND);
		 return 3;//�û��������벻ƥ��

	}

}
 int user::begin()
 {
	 char s1[5];
	 int a,temp1=0,temp2=0;
	 
	 InputBox(s1, 5, _T("1.ע��2.��½3.�˳�"));
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
		 return 1;//��½�ɹ�(��ͨ�û�)
	 if (temp2 == 1 && authority == 1)
		 return 1;//��½�ɹ�(����Ա)
	 else begin();
 }

	 
 

