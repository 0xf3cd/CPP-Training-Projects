/*1550431 �ƿ�3�� �����*/
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <iomanip>
#include "cmd_console_tools.h"
using namespace std;
#define zhux 1
#define zhuy 15
int z1cs = 0, z2cs = 0, z3cs = 0, steps = 0;
int z1[10] = { 0 }, z2[10] = { 0 }, z3[10]={0};

int panduan();
void showbranches();
void whichbranch(int n);
int getcs();
char getqs();
char getjs(char qs);
char getzz(char qs, char js);
int getspeed();
void fillin(char qs, int cs);
void hanoi(int n, int cs, char a, char b, char c, int speed);
void whattocout(int n, char from, char to, int speed);
void move(int from, int to);
void whattodo(int n, char from, char to, int speed);
void shuchuheng(int x, int y, char from, char to, bool whether_go);
void shuchushu(int x, int y);
void drawzhuzi(int x, int y);
void makeapause();
void sleepforawhile(int speed);
void drawpanzi(int cs, int z);
void moveabrick(HANDLE hout, char from, char to, int speed);
void drawhanoi(int n, int cs, char qs, char zz, char js, int speed);
int howmanypanzi(int z);
int topofzhu(int z);
void onlyfor9(int cs,char qs,char zz,char js,int speed);
bool judgethezhu(int cs,char js);
bool checkvalid(char x,char y);
char turnactoAC(char x);

int main()
{
	const HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE); //ȡ��׼����豸��Ӧ�ľ��
	char choose = 0;

	while (1)
	{
		setconsoleborder(hout, 70, 30);
		showbranches();
		choose = _getch();
		cout << choose << endl;

		if (choose == '0')
			break;

		if (choose == '5')
		{
			system("cls");
			system("mode con cols=110 lines=30");
			drawzhuzi(zhux, zhuy);
			gotoxy(hout, zhux, zhuy + 2);
			setcolor(hout, COLOR_BLACK, COLOR_WHITE);
			makeapause();
		}
		else if (choose >= '1'&&choose <= '9')
			whichbranch(int(choose - '0'));

		choose = 0;
		z1cs = 0;
		z2cs = 0;
		z3cs = 0;
		steps = 0;
		z1[10] = { 0 };
		z2[10] = { 0 };
		z3[10] = { 0 };
	}

	return 0;
}

int panduan()
{
	char x;
	int n = 0;

	cin >> x;
	while (1)
	{
		if (x == ' ' || x == '\n')
			break;

		if (int(x) > 57 || int(x) < 48)
		{
			cin.clear();
			cin.ignore(1024, '\n');
			cout << "�Ƿ����룬���������룺";
			n = 0;
			cin >> x;
			continue;
		}

		if (int(x) >= 48 && int(x) <= 57)
			n = n * 10 + (int(x) - 48);

		x = char(getchar());
	}

	return n;
}

void showbranches()
{
	system("cls");

	cout << "---------------------------------" << endl;
	cout << "1.������\n2.�����⣨������¼��\n3.�ڲ�������ʾ������\n4.�ڲ�������ʾ������+����" << endl;
	cout << "5.ͼ�ν�-Ԥ��-������Բ��\n6.ͼ�ν�-Ԥ��-����ʼ���ϻ�n������\n7.ͼ�ν�-Ԥ��-��һ���ƶ�" << endl;
	cout << "8.ͼ�ν�-�Զ��ƶ��汾\n9.ͼ�ν�-��Ϸ��\n0.�˳�" << endl;
	cout << "---------------------------------" << endl;
	cout << "[��ѡ��0-9] ";
}

