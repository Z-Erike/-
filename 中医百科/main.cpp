
#include<iostream>
#include<string>
#include<graphics.h>
#include<vector>
#include<conio.h>
#include<Windows.h>

#include"medicine.h"
#include"user.h"

using namespace std;

#define Width 30        //每格宽度
#define High 20         //每格长度
#define NUM 32          //格数
#define NUM1 128        //数组长度
#define NUM2 1024
int menuflag = 0;       //菜单选择flag
int PAGE = 1;
Message mess;


IMAGE bg1,bg2,bg3,bg4;               //背景图片预定义(带0的为点击后的效果图)
IMAGE medicine_bg;					 //装饰图片与安装的按钮
IMAGE bg_goon, bg_back, bg_goon_0, bg_back_0,bg_black;
IMAGE bg_last, bg_next,bg_last_0,bg_next_0,bg_last_1,bg_next_1;
IMAGE bg1_1, bg1_2, bg1_3, bg1_4,bg1_1_0, bg1_2_0, bg1_3_0, bg1_4_0;
IMAGE bg2_1, bg2_1_0;
IMAGE bg_a, bg_b, bg_c, bg_d, bg_a_0, bg_b_0, bg_c_0, bg_d_0;


void HideCursor();							//隐藏光标函数
void ClearScreen();							//清除debug信息
void ClearScreen1();                        //清除屏幕信息
void Menu();								//主菜单函数
void Menu(int a);							//主菜单（管理员）
void Init();								//初始化界面
void Init(int a);							//初始化界面（管理员）
void WaitView(int iCurPage);				//浏览数据时等待用户操作
void WaitUser();							//等待用户操作
void Cure();								//根据病症搜索药材
int Show_All(int page);						//全部显示
void Show_Detail(Medicine);					//显示细节
void Input();								//向文件输入
bool kmp_search(string text, string m, int &pos);//kmp算法查找病症
const vector<int> * kmp_next(string &m);	//寻找下一个
void Delete();								//删除
void revise();								//修改
void inquiry();

int main()									//主函数
{
	int flag;
	user u;
	flag=u.begin();
	initgraph(Width*NUM, High*NUM);
	if (flag == 1)//正常用户
	{
		while (1)
		{
			Init();
		}
	}

	if (flag == 2)//管理员
	{
		menuflag = 4;
		while (1)
		{
			Init(1);
		}
	}
	closegraph();
	return 0;
}
void WaitUser()
{
	MOUSEMSG m;
	putimage(23 * Width, 27 * High, &bg_back);
	FlushBatchDraw();
	while (1)
	{
		while (MouseHit())                       //当鼠标点击的时候根据鼠标坐标进行判定
		{
			m = GetMouseMsg();
			if (((23 * Width <= m.x) && (m.x <= 23 * Width + 150)) && (m.uMsg == WM_LBUTTONDOWN))
			{
				if ((27 * High <= m.y) && (m.y <= 30 * High))
					putimage(23 * Width, 27 * High, &bg_back_0);
				Sleep(100);
				menuflag = 1;
				FlushMouseMsgBuffer();
				return;
			}
		}
	}
}
void WaitUser(int a)
{
	MOUSEMSG m;
	putimage(23 * Width, 27 * High, &bg_back);
	FlushBatchDraw();
	while (1)
	{
		while (MouseHit())                       //当鼠标点击的时候根据鼠标坐标进行判定
		{
			m = GetMouseMsg();
			if (((23 * Width <= m.x) && (m.x <= 23 * Width + 150)) && (m.uMsg == WM_LBUTTONDOWN))
			{
				if ((27 * High <= m.y) && (m.y <= 30 * High))
					putimage(23 * Width, 27 * High, &bg_back_0);
				Sleep(100);
				Init();
				menuflag = 4;
			}
		}
	}
}
void Cure()
{
	
	char s1[50],s2[100],temp[100];
	char dou[10] = {","};
	int i,pot=0,flag=0,x=100,y=350;
	putimage(0, 0, &bg3);
	
	settextstyle(40, 0, _T("微软雅黑"));
	outtextxy(50, 100, _T("请输入病症"));
	FlushBatchDraw();
	InputBox(s1, 25, _T("请输入病症"),false);
	settextcolor(BLACK);
	Medicine *ptr;
	for (i = 1; i < mess.get_max();i++)
	{
		pot = 0;
		ptr=mess.find(i);

		if (kmp_search(ptr->get_usage(),s1,pot))
		{
			flag = 1;
			outtextxy(x += 100, y, ptr->get_name());
			
			
		}
	}
	if (flag==1)
	{
		settextcolor(RED);
		outtextxy(50, 300, _T("可服下列药材:"));
		
	}
	else outtextxy(50, 300, _T("未找到符合病症的药材"));

	MOUSEMSG m;
	putimage(23 * Width, 27 * High, &bg_back);
	FlushBatchDraw();
	while (1)
	{
		while (MouseHit())                       //当鼠标点击的时候根据鼠标坐标进行判定
		{
			m = GetMouseMsg();
			if (((23 * Width <= m.x) && (m.x <= 23 * Width + 150)) && (m.uMsg == WM_LBUTTONDOWN))
			{
				if ((27 * High <= m.y) && (m.y <= 30 * High))
					putimage(23 * Width, 27 * High, &bg_back_0);
				Sleep(100);
				menuflag = 0;
				return;
			}
		}
	}

}
void HideCursor()							//隐藏光标函数
{
	CONSOLE_CURSOR_INFO cursor_info = { 1,0 };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}
