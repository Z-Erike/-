#pragma once

#include<fstream>
using namespace std;

#define NUM1 128
#define NUM2 1024
#define Width 30        //每格宽度
#define HIGH 20         //每格长度

class Medicine
{public:
	Medicine(){}     //无参构造法  
	Medicine(char *Iname, char *Iintroduction, char *Iusage, char *Iclash, char *Ipicture);
	~Medicine() {}  //析构函数
public:
	void input(ifstream &in);
	Medicine* get_next();
	void output();
	void Load_image();
	void Write_Data();						//向文件中填写
	char *get_name();						//获得姓名
	char *get_usage();
protected:
	friend class Message;
	char name[NUM1];           //药名
	char introduction[NUM2];  //简单介绍
	char usage[NUM1];        //使用方法(可治疗的病症）
	char clash[NUM1];         //相冲的药物
	char picture[NUM1];       //图片名称
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
	Medicine *Search(const char *x);				 //查找
	void printf();					  //显示所有药材
	Medicine treat();                 //根据病症搜索药材kmp算法
	Medicine stick();                 //置顶
	Medicine output();                //输出
	Medicine *find(int o);			  //定位到单个节点(显示中用到）
	int show_num();                   //返回一共多少种药材
	int get_max();
	int Delete(char s[]);
	int revise(int n, char s[]);
	Medicine *inquiry(char s[]);
	
};