void whichbranch(int n)
{
	const HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	char qs, zz, js;
	int cs, speed = -1;

	cs = getcs();
	qs = getqs();
	js = getjs(qs);
	fillin(qs, cs);
	zz = getzz(qs, js);

	if (n == 4 || n == 8)
		speed = getspeed();

	system("cls");
	if (n == 3 || n == 4)
		system("mode con cols=110 lines=30");

	if (n == 4 )
		cout << "�� " << qs << " �ƶ��� " << js << " ���� " << cs << " ��"<< "����ʱ����Ϊ " << speed << endl;

	if (speed != 0)
		speed = (6 - speed) * 20;

	if (n < 5)
	{
		hanoi(n, cs, qs, zz, js, speed);
		setcolor(hout, COLOR_BLACK, COLOR_WHITE);
		makeapause();
	}
	else//n=6-9ʱ
	{

		if (n == 8)
		{
			system("mode con cols=100 lines=35");
			drawzhuzi(zhux, zhuy);
			setcolor(hout, COLOR_BLACK, COLOR_WHITE);
			shuchushu(zhux + 5, zhuy + 11);
			shuchuheng(0, zhuy + 15, qs, zz, 1);
		}
		else if (n == 9)
		{
			system("mode con cols=100 lines=38");
			speed = 1;
			drawzhuzi(zhux, zhuy);
			setcolor(hout, COLOR_BLACK, COLOR_WHITE);
			shuchushu(zhux + 5, zhuy + 11);
			shuchuheng(0, zhuy + 15, qs, zz, 1);
		}
		else
		{
			system("mode con cols=100 lines=25");
			drawzhuzi(zhux, zhuy);
			setcolor(hout, COLOR_BLACK, COLOR_WHITE);
		}

		gotoxy(hout, 0, 0);
		cout << "�� " << qs << " �ƶ��� " << js << " ���� " << cs << " ��";
		if (n == 8)
			cout << "����ʱ����Ϊ " << speed << endl;

		drawhanoi(n, cs, qs, zz, js, speed);
		setcolor(hout, COLOR_BLACK, COLOR_WHITE);
		makeapause();
	}

}

int getcs()
{
	int cs = 0;

	while (1)
	{
		cout << "�����������1-10����";
		cs = panduan();

		if (cs >= 1 && cs <= 10)
			break;

		cs = 0;
	}

	return cs;
}

char getqs()
{
	char qs;

	while (1)
	{
		cout << "��������ʼԲ������A-C����";
		cin >> qs;

		if (qs == 'A' || qs == 'B' || qs == 'C')
			break;
		else
		{
			qs = 'D';
			cin.clear();
			cin.ignore(1024, '\n');
		}
	}

	return qs;
}

char getjs(char qs)
{
	char js;

	while (1)
	{
		cout << "���������Բ������A-C����";
		cin >> js;

		if (js == 'A' || js == 'B' || js == 'C')
		{
			if (qs != js)
				break;
		}
		else
		{
			js = 'D';
			cin.clear();
			cin.ignore(1024, '\n');
		}
	}

	return js;
}

char getzz(char qs, char js)
{
	char zz = 'A';

	while (1)
	{
		if (zz != js&&zz != qs)
			break;
		else
			zz += 1;
	}

	return zz;
}

int getspeed()
{
	int speed;

	while (1)
	{
		cout << "�������ƶ��ٶ�(0-5��0-���س�������ʾ 1-��ʱ� 5-��ʱ���):";
		speed = panduan();

		if (speed >= 0 && speed <= 5)
			break;

		speed = -1;
	}

	return speed;
}

void fillin(char qs, int cs)
{
	int i;

	if (qs == 'A')
	{
		z1cs = cs;
		for (i = 0; i < cs; i++)
		{
			z1[i] = cs - i;
		}
	}
	else if (qs == 'B')
	{
		z2cs = cs;
		for (i = 0; i < cs; i++)
		{
			z2[i] = cs - i;
		}
	}
	else
	{
		z3cs = cs;
		for (i = 0; i < cs; i++)
		{
			z3[i] = cs - i;
		}
	}
}

void hanoi(int n, int cs, char a, char b, char c, int speed)
{
	if (cs == 1)
	{
		whattodo(n, a, c, speed);
	}
	else
	{
		hanoi(n, cs - 1, a, c, b, speed);
		whattodo(n, a, c, speed);
		hanoi(n, cs - 1, b, a, c, speed);
	}
}

void whattodo(int n, char a, char c, int speed)
{
	const HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	if (n == 8||n==9|| (n == 7 && steps == 0))
	{
		moveabrick(hout, a, c, speed);
	}
	move(int(a - 'A') + 1, int(c - 'A') + 1);
	whattocout(n, a, c, speed);
}