void ClearScreen()							//清除debug信息
{
	system("cls");
}
void ClearScreen1()							//清除画布信息
{
	BeginBatchDraw();
	putimage(0, 0, &bg1);
	setbkmode(TRANSPARENT);
	
}

void Init()
{
	HWND hwnd = GetHWnd();//获取窗口句柄
	SetWindowText(hwnd, _T("中医药百科"));
	loadimage(&bg1, _T("img\\bg1.jpg"));   //读取图片信息
	loadimage(&bg2, _T("img\\bg2.jpg"));
	loadimage(&bg3, _T("img\\bg3.jpg"));
	loadimage(&bg4, _T("img\\bg4.jpg"));
	loadimage(&bg1_1, _T("img\\bg1_1.jpg"));
	loadimage(&bg1_2, _T("img\\bg1_2.jpg"));
	loadimage(&bg1_3, _T("img\\bg1_3.jpg"));
	loadimage(&bg1_4, _T("img\\bg1_4.jpg"));
	loadimage(&bg_back, _T("img\\back.jpg"));
	loadimage(&bg_goon, _T("img\\goon.jpg"));
	loadimage(&bg_last, _T("img\\last.jpg"));
	loadimage(&bg_next, _T("img\\next.jpg"));
	loadimage(&bg_back_0, _T("img\\back_0.jpg"));
	loadimage(&bg_goon_0, _T("img\\goon_0.jpg"));
	loadimage(&bg_last_1, _T("img\\last_1.jpg"));
	loadimage(&bg_next_1, _T("img\\next_1.jpg"));
	loadimage(&bg_last_0, _T("img\\last_0.jpg"));
	loadimage(&bg_next_0, _T("img\\next_0.jpg"));
	loadimage(&bg1_1_0, _T("img\\bg1_1_0.jpg"));
	loadimage(&bg1_2_0, _T("img\\bg1_2_0.jpg"));
	loadimage(&bg1_3_0, _T("img\\bg1_3_0.jpg"));
	loadimage(&bg1_4_0, _T("img\\bg1_4_0.jpg"));
	loadimage(&bg2_1, _T("img\\bg2_1.jpg"));
	loadimage(&bg2_1_0, _T("img\\bg2_1_0.jpg"));
	loadimage(&bg_black, _T("img\\bg_black.jpg"));
	loadimage(&bg_d_0, _T("img\\bg_d_0.jpg"));
	loadimage(&bg_d, _T("img\\bg_d.jpg"));

	while (menuflag == 0)
		Menu();			//初始化菜单界面
	while (menuflag == 1)
		Show_All(PAGE);		//	显示页面
	while (menuflag == 2)
		Cure();			//寻医问病界面
	while (menuflag == 6)
		inquiry();	//查询
	while (menuflag == 3)
		exit(-1);		//退出
}
void Init(int a)
{
	
	//背景音乐（暂未启用）
	//mciSendString("open .\\BOOK_music.mp3 alias bkmusic", NULL, 0, NULL);
	//mciSendString("play bkmusic repeat", NULL, 0, NULL);
	HWND hwnd = GetHWnd();//获取窗口句柄
	SetWindowText(hwnd, _T("中医药百科"));
	loadimage(&bg1, _T("img\\bg1.jpg"));   //读取图片信息
	loadimage(&bg2, _T("img\\bg2.jpg"));
	loadimage(&bg3, _T("img\\bg3.jpg"));
	loadimage(&bg4, _T("img\\bg4.jpg"));
	loadimage(&bg1_1, _T("img\\bg1_1.jpg"));
	loadimage(&bg1_2, _T("img\\bg1_2.jpg"));
	loadimage(&bg1_3, _T("img\\bg1_3.jpg"));
	loadimage(&bg1_4, _T("img\\bg1_4.jpg"));
	loadimage(&bg_back, _T("img\\back.jpg"));
	loadimage(&bg_goon, _T("img\\goon.jpg"));
	loadimage(&bg_last, _T("img\\last.jpg"));
	loadimage(&bg_next, _T("img\\next.jpg"));
	loadimage(&bg_back_0, _T("img\\back_0.jpg"));
	loadimage(&bg_goon_0, _T("img\\goon_0.jpg"));
	loadimage(&bg_last_0, _T("img\\last_0.jpg"));
	loadimage(&bg_next_0, _T("img\\next_0.jpg"));
	loadimage(&bg1_1_0, _T("img\\bg1_1_0.jpg"));
	loadimage(&bg1_2_0, _T("img\\bg1_2_0.jpg"));
	loadimage(&bg1_3_0, _T("img\\bg1_3_0.jpg"));
	loadimage(&bg1_4_0, _T("img\\bg1_4_0.jpg"));
	loadimage(&bg_a, _T("img\\bg_a.jpg"));
	loadimage(&bg_b, _T("img\\bg_b.jpg"));
	loadimage(&bg_c, _T("img\\bg_c.jpg"));
	loadimage(&bg_d, _T("img\\bg_d.jpg"));
	loadimage(&bg_a_0, _T("img\\bg_a_0.jpg"));
	loadimage(&bg_b_0, _T("img\\bg_b_0.jpg"));
	loadimage(&bg_c_0, _T("img\\bg_c_0.jpg"));
	loadimage(&bg_d_0, _T("img\\bg_d_0.jpg"));


	
	
	while (menuflag ==4)
		Menu(1);			//初始化菜单界面(管理员版)
	while (menuflag == 5)
		Delete();			//	删除
	while (menuflag == 7)
		revise();	//	修改页面
	while (menuflag == 8)
		Input();		//	修改页面
	while (menuflag == 3)
		exit(-1);		//退出
	
	
}
void Menu(int a)
{
	BeginBatchDraw();
	setbkmode(TRANSPARENT);                  //设定图片模式为衬与文字下方
	putimage(0, 0, &bg1);
	settextstyle(40, 0, _T("黑体"));
	int Main_x = 500;                       //更改此处改变所有主界面文字横坐标
	
	putimage(Main_x, 200, &bg_a);
	putimage(Main_x, 300, &bg_b);
	putimage(Main_x, 400, &bg_c);
	putimage(Main_x, 500, &bg1_4);

	FlushBatchDraw();
	Sleep(100);

	MOUSEMSG m;//鼠标结构体

	while (MouseHit())                       //当鼠标点击的时候根据鼠标坐标进行判定
	{
		m = GetMouseMsg();
		if (((Main_x <= m.x) && (m.x <= Main_x + 150)) && (m.uMsg == WM_LBUTTONDOWN))
		{
			if ((200 <= m.y) && (m.y <= 260))
			{
				putimage(Main_x, 200, &bg_a_0);
				
				FlushBatchDraw();
				Sleep(100);
				Delete();				//删除
				menuflag = 5;
				return;
			}
			if ((300 <= m.y) && (m.y <= 360))
			{
				putimage(Main_x, 300,& bg_b_0);
				FlushBatchDraw();
				Sleep(100);
				revise();	
				menuflag = 7;
			}
			if ((400 <= m.y) && (m.y <= 460))
			{
				putimage(Main_x, 400,&bg_c_0);
				FlushBatchDraw();
				Sleep(100);
				Input();
				menuflag = 8;
			}
			if ((500 <= m.y) && (m.y <= 560))
			{
				putimage(Main_x, 500, &bg1_4_0);
				FlushBatchDraw();
				Sleep(100);
				exit(-1);
				menuflag = 3;
			}
			

		}
	}
}
void Menu()									//主菜单
{
	BeginBatchDraw();
	setbkmode(TRANSPARENT);                  //设定图片模式为衬与文字下方
	putimage(0, 0, &bg1);
	settextcolor(RED);
	settextstyle(40, 0, _T("黑体"));
	int Main_x = 500;                       //更改此处改变所有主界面文字横坐标
	putimage(Main_x, 200, &bg1_1);
	putimage(Main_x, 300, &bg1_2);
	putimage(Main_x, 400, &bg_d);
	putimage(Main_x, 500, &bg1_4);
	FlushBatchDraw();
	Sleep(10);

	MOUSEMSG m;//鼠标结构体
	
		while (MouseHit())                       //当鼠标点击的时候根据鼠标坐标进行判定
		{
			m = GetMouseMsg();
			if (((Main_x <= m.x) && (m.x <= Main_x + 150)) && (m.uMsg == WM_LBUTTONDOWN))
			{
				if ((200 <= m.y) && (m.y <= 260))
				{
					putimage(Main_x, 200, &bg1_1_0);
					FlushBatchDraw();
					Sleep(100);
					Show_All(1);				//定位到第一页
					menuflag = 1;
					return;
				}
				if ((300 <= m.y) && (m.y <= 360))
				{
					putimage(Main_x, 300, &bg1_2_0);
					FlushBatchDraw();
					Sleep(100);
					
					menuflag = 2;
					return;
				}
				if ((400 <= m.y) && (m.y <= 460))
				{
					putimage(Main_x, 400, &bg_d_0);
					FlushBatchDraw();
					inquiry();
					
					menuflag = 6;
				}
				else if ((500 <= m.y) && (m.y <= 560))
				{
					BeginBatchDraw();
					putimage(Main_x, 500, &bg1_4_0);
					FlushBatchDraw();
					Sleep(100);
					exit(-1);
					menuflag = 3;
				}
				
			}
		}
	
}
int Show_All(int page)              //严重问题（第一个是空的）
{
	int x[3] = { 2,9,17 }, y[3] = { 10,20,30 };  //每个选项在的格子
	int  i, max_page, last_page, sum = 0;
	Medicine med[9];
	max_page = mess.get_max() / 9;				//最大页数
	last_page = mess.get_max() % 9;				//最后一页剩下的数据数
	ClearScreen1();								//清除图画
	BeginBatchDraw();							//开始批量绘图
	putimage(Width*NUM, High*NUM, &bg2);
	settextstyle(40, 0, _T("微软雅黑"));
	settextcolor(BLACK);
	outtextxy(480, 20, _T("全部药材"));			//菜单界面文字输出
	settextstyle(30, 0, _T("微软雅黑"));
	if (page == 1)
		putimage(25 * Width, 22 * High, &bg_last_1);
	else putimage(25 * Width, 22 * High, &bg_last);
	if (page == max_page)
		putimage(25 * Width, 26 * High, &bg_next_1);
	else putimage(25 * Width, 26 * High, &bg_next);
	putimage(25 * Width, 30 * High, &bg_back);

	for (i = 0; i <9; i++)						//未完成（可以之后判断如果最后一页换一个函数***）
	{
		
		
		med[i] = *mess.find(i+1+(page-1)*9);

		
	}
	//cout << med[8].get_name() << i;closegraph();
	
	
	for (int j = 0; j < 3; j++)
	{
		for (int k = 0; k < 3; k++)
		{
			putimage(x[k] * Width-0.8*Width, y[j] * High-0.5*High, &bg2_1);
			outtextxy(x[k]*Width, y[j]*High, med[sum].get_name());
			sum++;
			
		}
	
	}
	FlushBatchDraw();             //将绘制完成的图像显示在绘画板上
	MOUSEMSG m;
	while (1)
	{
/*
		m = GetMouseMsg();
		if ((x[0] * Width <= m.x) && (m.x <= x[0] * Width + 5 * Width))
		{
			if ((y[0] * High <= m.y) && (m.y <= y[0] * High + 4 * High))
			{
				med[0].Load_image();
				putimage(23 * Width-0.5*Width, 2 * High-0.5*High, &bg_black);
				putimage(23 * Width, 2*High, &medicine_bg);
				FlushBatchDraw();

			}
			if ((y[1] * High <= m.y) && (m.y <= y[1] * High + 4 * High))
			{
				med[3].Load_image();
				putimage(23 * Width - 0.5*Width, 2 * High - 0.5*High, &bg_black);
				putimage(23 * Width, 2 * High, &medicine_bg);
				FlushBatchDraw();
			}
			else if ((y[2] * NUM <= m.y) && (m.y <= y[2] * High + 4 * High))
			{
				med[6].Load_image();
				putimage(23 * Width - 0.5*Width, 2 * High - 0.5*High, &bg_black);
				putimage(23 * Width, 2 * High, &medicine_bg);
				FlushBatchDraw();
			}

		}
		if ((x[1] * Width <= m.x) && (m.x <= x[1] * Width + 5 * Width))
		{
			if ((y[0] * High <= m.y) && (m.y <= y[0] * High + 4 * High))
			{
				med[1].Load_image();
				putimage(23 * Width - 0.5*Width, 2 * High - 0.5*High, &bg_black);
				putimage(23 * Width, 2*High, &medicine_bg);
				FlushBatchDraw();

			}
			if ((y[1] * High <= m.y) && (m.y <= y[1] * High + 4 * High))
			{
				med[4].Load_image();
				putimage(23 * Width - 0.5*Width, 2 * High - 0.5*High, &bg_black);
				putimage(23 * Width, 2*High, &medicine_bg);
				FlushBatchDraw();
			}
			else if ((y[2] * High <= m.y) && (m.y <= y[2] * High + 4 * High))
			{
				med[7].Load_image();
				putimage(23 * Width - 0.5*Width, 2 * High - 0.5*High, &bg_black);
				putimage(23 * Width, 2*High, &medicine_bg);
				FlushBatchDraw();
			}

		}
		if ((x[2] * Width <= m.x) && (m.x <= x[2] * Width + 5 * Width))
		{
			if ((y[0] * High <= m.y) && (m.y <= y[0] * High + 4 * High))
			{
				med[2].Load_image();
				putimage(23 * Width - 0.5*Width, 2 * High - 0.5*High, &bg_black);
				putimage(23 * Width, 2*High, &medicine_bg);
				FlushBatchDraw();

			}
			if ((y[1] * High <= m.y) && (m.y <= y[1] * High + 4 * High))
			{
				med[5].Load_image();
				putimage(23 * Width - 0.5*Width, 2 * High - 0.5*High, &bg_black);
				putimage(23 * Width, 2*High, &medicine_bg);
				FlushBatchDraw();

			}
			else if ((y[2] * High <= m.y) && (m.y <= y[2] * High + 4 * High))
			{
				med[8].Load_image();
				putimage(23 * Width - 0.5*Width, 2 * High - 0.5*High, &bg_black);
				putimage(23 * Width, 2*High, &medicine_bg);
				FlushBatchDraw();
			}

		}
		else
		{
			putimage(23 * Width - 0.5*Width, 2 * High - 0.5*High, &bg_black);             //鼠标在其他位置时显示空图片
			FlushBatchDraw();
		}
		*/
		while (MouseHit())
		{
			m = GetMouseMsg();
			if (((x[0] * Width <= m.x) && (m.x <= x[0] * Width + 5 * Width)) && (m.uMsg == WM_LBUTTONDOWN))
			{
				if ((y[0] * High <= m.y) && (m.y <= y[0] * High + 4 * High))
				{
					Show_Detail(med[0]);

				}
				if ((y[1] * High <= m.y) && (m.y <= y[1] * High + 4 * High))
				{
					Show_Detail(med[3]);
				}
				else if ((y[2] * High <= m.y) && (m.y <= y[2] * High + 4 * High))
				{
					Show_Detail(med[6]);
				}

			}

			if (((x[1] * Width <= m.x) && (m.x <= x[1] * Width + 5 * Width)) && (m.uMsg == WM_LBUTTONDOWN))
			{
				if ((y[0] * High <= m.y) && (m.y <= y[0] * High + 4 * High))
				{
					Show_Detail(med[1]);

				}
				if ((y[1] * High <= m.y) && (m.y <= y[1] * High + 4 * High))
				{
					Show_Detail(med[4]);
				}
				else if ((y[2] * High <= m.y) && (m.y <= y[2] * High + 4 * High))
				{
					Show_Detail(med[7]);
				}

			}
			if (((x[2] * Width <= m.x) && (m.x <= x[2] * Width + 5 * Width)) && (m.uMsg == WM_LBUTTONDOWN))
			{
				if ((y[0] * High <= m.y) && (m.y <= y[0] * High + 4 * High))
				{
					Show_Detail(med[2]);

				}
				if ((y[1] * High <= m.y) && (m.y <= y[1] * High + 4 * High))
				{
					Show_Detail(med[5]);

				}
				else if ((y[2] * High <= m.y) && (m.y <= y[2] * High + 4 * High))
				{
					Show_Detail(med[8]);
				}

			}


			
			if (((25 * Width <= m.x) && (m.x <= 30 * Width)) && ((30 * High <= m.y) && (m.y <= 32 * High)) && (m.uMsg == WM_LBUTTONDOWN))//返回桌面
			{
		
				putimage(25 * Width, 30 * High, &bg_back_0);	
				FlushBatchDraw();
				Sleep(100);
				menuflag = 0;
				Init();
				
			}
			if (((25 * Width <= m.x) && (m.x <= 30 * Width)) && ((26 * High <= m.y) && (m.y <= 28 * High)) && (m.uMsg == WM_LBUTTONDOWN)&&(page!=max_page))//下一页
			{
				
				
				
				BeginBatchDraw();
				putimage(25 * Width, 26 * High, &bg_next_0);
				FlushBatchDraw();
				Sleep(80);
				PAGE++;
				return 0;
			}
			if (((25 * Width <= m.x) && (m.x <= 30 * Width)) && ((22 * High <= m.y) && (m.y <= 24 * High)) && (m.uMsg == WM_LBUTTONDOWN) && (page !=1))//上一页
			{
				BeginBatchDraw();
				putimage(25 * Width, 22 * High, &bg_last_0);
				FlushBatchDraw();
				Sleep(80);
				PAGE--;
				return 0;
				
			}

		}

	}
return 0;
}
void Show_Detail(Medicine a)
{
	MOUSEMSG m;
	ClearScreen1();
	settextstyle(40, 0, _T("黑体"));   //设置字体样式

	putimage(0, 0, &bg3);			//读取背景图片
	a.Load_image();
	putimage(20*Width,3*High,&medicine_bg);
	putimage(23 * Width, 27 * High, &bg_back);

	a.output();						//完成文字输出
	FlushBatchDraw();
	while (1)
	{
		while (MouseHit())                       //当鼠标点击的时候根据鼠标坐标进行判定
		{
			m = GetMouseMsg();
			if (((23 * Width <= m.x) && (m.x <= 23 * Width + 150)) && (m.uMsg == WM_LBUTTONDOWN))
			{
				if ((27 * High <= m.y) && (m.y <= 30 * High))
					
					menuflag = 1;
				Sleep(100);
				Init();
				return;
			}
		}

	}
	

}
void Show_Detail(Medicine a,int b)
{
	MOUSEMSG m;
	ClearScreen1();
	settextstyle(40, 0, _T("黑体"));   //设置字体样式

	putimage(0, 0, &bg3);			//读取背景图片
	a.Load_image();
	putimage(20 * Width, 3 * High, &medicine_bg);
	putimage(23 * Width, 27 * High, &bg_back);

	a.output();						//完成文字输出
	FlushBatchDraw();
	while (1)
	{
		while (MouseHit())                       //当鼠标点击的时候根据鼠标坐标进行判定
		{
			m = GetMouseMsg();
			if (((23 * Width <= m.x) && (m.x <= 23 * Width + 150)) && (m.uMsg == WM_LBUTTONDOWN))
			{
				if ((27 * High <= m.y) && (m.y <= 30 * High))

					menuflag = 0;
				Sleep(100);
				Init();
				return;
			}
		}

	}


}
void Input()
{
	MOUSEMSG m;
	putimage(0, 0, &bg4);
	char Iname[NUM1];           //药名
	char Iintroduction[NUM2];  //简单介绍
	char Iusage[NUM1];        //使用方法(可治疗的病症）
	char Iclash[NUM1];         //相冲的药物
	char Ipicture[NUM1];       //图片名称
	FlushBatchDraw();
	

	InputBox(Iname, 128, _T("请输入药材名称:"), false);//录入信息
	InputBox(Iintroduction, 128, _T("请输入药材简介:"), false);
	InputBox(Iusage, 128, _T("请输入药材用途:"), false);
	InputBox(Iclash, 128, _T("请输入药材忌讳:"), false);
	InputBox(Ipicture, 128, _T("请输入附图名称（图片放入文件夹）:"), false);

	
	Medicine med(Iname, Iintroduction, Iusage, Iclash, Ipicture);
	med.Write_Data();

	putimage(23 * Width, 27 * High, &bg_back);
	FlushBatchDraw();
	while (1)
	{
		while (MouseHit())                       //当鼠标点击的时候根据鼠标坐标进行判定
		{
			m = GetMouseMsg();
			if (((23 * Width <= m.x) && (m.x <= 23 * Width + 150)) && (m.uMsg == WM_LBUTTONDOWN))
			{
				if ((27 * High <= m.y) && (m.y <= 30 * High))
					putimage(23 * Width, 27 * High, &bg_back_0);
				Sleep(100);
				Init(1);
				menuflag = 4;
			}
		}
	}
}
void WaitView(int page)
{
	int x[3] = { 2,9,17 }, y[3] = { 4,14,24 };
	Medicine med[9];
	MOUSEMSG m;
	for (int i = 0; i < 9; i++)						//未完成（可以之后判断如果最后一页换一个函数***）
	{

		med[i] = *mess.find(i+1 + (page - 1) * 9);

	}
	



		/*m = GetMouseMsg();
		if ((x[0] * Width <= m.x) && (m.x <= x[0] * Width + 5 * Width))
		{
			if ((y[0] * High <= m.y) && (m.y <= y[0] * High + 4 * High))
			{
				med[0].Load_image();
				loadimage(&medicine_bg, _T("雄黄.jpg"));
				putimage(23 * Width, 2*High, &medicine_bg);

			}
			if ((y[1] * High <= m.y) && (m.y <= y[1] * High + 4 * High))
			{
				med[1].Load_image();
				putimage(22 * Width, 0 * NUM, &medicine_bg);
			}
			else if ((y[2] * NUM <= m.y) && (m.y <= y[2] * High + 4 * High))
			{
				med[2].Load_image();
				putimage(22 * Width, 0 * NUM, &medicine_bg);
			}

		}
		if ((x[1] * Width <= m.x) && (m.x <= x[1] * Width + 5 * Width))
		{
			if ((y[0] * High <= m.y) && (m.y <= y[0] * High + 4 * High))
			{
				med[3].Load_image();
				putimage(23 * Width, 2*High, &medicine_bg);

			}
			if ((y[1] * High <= m.y) && (m.y <= y[1] * High + 4 * High))
			{
				med[4].Load_image();
				putimage(23 * Width, 2*High, &medicine_bg);
			}
			else if ((y[2] * High <= m.y) && (m.y <= y[2] * High + 4 * High))
			{
				med[5].Load_image();
				putimage(23 * Width, 2*High, &medicine_bg);
			}

		}
		if ((x[2] * Width <= m.x) && (m.x <= x[2] * Width + 5 * Width))
		{
			if ((y[0] * High <= m.y) && (m.y <= y[0] * High + 4 * High))
			{
				med[6].Load_image();
				putimage(23 * Width, 2*High, &medicine_bg);

			}
			if ((y[1] * High <= m.y) && (m.y <= y[1] * High + 4 * High))
			{
				med[7].Load_image();
				putimage(23 * Width, 2*High, &medicine_bg);

			}
			else if ((y[2] * High <= m.y) && (m.y <= y[2] * High + 4 * High))
			{
				med[8].Load_image();
				putimage(23 * Width, 2*High, &medicine_bg);
			}

		}
		else
		{
			loadimage(&medicine_bg, _T("blank.jpg"));              //鼠标在其他位置时显示空图片
			putimage(23 * Width, 2*High, &medicine_bg);
		}
		*/
		while (MouseHit())
		{
			m = GetMouseMsg();
			if (((x[0] * Width <= m.x) && (m.x <= x[0] * Width + 5 * Width)) && (m.uMsg == WM_LBUTTONDOWN))
			{
				if ((y[0] * High <= m.y) && (m.y <= y[0] * High + 4 * High))
				{
					Show_Detail(med[0]);

				}
				if ((y[1] * High <= m.y) && (m.y <= y[1] * High + 4 * High))
				{
					Show_Detail(med[3]);
				}
				else if ((y[2] * High <= m.y) && (m.y <= y[2] * High + 4 * High))
				{
					Show_Detail(med[6]);
				}

			}

			if (((x[1] * Width <= m.x) && (m.x <= x[1] * Width + 5 * Width)) && (m.uMsg == WM_LBUTTONDOWN))
			{
				if ((y[0] * High <= m.y) && (m.y <= y[0] * High + 4 * High))
				{
					Show_Detail(med[1]);

				}
				if ((y[1] * High <= m.y) && (m.y <= y[1] * High + 4 * High))
				{
					Show_Detail(med[4]);
				}
				else if ((y[2] * High <= m.y) && (m.y <= y[2] * High + 4 * High))
				{
					Show_Detail(med[7]);
				}

			}
			if (((x[2] * Width <= m.x) && (m.x <= x[2] * Width + 5 * Width)) && (m.uMsg == WM_LBUTTONDOWN))
			{
				if ((y[0] * High <= m.y) && (m.y <= y[0] * High + 4 * High))
				{
					Show_Detail(med[3]);

				}
				if ((y[1] * High <= m.y) && (m.y <= y[1] * High + 4 * High))
				{
					Show_Detail(med[5]);

				}
				else if ((y[2] * High <= m.y) && (m.y <= y[2] * High + 4 * High))
				{
					Show_Detail(med[8]);
				}

			}


			if (((25 * Width <= m.x) && (m.x <= 30 * Width)) && ((30 * High <= m.y) && (m.y <= 32 * High)) && (m.uMsg == WM_LBUTTONDOWN))//返回桌面
			{
		
				putimage(25 * Width, 30 * High, &bg_back_0);	
				FlushBatchDraw();
				Sleep(100);
				Init();
				menuflag = 0;
			}
			if (((25 * Width <= m.x) && (m.x <= 30 * Width)) && ((26 * High <= m.y) && (m.y <= 28 * High)) && (m.uMsg == WM_LBUTTONDOWN))//下一页
			{
				
				
				
				BeginBatchDraw();
				putimage(25 * Width, 26 * High, &bg_next_0);
				FlushBatchDraw();
				Sleep(80);
				page++;
				Show_All(page);
			}
			if (((25 * Width <= m.x) && (m.x <= 30 * Width)) && ((22 * High <= m.y) && (m.y <= 24 * High)) && (m.uMsg == WM_LBUTTONDOWN))//上一页
			{
				BeginBatchDraw();
				putimage(25 * Width, 22 * High, &bg_last_0);
				FlushBatchDraw();
				Sleep(80);
				page--;
				Show_All(page);
			}

		}

	
}                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          
const vector<int> * kmp_next(string &m)
{
	static vector<int> next(m.size());
	next[0] = 0;
	int temp;
	for (int i = 1; i < next.size(); i++)
	{
		temp = next[i - 1];
		while (m[i] != m[temp] && temp > 0)
		{
			temp = next[temp - 1];
		}
		if (m[i] == m[temp])
			next[i] = temp + 1;
		else next[i] = 0;
	}
	return &next;
}
bool kmp_search(string text, string m, int &pos)
{
	const vector<int> * next = kmp_next(m);
	int tp = 0;
	int mp = 0;
	for (tp = 0; tp < text.size(); tp++)
	{
		while (text[tp] != m[mp] && mp)
			mp = (*next)[mp - 1];
		if (text[tp] == m[mp])
			mp++;
		if (mp == m.size())
		{
			pos = tp - mp + 1;
			return true;
		}
	}
	if (tp == text.size())
		return false;
}
void Delete()
{
	MOUSEMSG m;
	char s1[50];
	int i, pot = 0, flag = 0;
	putimage(0, 0, &bg4);
	settextstyle(40, 0, _T("微软雅黑"));
	outtextxy(50, 100, _T("请输入要删除的药材名称"));
	FlushBatchDraw();
	InputBox(s1, 25, _T("请输入药名"), false);
	
	flag=mess.Delete(s1);
	if (flag)
	{
		outtextxy(50, 300, _T("删除成功"));
	}
	else
	{
		outtextxy(50, 300, _T("未查询到该药材"));
	}

	putimage(23 * Width, 27 * High, &bg_back);
	FlushBatchDraw();
	while (1)
	{
		while (MouseHit())                       //当鼠标点击的时候根据鼠标坐标进行判定
		{
			m = GetMouseMsg();
			if (((23 * Width <= m.x) && (m.x <= 23 * Width + 150)) && (m.uMsg == WM_LBUTTONDOWN))
			{
				if ((27 * High <= m.y) && (m.y <= 30 * High))
					putimage(23 * Width, 27 * High, &bg_back_0);
				Sleep(100);
				Init(1);
				menuflag = 4;
			}
		}
	}
}
void revise()
{
	MOUSEMSG m;
	putimage(0, 0, &bg4);
	int flag = 0,a;
	char s1[100],s2[5];
	outtextxy(50, 100, _T("请输入要要修改的药材名称"));
	FlushBatchDraw();
	InputBox(s1, 20, _T("请输入要修改的药材名称"));
	InputBox(s2, 10, _T("请输入要修改的信息1.药材名2.简介3.用处4.禁忌"));
	sscanf_s(s2, "%d", &a);
	flag=mess.revise(a, s1);
	if (flag)
	{

		outtextxy(50, 300, _T("修改成功"));
	}
	else
	{
		outtextxy(50, 300, _T("未查询到该药材"));
	}
	
	putimage(23 * Width, 27 * High, &bg_back);
	FlushBatchDraw();
	while (1)
	{
		while (MouseHit())                       //当鼠标点击的时候根据鼠标坐标进行判定
		{
			m = GetMouseMsg();
			if (((23 * Width <= m.x) && (m.x <= 23 * Width + 150)) && (m.uMsg == WM_LBUTTONDOWN))
			{
				if ((27 * High <= m.y) && (m.y <= 30 * High))
					putimage(23 * Width, 27 * High, &bg_back_0);
				Sleep(100);
				Init(1);
				menuflag = 4;
			}
		}
	}
}
void inquiry()
{
	MOUSEMSG m;
	int flag = 0, a;
	char s1[100], s2[5];
	putimage(0, 0, &bg4);
	outtextxy(50, 100, _T("请输入要要查询的药材名称"));
	FlushBatchDraw();
	InputBox(s1, 10, _T("请输入要查询的药材名称"));

	Medicine *ptr= mess.inquiry(s1);
	
	if (ptr!=NULL)
	{
		Show_Detail(*ptr,1);
		outtextxy(50, 300, _T("修改成功"));
	}
	else
	{
		outtextxy(50, 300, _T("未查询到该药材"));
	}
	putimage(23 * Width, 27 * High, &bg_back);
	while (1)
	{
		while (MouseHit())                       //当鼠标点击的时候根据鼠标坐标进行判定
		{
			m = GetMouseMsg();
			if (((23 * Width <= m.x) && (m.x <= 23 * Width + 150)) && (m.uMsg == WM_LBUTTONDOWN))
			{
				if ((27 * High <= m.y) && (m.y <= 30 * High))
					putimage(23 * Width, 27 * High, &bg_back_0);
				Sleep(100);
				Init(1);
				menuflag = 4;
			}
		}
	}
	return;
}






