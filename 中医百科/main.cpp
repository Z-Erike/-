
#include<iostream>
#include<string>
#include<graphics.h>
#include<vector>
#include<conio.h>
#include<Windows.h>

#include"medicine.h"
#include"user.h"

using namespace std;

#define Width 30        //ÿ����
#define High 20         //ÿ�񳤶�
#define NUM 32          //����
#define NUM1 128        //���鳤��
#define NUM2 1024
int menuflag = 0;       //�˵�ѡ��flag
Message mess;


IMAGE bg1,bg2,bg3,bg4;               //����ͼƬԤ����(��0��Ϊ������Ч��ͼ)
IMAGE medicine_bg;					 //װ��ͼƬ�밲װ�İ�ť
IMAGE bg_goon, bg_back, bg_goon_0, bg_back_0;
IMAGE bg_last, bg_next,bg_last_0,bg_next_0;
IMAGE bg1_1, bg1_2, bg1_3, bg1_4,bg1_1_0, bg1_2_0, bg1_3_0, bg1_4_0;
IMAGE bg2_1, bg2_1_0;


void HideCursor();							//���ع�꺯��
void ClearScreen();							//���debug��Ϣ
void ClearScreen1();                        //�����Ļ��Ϣ
void Menu();								//���˵�����
void Menu(int a);							//���˵�������Ա��
void Init();								//��ʼ������
void Init(int a);							//��ʼ�����棨����Ա��
void WaitView(int iCurPage);				//�������ʱ�ȴ��û�����
void WaitUser();							//�ȴ��û�����
void Cure();								//���ݲ�֢����ҩ��
int Show_All(int page);						//ȫ����ʾ
void Show_Detail(Medicine);					//��ʾϸ��
void Input();								//���ļ�����
bool kmp_search(string text, string m, int &pos);//kmp�㷨���Ҳ�֢
const vector<int> * kmp_next(string &m);	//Ѱ����һ��
void Delete();								//ɾ��
void revise();								//�޸�
void inquiry();