void whattocout(int n, char from, char to, int speed)
{
	const HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	switch (n)
	{
		case(1):
			cout << from << "---->" << to << endl;
			break;
		case(2):
			cout << "��" << setw(5) << steps << "  ����" << from << "---->" << to << endl;
			break;
		case(3):
			shuchuheng(0, 0, from, to, 0);
			break;
		case(4):
			sleepforawhile(speed);
			shuchushu(10, 15);
			gotoxy(hout, 0, 20);
			shuchuheng(0, 20, from, to, 1);
			break;
		case(8):
			setcolor(hout, COLOR_BLACK, COLOR_WHITE);
			shuchushu(zhux + 5, zhuy + 11);
			shuchuheng(0, zhuy + 15, from, to, 1);
			break;
		case(9):
			setcolor(hout, COLOR_BLACK, COLOR_WHITE);
			shuchushu(zhux + 5, zhuy + 11);
			shuchuheng(0, zhuy + 15, from, to, 1);
			break;
	}
}

void move(int from, int to)
{
	int trans;

	switch (from)
	{
		case(1):
			z1cs--;
			trans = z1[z1cs];
			break;
		case(2):
			z2cs--;
			trans = z2[z2cs];
			break;
		default:
			z3cs--;
			trans = z3[z3cs];
			break;
	}

	switch (to)
	{
		case(1):
			z1[z1cs] = trans;
			z1cs++;
			break;
		case(2):
			z2[z2cs] = trans;
			z2cs++;
			break;
		default:
			z3[z3cs] = trans;
			z3cs++;
			break;
	}

	steps++;
}

void shuchuheng(int x, int y, char from, char to, bool whether_go)
{
	const HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	int i, spacez1 = 2 * (10 - z1cs), spacez2 = 2 * (10 - z2cs), spacez3 = 2 * (10 - z3cs);

	if (whether_go == 1)
		gotoxy(hout, x, y);

	if (steps == 0)
		cout << "��ʼ�� ";
	else
		cout << "��" << setw(5) << steps << "  ����" << from << "---->" << to << ' ';

	//���A��
	cout << "A: ";
	for (i = 0; i < z1cs; i++)
	{
		cout << z1[i] << ' ';
	}
	for (i = 1; i <= spacez1; i++)
	{
		cout << ' ';
	}

	//���B��
	cout << "B: ";
	for (i = 0; i < z2cs; i++)
	{
		cout << z2[i] << ' ';
	}
	for (i = 1; i <= spacez2; i++)
	{
		cout << ' ';
	}

	//���C��
	cout << "C: ";
	for (i = 0; i < z3cs; i++)
	{
		cout << z3[i] << ' ';
	}
	for (i = 1; i <= spacez3; i++)
	{
		cout << ' ';
	}

	cout << endl;
}

void shuchushu(int x, int y)
{
	//(x,y)��A�������һ�����ӵ�����
	const HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	int i;

	//���A��
	for (i = 0; i < 10; i++)
	{
		gotoxy(hout, x, y - i);
		cout << "  ";
	}
	for (i = 0; i < z1cs; i++)
	{
		gotoxy(hout, x, y - i);
		cout << z1[i];
	}

	//���B��
	for (i = 0; i < 10; i++)
	{
		gotoxy(hout, x + 10, y - i);
		cout << "  ";
	}
	for (i = 0; i < z2cs; i++)
	{
		gotoxy(hout, x + 10, y - i);
		cout << z2[i];
	}

	//���C��
	for (i = 0; i < 10; i++)
	{
		gotoxy(hout, x + 20, y - i);
		cout << "  ";
	}
	for (i = 0; i < z3cs; i++)
	{
		gotoxy(hout, x + 20, y - i);
		cout << z3[i];
	}

	gotoxy(hout, x - 2, y + 1);
	for (i = 1; i <= 24; i++)
		cout << '=';

	gotoxy(hout, x, y + 2);
	cout << 'A';
	gotoxy(hout, x + 10, y + 2);
	cout << 'B';
	gotoxy(hout, x + 20, y + 2);
	cout << 'C';
}

void drawzhuzi(int x, int y)
{
	//(x,y)Ϊ��1���������½�����
	const HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	int i, x1 = x, x2 = x + 30, x3 = x + 60;

	showch(hout, x1, y, ' ', 6, 6, 25);
	sleepforawhile(50);
	for (i = 1; i <= 11; i++)
	{
		showch(hout, x1 + 12, y - i, ' ', 6, 6, 1);
		sleepforawhile(50);
	}

	showch(hout, x2, y, ' ', 6, 6, 25);
	sleepforawhile(50);
	for (i = 1; i <= 11; i++)
	{
		showch(hout, x2 + 12, y - i, ' ', 6, 6, 1);
		sleepforawhile(50);
	}

	showch(hout, x3, y, ' ', 6, 6, 25);
	sleepforawhile(50);
	for (i = 1; i <= 11; i++)
	{
		showch(hout, x3 + 12, y - i, ' ', 6, 6, 1);
		sleepforawhile(50);
	}
}

