#pragma once

#include<fstream>
using namespace std;

#define NUM1 128
#define NUM2 1024
#define Width 30        //ÿ����
#define HIGH 20         //ÿ�񳤶�

class Medicine
{public:
	Medicine(){}     //�޲ι��취  
	Medicine(char *Iname, char *Iintroduction, char *Iusage, char *Iclash, char *Ipicture);
	~Medicine() {}  //��������
public:
	void input(ifstream &in);
	Medicine* get_next();
	void output();
	void Load_image();
	void Write_Data();						//���ļ�����д
	char *get_name();						//�������
	char *get_usage();
protected:
	friend class Message;
	char name[NUM1];           //ҩ��
	char introduction[NUM2];  //�򵥽���
	char usage[NUM1];        //ʹ�÷���(�����ƵĲ�֢��
	char clash[NUM1];         //����ҩ��
	char picture[NUM1];       //ͼƬ����
	Medicine *next;
};



class Message
{
private:
	Medicine *first;
	Medicine *last;
	ifstream in;
	ofstream out;
	static int maxnum;
public:
	Message();
	Medicine *Search(const char *x);				 //����
	void printf();					  //��ʾ����ҩ��
	Medicine treat();                 //���ݲ�֢����ҩ��kmp�㷨
	Medicine stick();                 //�ö�
	Medicine output();                //���
	Medicine *find(int o);			  //��λ�������ڵ�(��ʾ���õ���
	int show_num();                   //����һ��������ҩ��
	int get_max();
	int Delete(char s[]);
	int revise(int n, char s[]);
	Medicine *inquiry(char s[]);
	
};