int main()									//������
{
	int flag;
	user u;
	flag=u.begin();
	initgraph(Width*NUM, High*NUM);
	if (flag == 1)//�����û�
	{
		while (1)
		{
			Init();
		}
	}
	if (flag == 2)//����Ա
	{
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
		while (MouseHit())                       //���������ʱ����������������ж�
		{
			m = GetMouseMsg();
			if (((23 * Width <= m.x) && (m.x <= 23 * Width + 150)) && (m.uMsg == WM_LBUTTONDOWN))
			{
				if ((27 * High <= m.y) && (m.y <= 30 * High))
					putimage(23 * Width, 27 * High, &bg_back_0);
					Sleep(100);
					menuflag = 1;
				return;
			}
		}
	
}
void Cure()
{
	
	char s1[50],s2[100],temp[100];
	char dou[10] = {","};
	int i,pot=0,flag=0;
	putimage(0, 0, &bg3);
	settextstyle(40, 0, _T("����"));
	outtextxy(50, 100, _T("�����벡֢"));
	FlushBatchDraw();
	InputBox(s1, 25, _T("�����벡֢"),false);
	
	Medicine *ptr;
	for (i = 0; i < mess.get_max();i++)
	{
		pot = 0;
		ptr=mess.find(i);

		if (kmp_search(ptr->get_usage(), s1, pot))
		{
			flag = 1;
			memcpy(ptr->get_name(), temp, sizeof(ptr->get_name()));
			strcat_s(temp, s2);
			strcat_s(dou, s2);
		}
	}
	if (flag==1)
	{
		outtextxy(50, 300, _T("�ɷ�����ҩ��:"));
		outtextxy(100, 350, s2);
	}
	else outtextxy(50, 300, _T("δ�ҵ����ϲ�֢��ҩ��"));

	WaitUser();
	

}
void HideCursor()							//���ع�꺯��
{
	CONSOLE_CURSOR_INFO cursor_info = { 1,0 };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}
void ClearScreen()							//���debug��Ϣ
{
	system("cls");
}
void ClearScreen1()							//���������Ϣ
{
	BeginBatchDraw();
	putimage(0, 0, &bg1);
	setbkmode(TRANSPARENT);
	
}

void Init()
{
	HWND hwnd = GetHWnd();//��ȡ���ھ��
	SetWindowText(hwnd, _T("��ҽҩ�ٿ�"));
	loadimage(&bg1, _T("img\\bg1.jpg"));   //��ȡͼƬ��Ϣ
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
	loadimage(&bg1_2_0, _T("img\\bg1_1_0.jpg"));
	loadimage(&bg1_3_0, _T("img\\bg1_1_0.jpg"));
	loadimage(&bg1_4_0, _T("img\\bg1_1_0.jpg"));
	while (menuflag == 0)
		Menu();			//��ʼ���˵�����
	while (menuflag == 1)
		Show_All(1);		//	��ʾҳ��
	while (menuflag == 2)
		Cure();			//Ѱҽ�ʲ�����
	while (menuflag == 3)
		exit(-1);		//�˳�
}
void Init(int a)
{
	
	//�������֣���δ���ã�
	//mciSendString("open .\\BOOK_music.mp3 alias bkmusic", NULL, 0, NULL);
	//mciSendString("play bkmusic repeat", NULL, 0, NULL);
	HWND hwnd = GetHWnd();//��ȡ���ھ��
	SetWindowText(hwnd, _T("��ҽҩ�ٿ�"));
	loadimage(&bg1, _T("img\\bg1.jpg"));   //��ȡͼƬ��Ϣ
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
	loadimage(&bg1_2_0, _T("img\\bg1_1_0.jpg"));
	loadimage(&bg1_3_0, _T("img\\bg1_1_0.jpg"));
	loadimage(&bg1_4_0, _T("img\\bg1_1_0.jpg"));


	
	
	while (menuflag ==4)
		Menu(1);			//��ʼ���˵�����(����Ա��)
	while (menuflag == 5)
		Delete();			//	ɾ��
	while (menuflag == 6)
		inquiry();	//	�޸�ҳ��
	while (menuflag == 7)
		revise();	//	�޸�ҳ��
	while (menuflag == 8)
		Input();		//	�޸�ҳ��
	while (menuflag == 3)
		exit(-1);		//�˳�
	
	
}
void Menu(int a)
{
	BeginBatchDraw();
	setbkmode(TRANSPARENT);                  //�趨ͼƬģʽΪ���������·�
	putimage(0, 0, &bg1);
	settextstyle(40, 0, _T("����"));
	int Main_x = 500;                       //���Ĵ˴��ı��������������ֺ�����
	putimage(Main_x, 100, &bg1_1);
	putimage(Main_x, 200, &bg1_2);
	putimage(Main_x, 300, &bg1_3);
	putimage(Main_x, 400, &bg1_4);
	FlushBatchDraw();
	Sleep(100);

	MOUSEMSG m;//���ṹ��

	while (MouseHit())                       //���������ʱ����������������ж�
	{
		m = GetMouseMsg();
		if (((Main_x <= m.x) && (m.x <= Main_x + 150)) && (m.uMsg == WM_LBUTTONDOWN))
		{
			if ((100 <= m.y) && (m.y <= 160))
			{
				putimage(Main_x, 100, &bg1_1_0);
				FlushBatchDraw();
				Sleep(100);
				Delete();				//ɾ��
				menuflag = 1;
				return;
			}
			if ((200 <= m.y) && (m.y <= 260))
			{
				putimage(Main_x, 100, &bg1_2_0);
				FlushBatchDraw();
				Sleep(100);
				inquiry();
				menuflag = 2;
				return;
			}
			if ((300 <= m.y) && (m.y <= 360))
			{
				putimage(Main_x, 100, &bg1_3_0);
				FlushBatchDraw();
				Sleep(100);
				revise();	
				menuflag = 3;
			}
			if ((400 <= m.y) && (m.y <= 460))
			{
				putimage(Main_x, 100, &bg1_3_0);
				FlushBatchDraw();
				Sleep(100);
				Input();
				menuflag = 3;
			}
			if ((500 <= m.y) && (m.y <= 560))
			{
				putimage(Main_x, 100, &bg1_3_0);
				FlushBatchDraw();
				Sleep(100);
				exit(-1);
				menuflag = 3;
			}
			

		}
	}
}
void Menu()									//���˵�
{
	BeginBatchDraw();
	setbkmode(TRANSPARENT);                  //�趨ͼƬģʽΪ���������·�
	putimage(0, 0, &bg1);
	settextcolor(RED);
	settextstyle(40, 0, _T("����"));
	int Main_x = 500;                       //���Ĵ˴��ı��������������ֺ�����
	putimage(Main_x, 100, &bg1_1);
	putimage(Main_x, 200, &bg1_2);
	putimage(Main_x, 300, &bg1_3);
	putimage(Main_x, 400, &bg1_4);
	FlushBatchDraw();
	Sleep(10);

	MOUSEMSG m;//���ṹ��
	
		while (MouseHit())                       //���������ʱ����������������ж�
		{
			m = GetMouseMsg();
			if (((Main_x <= m.x) && (m.x <= Main_x + 150)) && (m.uMsg == WM_LBUTTONDOWN))
			{
				if ((100 <= m.y) && (m.y <= 160))
				{
					putimage(Main_x, 100, &bg1_1_0);
					FlushBatchDraw();
					Sleep(100);
					Show_All(1);				//��λ����һҳ
					menuflag = 1;
					return;
				}
				if ((200 <= m.y) && (m.y <= 260))
				{
					putimage(Main_x, 100, &bg1_2_0);
					FlushBatchDraw();
					Sleep(100);
					Cure();
					menuflag = 2;
					return;
				}
				if ((300 <= m.y) && (m.y <= 360))
				{
					putimage(Main_x, 100, &bg1_3_0);
					FlushBatchDraw();
					Sleep(100);
					exit(-1);
					menuflag = 3;
				}
				else if ((400 <= m.y) && (m.y <= 460))
				{
					BeginBatchDraw();
					putimage(Main_x, 100, &bg1_4_0);
					FlushBatchDraw();
					Sleep(100);
					exit(-1);
					menuflag = 3;
				}
				
			}
		}
	
}

int Show_All(int page)              //�������⣨��һ���ǿյģ�
{
	int x[3] = { 2,9,17 }, y[3] = { 4,14,24 };  //ÿ��ѡ���ڵĸ���
	int  i, max_page, last_page, sum = 0;
	Medicine med[9];
	max_page = mess.get_max() / 9;				//���ҳ��
	last_page = mess.get_max() % 9;				//���һҳʣ�µ�������
	ClearScreen1();								//���ͼ��
	BeginBatchDraw();							//��ʼ������ͼ
	putimage(Width*NUM, High*NUM, &bg2);
	settextstyle(40, 0, _T("΢���ź�"));
	settextcolor(BLACK);
	outtextxy(480, 20, _T("ȫ��ҩ��"));			//�˵������������
	settextstyle(30, 0, _T("����"));
	putimage(25 * Width, 22 * High, &bg_last);
	putimage(25 * Width, 26 * High, &bg_next);
	putimage(25 * Width, 30 * High, &bg_back);

	for (i = 0; i <9; i++)						//δ��ɣ�����֮���ж�������һҳ��һ������***��
	{
		
		med[i] = *mess.find(i+(page-1)*9);

	}
	//cout << med[8].get_name() << i;closegraph();
	
	
	for (int j = 0; j < 3; j++)
	{
		for (int k = 0; k < 3; k++)
		{
			outtextxy(x[k]*Width, y[j]*High, med[sum].get_name());
			sum++;
		
		}

	}
	FlushBatchDraw();             //��������ɵ�ͼ����ʾ�ڻ滭����
	MOUSEMSG m;
	
	while (1)
	{
		/*m = GetMouseMsg();
		if ((x[0] * Width <= m.x) && (m.x <= x[0] * Width + 5 * Width))
		{
			if ((y[0] * High <= m.y) && (m.y <= y[0] * High + 4 * High))
			{
				med[0].Load_image();
				loadimage(&medicine_bg, _T("�ۻ�.jpg"));
				putimage(22 * Width, 0, &medicine_bg);

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
				putimage(22 * Width, 0, &medicine_bg);

			}
			if ((y[1] * High <= m.y) && (m.y <= y[1] * High + 4 * High))
			{
				med[4].Load_image();
				putimage(22 * Width, 0, &medicine_bg);
			}
			else if ((y[2] * High <= m.y) && (m.y <= y[2] * High + 4 * High))
			{
				med[5].Load_image();
				putimage(22 * Width, 0, &medicine_bg);
			}

		}
		if ((x[2] * Width <= m.x) && (m.x <= x[2] * Width + 5 * Width))
		{
			if ((y[0] * High <= m.y) && (m.y <= y[0] * High + 4 * High))
			{
				med[6].Load_image();
				putimage(22 * Width, 0, &medicine_bg);

			}
			if ((y[1] * High <= m.y) && (m.y <= y[1] * High + 4 * High))
			{
				med[7].Load_image();
				putimage(22 * Width, 0, &medicine_bg);

			}
			else if ((y[2] * High <= m.y) && (m.y <= y[2] * High + 4 * High))
			{
				med[8].Load_image();
				putimage(22 * Width, 0, &medicine_bg);
			}

		}
		else
		{
			loadimage(&medicine_bg, _T("blank.jpg"));              //���������λ��ʱ��ʾ��ͼƬ
			putimage(22 * Width, 0, &medicine_bg);
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


			
			if (((25 * Width <= m.x) && (m.x <= 30 * Width)) && ((30 * High <= m.y) && (m.y <= 32 * High)) && (m.uMsg == WM_LBUTTONDOWN))//��������
			{
		
				putimage(25 * Width, 30 * High, &bg_back_0);	
				FlushBatchDraw();
				Sleep(100);
				Init();
				menuflag = 0;
			}
			if (((25 * Width <= m.x) && (m.x <= 30 * Width)) && ((26 * High <= m.y) && (m.y <= 28 * High)) && (m.uMsg == WM_LBUTTONDOWN))//��һҳ
			{
				
				
				
				BeginBatchDraw();
				putimage(25 * Width, 26 * High, &bg_next_0);
				FlushBatchDraw();
				Sleep(80);
				page++;
				Show_All(page);
			}
			if (((25 * Width <= m.x) && (m.x <= 30 * Width)) && ((22 * High <= m.y) && (m.y <= 24 * High)) && (m.uMsg == WM_LBUTTONDOWN))//��һҳ
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
return 0;
}
void Show_Detail(Medicine a)
{
	MOUSEMSG m;
	ClearScreen1();
	settextstyle(40, 0, _T("����"));   //����������ʽ

	putimage(0, 0, &bg3);			//��ȡ����ͼƬ
	a.Load_image();
	putimage(20*Width,3*High,&medicine_bg);
	putimage(23 * Width, 27 * High, &bg_back);

	a.output();						//����������
	FlushBatchDraw();
	while (MouseHit())                       //���������ʱ����������������ж�
		{
			m = GetMouseMsg();
			if (((23 * Width <= m.x) && (m.x <= 23 * Width + 150)) && (m.uMsg == WM_LBUTTONDOWN))
			{
				if ((27 * High <= m.y) && (m.y <= 30 * High))
					menuflag = 1;
				Sleep(100);
				return;
			}
		}
	

	

}
void Input()
{
	
	char Iname[NUM1];           //ҩ��
	char Iintroduction[NUM2];  //�򵥽���
	char Iusage[NUM1];        //ʹ�÷���(�����ƵĲ�֢��
	char Iclash[NUM1];         //����ҩ��
	char Ipicture[NUM1];       //ͼƬ����

	ClearScreen1();            //���»�����

	InputBox(Iname, 128, _T("������ҩ������:"), false);//¼����Ϣ
	InputBox(Iintroduction, 128, _T("������ҩ�ļ��:"), false);
	InputBox(Iusage, 128, _T("������ҩ����;:"), false);
	InputBox(Iclash, 128, _T("������ҩ�ļɻ�:"), false);
	InputBox(Ipicture, 128, _T("�����븽ͼ���ƣ�ͼƬ�����ļ��У�:"), false);

	
	Medicine med(Iname, Iintroduction, Iusage, Iclash, Ipicture);
	med.Write_Data();
	WaitUser();//	�ȴ��û�����
}
void WaitView(int page)
{
	int x[3] = { 2,9,17 }, y[3] = { 4,14,24 };
	Medicine med[9];
	MOUSEMSG m;
	for (int i = 0; i < 9; i++)						//δ��ɣ�����֮���ж�������һҳ��һ������***��
	{

		med[i] = *mess.find(i+1 + (page - 1) * 9);

	}
	



		/*m = GetMouseMsg();
		if ((x[0] * Width <= m.x) && (m.x <= x[0] * Width + 5 * Width))
		{
			if ((y[0] * High <= m.y) && (m.y <= y[0] * High + 4 * High))
			{
				med[0].Load_image();
				loadimage(&medicine_bg, _T("�ۻ�.jpg"));
				putimage(22 * Width, 0, &medicine_bg);

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
				putimage(22 * Width, 0, &medicine_bg);

			}
			if ((y[1] * High <= m.y) && (m.y <= y[1] * High + 4 * High))
			{
				med[4].Load_image();
				putimage(22 * Width, 0, &medicine_bg);
			}
			else if ((y[2] * High <= m.y) && (m.y <= y[2] * High + 4 * High))
			{
				med[5].Load_image();
				putimage(22 * Width, 0, &medicine_bg);
			}

		}
		if ((x[2] * Width <= m.x) && (m.x <= x[2] * Width + 5 * Width))
		{
			if ((y[0] * High <= m.y) && (m.y <= y[0] * High + 4 * High))
			{
				med[6].Load_image();
				putimage(22 * Width, 0, &medicine_bg);

			}
			if ((y[1] * High <= m.y) && (m.y <= y[1] * High + 4 * High))
			{
				med[7].Load_image();
				putimage(22 * Width, 0, &medicine_bg);

			}
			else if ((y[2] * High <= m.y) && (m.y <= y[2] * High + 4 * High))
			{
				med[8].Load_image();
				putimage(22 * Width, 0, &medicine_bg);
			}

		}
		else
		{
			loadimage(&medicine_bg, _T("blank.jpg"));              //���������λ��ʱ��ʾ��ͼƬ
			putimage(22 * Width, 0, &medicine_bg);
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


			if (((25 * Width <= m.x) && (m.x <= 30 * Width)) && ((30 * High <= m.y) && (m.y <= 32 * High)) && (m.uMsg == WM_LBUTTONDOWN))//��������
			{
		
				putimage(25 * Width, 30 * High, &bg_back_0);	
				FlushBatchDraw();
				Sleep(100);
				Init();
				menuflag = 0;
			}
			if (((25 * Width <= m.x) && (m.x <= 30 * Width)) && ((26 * High <= m.y) && (m.y <= 28 * High)) && (m.uMsg == WM_LBUTTONDOWN))//��һҳ
			{
				
				
				
				BeginBatchDraw();
				putimage(25 * Width, 26 * High, &bg_next_0);
				FlushBatchDraw();
				Sleep(80);
				page++;
				Show_All(page);
			}
			if (((25 * Width <= m.x) && (m.x <= 30 * Width)) && ((22 * High <= m.y) && (m.y <= 24 * High)) && (m.uMsg == WM_LBUTTONDOWN))//��һҳ
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
	
	char s1[50];
	int i, pot = 0, flag = 0;
	putimage(0, 0, &bg4);
	settextstyle(40, 0, _T("΢���ź�"));
	outtextxy(50, 100, _T("������Ҫɾ����ҩ������"));
	FlushBatchDraw();
	InputBox(s1, 25, _T("������ҩ��"), false);
	
	flag=mess.Delete(s1);
	if (flag)
	{
		outtextxy(50, 300, _T("ɾ���ɹ�"));
	}
	else
	{
		outtextxy(50, 300, _T("δ��ѯ����ҩ��"));
	}

	WaitUser();
}
void revise()
{
	putimage(0, 0, &bg4);
	int flag = 0,a;
	char s1[100],s2[5];
	outtextxy(50, 100, _T("������ҪҪ�޸ĵ�ҩ������"));
	InputBox(s1, 20, _T("������Ҫ�޸ĵ�ҩ������"));
	InputBox(s2, 5, _T("������Ҫ�޸ĵ���Ϣ1.ҩ����2.���3.�ô�4.����"));
	sscanf_s(s2, "%d", &a);
	flag=mess.revise(a, s1);
	if (flag)
	{

		outtextxy(50, 300, _T("�޸ĳɹ�"));
	}
	else
	{
		outtextxy(50, 300, _T("δ��ѯ����ҩ��"));
	}
	WaitUser();
}
void inquiry()
{
	int flag = 0, a;
	char s1[100], s2[5];
	putimage(0, 0, &bg4);
	outtextxy(50, 100, _T("������ҪҪ��ѯ��ҩ������"));
	InputBox(s1, 5, _T("������Ҫ��ѯ��ҩ������"));
	Medicine *ptr= mess.inquiry(s1);
	Show_Detail(*ptr);
	if (flag)
	{
		outtextxy(50, 300, _T("�޸ĳɹ�"));
	}
	else
	{
		outtextxy(50, 300, _T("δ��ѯ����ҩ��"));
	}
	WaitUser();
}