void makeapause()
{
	cout << "\n���س�������...";

	while (_getch() != '\r')
		;
}

void sleepforawhile(int speed)
{
	if (speed == 0)
	{
		while (_getch() != '\r')
			;
	}
	else
		Sleep(speed);
}

void drawpanzi(int cs, int z)
{
	const HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	int i, j;
	const int x = (z - 1) * 30 + zhux;

	for (i = cs; i >= 1; i--)
	{
		sleepforawhile(20);

		setcolor(hout, COLOR_BLACK, COLOR_WHITE);

		gotoxy(hout, x, zhuy - (cs - i + 1));
		for (j = 1; j <= 12 - i; j++)
			cout << ' ';

		setcolor(hout, i + 2, i + 1);
		for (j = 1; j <= 2 * i + 1; j++)
		{
			sleepforawhile(5);
			cout << ' ';
		}
	}
}

void drawhanoi(int n, int cs, char qs, char zz, char js, int speed)
{
	const HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	setcolor(hout, COLOR_BLACK, COLOR_WHITE);
	switch (n)
	{
		case(6):
			drawpanzi(cs, int(qs - 'A') + 1);
			setcolor(hout, COLOR_BLACK, COLOR_WHITE);
			gotoxy(hout, 0, zhuy + 2);
			break;
		case(7):
			drawpanzi(cs, int(qs - 'A') + 1);
			setcolor(hout, COLOR_BLACK, COLOR_WHITE);
			sleepforawhile(150);
			hanoi(n, cs, qs, zz, js, 5);
			gotoxy(hout, 0, zhuy + 2);
			break;
		case(8):
			drawpanzi(cs, int(qs - 'A') + 1);
			setcolor(hout, COLOR_BLACK, COLOR_WHITE);
			hanoi(n, cs, qs, zz, js, speed);
			break;
		case(9):
			drawpanzi(cs, int(qs - 'A') + 1);
			setcolor(hout, COLOR_BLACK, COLOR_WHITE);
			onlyfor9(cs,qs,zz,js,speed);
			break;
	}
}

void moveabrick(HANDLE hout, char from, char to, int speed)
{
	int fromz = int(from - 'A') + 1, toz = int(to - 'A') + 1, fgs = howmanypanzi(fromz), tgs = howmanypanzi(toz), fbh = topofzhu(fromz);
	const int x = (fromz - 1) * 30 + zhux, y = zhuy - 12;
	int spacesleft = 12 - fbh, lenthofpanzi = fbh * 2 + 1, dis = toz - fromz, i, j, fromx = x + spacesleft, tox = fromx + 30 * dis;

	sleepforawhile(speed);
	if (speed == 20||speed==0)//����Ϊ�˴ﵽ����չʾЧ����ͬʱ��֤�����ٶȣ����Ǳ�Ҫ����
		speed =1;

	//����from���϶��˵�����
	{
		gotoxy(hout, x, zhuy - fgs);
		setcolor(hout, COLOR_BLACK, COLOR_WHITE);
		for (i = 1; i <= 25; i++)
		{
			cout << ' ';
		}

		setcolor(hout, 6, 6);
		gotoxy(hout, x + 12, zhuy - fgs);
		cout << ' ';
	}

	//�����������ƶ���from������
	{
		for (i = zhuy - fgs - 1; i >= zhuy - 11; i--)
		{
			Sleep(speed);
			gotoxy(hout, fromx, i);
			setcolor(hout, fbh + 2, fbh + 1);
			for (j = 1; j <= lenthofpanzi; j++)
			{
				cout << ' ';
			}
			Sleep(speed);

			gotoxy(hout, x, i);
			setcolor(hout, COLOR_BLACK, COLOR_WHITE);
			for (j = 1; j <= 25; j++)
			{
				cout << ' ';
			}

			setcolor(hout, 6, 6);
			gotoxy(hout, x + 12, i);
			cout << ' ';
		}
	}

	//�������ƶ���to���Ķ���
	{
		i = fromx;
		while (1)
		{
			Sleep(speed);
			gotoxy(hout, i, y);
			setcolor(hout, COLOR_BLACK, COLOR_WHITE);
			for (j = 1; j <= lenthofpanzi; j++)
			{
				cout << ' ';
			}

			if (dis > 0)
			{
				i++;
				if (i > tox)
					break;
			}
			else
			{
				i--;
				if (i < tox)
					break;
			}

			gotoxy(hout, i, y);
			setcolor(hout, fbh + 2, fbh + 1);
			for (j = 1; j <= lenthofpanzi; j++)
			{
				cout << ' ';
			}
		}
	}

	//�����ӽ��䵽to����
	{
		for (i = y + 1; i <= zhuy - tgs - 1; i++)
		{
			Sleep(speed);
			gotoxy(hout, tox, i);
			setcolor(hout, fbh + 2, fbh + 1);
			for (j = 1; j <= lenthofpanzi; j++)
			{
				cout << ' ';
			}
			Sleep(speed);

			gotoxy(hout, x + 30 * dis, i);
			setcolor(hout, COLOR_BLACK, COLOR_WHITE);
			for (j = 1; j <= 25; j++)
			{
				cout << ' ';
			}

			setcolor(hout, 6, 6);
			gotoxy(hout, x + 30 * dis + 12, i);
			cout << ' ';
		}
	}

	//������������λ��
	{
		Sleep(speed);
		gotoxy(hout, tox, zhuy - tgs - 1);
		setcolor(hout, fbh + 2, fbh + 1);
		for (j = 1; j <= lenthofpanzi; j++)
		{
			cout << ' ';
		}
	}
}

