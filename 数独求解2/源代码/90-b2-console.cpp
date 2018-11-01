/*1550431 计科3班 王甯琪*/
#include "90-b2.h"
//存放控制输出及绘图的函数

void draw_basic_sudoku(point *head, const int X, const int Y, int goxyornot )
{
	//在X,Y处输出简单的数独分布情况
	int i, j, k, color;
	point *pos;

	if (goxyornot)
		gotoxy(hout, X, Y);

	//打印开头
	cout << "-+-";
	for(i=0;i<9;i++)
	{
		cout << char('a' + i);
		cout << '-';

		if ((i + 1) % 3 == 0&&i!=8)
			cout << "+-";
	}
	cout << '\n';

	for (i = 1; i <= 9; i++)
	{
		setcolor(hout, COLOR_BLACK, COLOR_WHITE);
		cout << i<< '|';
		for (j = 1; j <= 3; j++)
		{
			cout << ' ';
			for (k = 1; k <= 3; k++)
			{
				pos = (head + 9 * (i - 1) + 3 * (j - 1) + k - 1);
				if (pos->changable)
					color = 14;
				else
					color = 9;

				if (pos->conflict)
					color = 10;

				setcolor(hout, pos->highlight ? 6:0, color );
				cout << pos->value<<' ';
				setcolor(hout, COLOR_BLACK, COLOR_WHITE);
			}

			if (j < 3)
			{
				setcolor(hout, COLOR_BLACK, COLOR_WHITE);
				cout << '|';
			}
		}
		cout << '\n';

		if (i == 3 || i == 6)
		{
			setcolor(hout, COLOR_BLACK, COLOR_WHITE); 
			cout << "-+-------+-------+-------\n";
		}
	}

	cout << '\n';
	setcolor(hout, COLOR_BLACK, COLOR_WHITE);

}

void draw_file_choice(const int X,const int Y,const int from,const int highlight, char file_name[100][50])//输出可选文件菜单
{
	int k;

	gotoxy(hout, X, Y);
	cout << "数独样本文件";
	gotoxy(hout, X, Y + 1);
	cout << "╔═══════════════╗";
	for (k = 1; k <= 8; k++)//一次显示8个文件
	{
		gotoxy(hout, X, Y + 1 + k);
		cout << "║                              ║";
	}
	gotoxy(hout, X, Y + 10);
	cout << "╚═══════════════╝";

	for (k = 1; k <= 8; k++)//一次显示8个文件
	{
		gotoxy(hout, X + 2, Y + 1 + k);
		if (k == highlight)
		{
			setcolor(hout, 7, 0);
			cout << file_name[from + k - 2];
			setcolor(hout, COLOR_BLACK, COLOR_WHITE);
		}
		else
			cout << file_name[from + k - 2];
	}
}

void draw_complex_sudoku(point *head, const int X, const int Y, int goxyornot)
{
	//在X,Y处输出图形化的数独分布情况
	int i,j,color;
	point *pos;

	if (goxyornot)
		gotoxy(hout, X, Y);

	//1 代表列的字母(a-i)输出在(X+6*j-2,Y)
	//2代表行的数字(1-9)输出在(X,Y+3*i-1)
	//3 i行j列的方框左上角坐标是(X+2+(j-1)*6,Y+3*i-2)

	//1
	for(j=1;j<=9;j++)
	{
		gotoxy(hout, X + 6 * j - 2, Y);
		cout << char('a' + j - 1);
	}

	//2
	for(i=1;i<=9;i++)
	{
		gotoxy(hout, X, Y + 3 * i - 1);
		cout << i;
	}

	//3
	for(i=1;i<=9;i++)
	{
		for(j=1;j<=9;j++)
		{
			pos = head + 9 * (i - 1) + j - 1;
			if (pos->changable)
				color = 14;
			else
				color = 9;

			if (pos->conflict)
				color = 10;

			setcolor(hout, pos->highlight ? 6 : 0, color);
			gotoxy(hout, X + 2 + (j - 1) * 6, Y + 3 * i - 2);
			cout << "╔═╗";
			gotoxy(hout, X + 2 + (j - 1) * 6, Y + 3 * i - 1);
			cout << "║" << pos->value<<" ║";
			gotoxy(hout, X + 2 + (j - 1) * 6, Y + 3 * i );
			cout << "╚═╝";
		}
	}

	setcolor(hout, COLOR_BLACK, COLOR_WHITE);
	gotoxy(hout, X, Y + 29);
}

void output_res(char *res,char *last_move, const int X, const int Y, int goxyornot )//在X,Y处输出移动后的提示
{
	if (goxyornot)
	{
		if(strlen(last_move))
		{
			gotoxy(hout, X, Y + 30);
			cout <<"上次输入:"<< last_move;
		}

		gotoxy(hout, X, Y + 31);
	}

	cout << res<<endl;
}