int howmanypanzi(int z)
{
	int gs;

	if (z == 1)
		gs = z1cs;
	else if (z == 2)
		gs = z2cs;
	else
		gs = z3cs;

	return gs;
}

int topofzhu(int z)
{
	int bh;

	if (z == 1)
		bh = z1[z1cs - 1];
	else if (z == 2)
		bh = z2[z2cs - 1];
	else
		bh = z3[z3cs - 1];

	return bh;
}

void onlyfor9(int cs,char qs, char zz, char js,int speed)
{
	const HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	char x=0, y=0;

	while (1)
	{
		gotoxy(hout, 0, zhuy + 17);
		cout << "�������ƶ�������(������ʽ��AC=A���˵������ƶ���C) ��        ";
		gotoxy(hout, 52, zhuy + 17);

		cin >> x;
		cin >> y;
		cin.clear();
		cin.ignore(1024, '\n');
		x = turnactoAC(x);
		y = turnactoAC(y);
		gotoxy(hout, 52, zhuy + 17);
		cout << "                ";
		gotoxy(hout, 0, zhuy + 18);

		if (checkvalid(x, y))
		{
			whattodo(9, x, y, speed);
		}

		if (judgethezhu(cs,js))
		{
			gotoxy(hout, 0, zhuy + 18);
			cout << "��Ϸ������";
			break;
		}

		gotoxy(hout, 0, zhuy + 18);
		cout << "                                   ";

		x = 0;
		y = 0;
	}
}

bool checkvalid(char x,char y)
{
	const HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	bool whether_ok = 1;

	if (x<'A' || x>'C')
		whether_ok = 0;
	if (y<'A' || y>'C')
		whether_ok = 0;

	int pzofx = howmanypanzi(int(x - 'A') + 1),topofx = topofzhu(int(x - 'A') + 1), topofy = topofzhu(int(y - 'A') + 1);
	if(x==y)
	{
		cout << "����ͬ����";
		whether_ok = 0;
	}
	if(pzofx==0)
	{
		cout << "Դ����������";
		whether_ok = 0;
	}
	if((topofx>topofy)&&(topofy!=0))
	{
		cout << "����ѹС�̣��Ƿ��ƶ�";
		whether_ok = 0;
	}
	
	Sleep(500);

	return whether_ok;
}

bool judgethezhu(int cs,char js)
{
	int i;

	if(js=='A')
	{
		for(i=0;i<=cs-1;i++)
		{
			if(z1[i]!=cs-i)
			{
				return 0;
			}
		}
	}
	else if (js == 'B')
	{
		for (i = 0; i <= cs-1; i++)
		{
			if (z2[i] != cs - i)
			{
				return 0;
			}
		}
	}
	else 
	{
		for (i = 0; i <= cs - 1; i++)
		{
			if (z3[i] != cs - i)
			{
				return 0;
			}
		}
	}

	return 1;
}

char turnactoAC(char x)
{
	if (x >= 'a'&&x <= 'z')
		x = x - 'a' + 'A';

	return x;
}