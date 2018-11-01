/*1550431 计科3班 王甯琪*/
#include "90-b1.h"
//存放控制输出及绘图的函数

void draw_basic_map(const int X, const int Y, point *const first, int h, int l, int gotoxyornot, int show_highlight)
{
	int i, j;
	point *p = first;
	if (gotoxyornot == 1)
		gotoxy(hout, X, Y);
	else
		cout << "\n";

	cout << "  |";//第一排输出
	for (i = 1; i <= l; i++)
	{
		cout << "  ";
		cout << i;
	}
	cout << " \n";

	cout << "--+";//第二排输出
	for (i = 1; i <= 3 * l + 1; i++)
	{
		cout << '-';
	}
	cout << '\n';

	if (show_highlight)
	{
		for (i = 0; i < h; i++)//剩下的输出
		{
			p = first + i*l_max;//指向第i+1行
			cout << char('A' + i) << " |";
			for (j = 0; j < l; j++)
			{
				cout << "  ";
				if (p->highlight == 1 || p->color == 0 || p->key_highlight == 1)
				{
					setcolor(hout, 13, 11);
					cout << p->color;
					setcolor(hout, COLOR_BLACK, COLOR_WHITE);
				}
				else
					cout << p->color;

				p++;//指向之后的一个球
			}
			cout << '\n';
		}
	}
	else
	{
		for (i = 0; i < h; i++)//剩下的输出
		{
			p = first + i*l_max;//指向第i+1行
			cout << char('A' + i) << " |";
			for (j = 0; j < l; j++)
			{
				cout << "  ";
				cout << p->color;

				p++;//指向之后的一个球
			}
			cout << '\n';
		}
	}
}

void draw_primary_map(point *const first, const int X, const int Y, const int h, const int l)//画出基本图形，无分割线
{
	int i, j;
	point *p;

	gotoxy(hout, X, Y);
	setcolor(hout, 15, 0);
	cout << "╔";//第一排输出
	for (i = 1; i <= l; i++)
	{
		cout << "═";
	}
	cout << "╗\n";

	for (i = 1; i <= h; i++)//中间部分输出
	{
		p = first + l_max*(i - 1);
		gotoxy(hout, X, Y + i);
		cout << "║";
		for (j = 1; j <= l; j++)
		{
			setcolor(hout, p->color + 5, 0);
			cout << "〇";
			p++;
		}
		setcolor(hout, 15, 0);
		cout << "║\n";
	}

	gotoxy(hout, X, Y + h + 1);//移动到最后一行的位置
	setcolor(hout, 15, 0);
	cout << "╚";//最后一排输出
	for (i = 1; i <= l; i++)
	{
		cout << "═";
	}
	cout << "╝\n";

	setcolor(hout, COLOR_BLACK, COLOR_WHITE);
}

void draw_complex_map(point * const first, const int X, const int Y, const int h, const int l)//画出完整图形
{
	int i, j;
	point *p;

	gotoxy(hout, X, Y);
	setcolor(hout, 15, 0);
	cout << "╔";//第一排输出
	for (i = 1; i <= l - 1; i++)
	{
		cout << "═╤";
	}
	cout << "═╗\n";

	for (i = 1; i <= h - 1; i++)//中间部分的白底输出
	{
		gotoxy(hout, X, Y - 1 + 2 * i);
		cout << "║";
		for (j = 1; j <= l - 1; j++)
		{
			cout << "  │";
		}
		cout << "  ║\n";

		gotoxy(hout, X, Y + 2 * i);
		cout << "╟";
		for (j = 1; j <= l - 1; j++)
		{
			cout << "─┼";
		}
		cout << "─╢\n";
	}

	{//最底下一行空白输出
		gotoxy(hout, X, Y + 2 * h - 1);
		cout << "║";
		for (j = 1; j <= l - 1; j++)
		{
			cout << "  │";
		}
		cout << "  ║\n";
	}

	for (i = 1; i <= h; i++)//中间部分的输出
	{
		p = first + l_max*(i - 1);
		for (j = 1; j <= l; j++)
		{
			gotoxy(hout, X + 4 * j - 2, Y + 2 * i - 1);
			if (p->color)
			{
				setcolor(hout, p->color + 5, 0);
				cout << "〇";
			}
			else
			{
				setcolor(hout, 15, 0);
				cout << "  ";
			}
			p++;
		}
	}

	gotoxy(hout, X, Y + 2 * h);//移动到最后一行的位置
	setcolor(hout, 15, 0);
	cout << "╚";//最后一排输出
	for (i = 1; i <= l - 1; i++)
	{
		cout << "═╧";
	}
	cout << "═╝\n";

	setcolor(hout, COLOR_BLACK, COLOR_WHITE);
}

void turn_emptyball_to_fullball(point * const first, const int X, const int Y, const int h, const int l)//将highlight=1的空心球变实心球
{
	int i, j;
	point *p;

	for (i = 1; i <= h; i++)
	{
		p = first + l_max*(i - 1);
		for (j = 1; j <= l; j++)
		{
			if (p->highlight)
			{
				gotoxy(hout, X + 4 * j - 2, Y + 2 * i - 1);
				setcolor(hout, p->color + 5, 0);
				cout << "●";
			}
			p++;
		}
	}

	setcolor(hout, COLOR_BLACK, COLOR_WHITE);
}

void draw_remove_points(point *const first, const int X, const int Y, const int h, const int l)//将downwards不为0的球删除，显示动画
{
	point *p = first;
	int i, j;

	for (i = 1; i <= h; i++)
	{
		p = first + l_max*(i - 1);
		for (j = 1; j <= l; j++)
		{
			if (p->highlight)
			{
				Sleep(15);
				gotoxy(hout, X + 4 * j - 2, Y + 2 * i - 1);
				setcolor(hout, p->color + 5, 0);
				cout << "¤";
				Sleep(50);
				gotoxy(hout, X + 4 * j - 2, Y + 2 * i - 1);
				setcolor(hout, 15, 0);
				cout << "  ";
			}
			p++;
		}
	}

	setcolor(hout, COLOR_BLACK, COLOR_WHITE);
}

/*
void draw_move_points(point *first, const int X, const int Y, const int h, const int l)//让球下落
{
	point *p,*tp;
	int i, j,k, removable;

	for (i = h - 1; i >= 0; i--)//由下而上，由左而右
	{
		p = first + l_max*i;
		for (j = 0; j < l; j++)
		{
			if (p->highlight)
			{
				tp = p;
				removable = how_many_highlighted_upwards(p, i + 1);
				for(k=0;k<removable;k++)
				{
					tp->highlight = 0;
					tp -= l_max;
				}
				draw_move_downwards(tp, 4 * j + 2, 2 * i+2-2*removable, i + 1 - removable, removable);

			}

			p++;
		}
	}
}
*/

void draw_move_downwards(point *const first, const int h, const int l, const int X, const int Y)//把p指向的球及其上面的所有球，共amount个，向下移动spaces个位置，显示动画,(x,y)为p坐标
{
	int i, j, k;
	point *p = first;

	for (j = 0; j < l; j++)
	{
		for (i = h - 1; i >= 0; i--)
		{
			if ((p + i*l_max + j)->downwards != 0 && (p + i*l_max + j)->color != 0)
			{
				for (k = 1; k <= (p + i*l_max + j)->downwards; k++)
				{
					draw_move_a_point((p + i*l_max + j)->color, X + 4 * j + 2, Y + 2 * i + 2 * k - 1, X + 4 * j + 2, Y + 2 * i + 1 + 2 * k);
				}

				((p + i*l_max + j) + (p + i*l_max + j)->downwards*l_max)->color = (p + i*l_max + j)->color;
				(p + i*l_max + j)->color = 0;
			}
		}
	}
}

void draw_move_a_point(const int color, const int fx, const int fy, const int tx, const int ty)//动态显示将一个球从(fx,fy)->(tx,ty)
{
	int i;

	for (i = fy; i <= ty - 2; i += 2)
	{
		gotoxy(hout, fx, i);
		setcolor(hout, 15, 0);
		cout << "  ";
		Sleep(15);
		gotoxy(hout, fx, i + 1);
		setcolor(hout, color + 5, 0);
		cout << "〇";
		Sleep(15);
		gotoxy(hout, fx, i + 1);
		setcolor(hout, 15, 0);
		cout << "─┼";
		gotoxy(hout, fx, i + 2);
		setcolor(hout, color + 5, 0);
		cout << "〇";
		Sleep(15);
	}

	setcolor(hout, COLOR_BLACK, COLOR_WHITE);
}

void draw_fill_empty_points(point *const first, const int X, const int Y, const int h, const int l)//补充空缺位置，显示动态
{
	point *p;
	int i, j;

	for (i = 1; i <= h; i++)
	{
		p = first + l_max*(i - 1);
		for (j = 1; j <= l; j++)
		{
			if (p->color == 0)
			{
				Sleep(40);
				p->color = randomly_return_color();
				gotoxy(hout, X + 4 * j - 2, Y + 2 * i - 1);
				setcolor(hout, p->color + 5, 0);
				cout << "〇";
			}
			p++;
		}
	}

	setcolor(hout, COLOR_BLACK, COLOR_WHITE);
}

void draw_keys_highlight_points(point *const first, const int X, const int Y, const int h, const int l)//显示消除提示
{
	point *p;
	int i, j;

	for (i = 0; i < h; i++)
	{
		p = first + l_max*i;
		for (j = 0; j < l; j++)
		{
			if (p->key_highlight)
			{
				Sleep(10);
				gotoxy(hout, X + 4 * j + 2, Y + 2 * i + 1);
				setcolor(hout, p->color + 5, 0);
				cout << "◎";
			}
			p++;
		}
	}

	setcolor(hout, COLOR_BLACK, COLOR_WHITE);
}

void show_mouse_position(const int last_x, const int last_y, char mouseh, char mousel)//在(last_x,last_y),即在球盘后一行处输出鼠标所在位置
{
	gotoxy(hout, last_x, last_y);
	cout << "                                                        ";
	gotoxy(hout, last_x, last_y);
	cout << "当前位置：" << mouseh << "行" << mousel << "列";
}

void show_scores_gotten(point *const first, const int X, const int Y, const int h, const int l)//在球盘上一排，注意！！！！上一排！！！！！！！！！！输出分数
{
	point *p;
	static int scores = 0;
	int i, j;

	for (i = 0; i < h; i++)
	{
		p = first + i*l_max;
		for (j = 0; j < l; j++)
		{
			if (p->score)
			{
				scores += p->score;
				p->score = 0;
			}

			p++;
		}
	}

	gotoxy(hout, X, Y - 1);
	cout << "                                      ";
	gotoxy(hout, X, Y - 1);
	cout << "当前分数为:" << scores << "  右键退出";
}


int from_mouse_get_position(point * const first, const int last_x, const int last_y, const int X, const int Y, const int h, const int l, int &fh, int &fl, int &th, int &tl)//得到鼠标操控的移动的两个位置
{
	//返回特定值-1代表按下了右键，返回0代表找到了相邻的合法球对，返回1代表所选的相邻球交换后不能带来消除或是两球不相邻
	point *p;
	int mousex, mousey, mousevalue, px, py;

	while (1)//获得要移动的球坐标
	{
		enable_mouse(hin);
		mousevalue = read_mouse(hin, mousex, mousey);

		if (mousevalue == 3)//按下右键则结束branch
			return -1;

		if ((mousex = (mousex - X) / 2) % 2 == 1 && (mousey = mousey - Y) % 2 == 1)//得到鼠标所在方格的位置（不包括边线）
		{
			mousex = (mousex + 1) / 2;
			mousey = (mousey + 1) / 2;

			if (mousex >= 1 && mousex <= l  && mousey >= 1 && mousey <= h)//在图形区域内（除边框）
			{
				show_mouse_position(last_x, last_y, 'A' + mousey - 1, '1' + mousex - 1);

				if (mousevalue == FROM_LEFT_1ST_BUTTON_PRESSED)//当鼠标在区域同时左键点击
				{
					//返回第一个选中球的坐标
					fh = mousey;
					fl = mousex;

					//得到选中球对应的内存地址，以及在cmd窗口中对应的坐标
					p = first + fl - 1 + l_max*(fh - 1);
					px = X + 4 * fl - 2;
					py = Y + 2 * fh - 1;

					//画成实心球
					gotoxy(hout, px, py);
					setcolor(hout, p->color + 5, 15);
					cout << "●";
					setcolor(hout, COLOR_BLACK, COLOR_WHITE);

					break;//得到球位则跳出循环
				}
			}
		}
	}

	while (1)//得到目标坐标
	{
		enable_mouse(hin);
		mousevalue = read_mouse(hin, mousex, mousey);

		if (mousevalue == 3)//按下右键则结束branch6
			return -1;

		if ((mousex = (mousex - X) / 2) % 2 == 1 && (mousey = mousey - Y) % 2 == 1)//得到鼠标所在方格的位置（不包括边线）
		{
			mousex = (mousex + 1) / 2;
			mousey = (mousey + 1) / 2;

			if (mousex >= 1 && mousex <= l  && mousey >= 1 && mousey <= h)//在图形区域内（除边框）
			{
				show_mouse_position(last_x, last_y, 'A' + mousey - 1, '1' + mousex - 1);

				//判断相邻
				if (mousevalue == FROM_LEFT_1ST_BUTTON_PRESSED)//当鼠标在区域同时左键点击
				{
					th = mousey;
					tl = mousex;

					if ((fh - th == 1) || (fh - th == -1) || (fl - tl == 1) || (fl - tl == -1))//与之前点击相邻
					{
						//如果两点更换能有球消除
						if (whether_after_move_get_score(first, fh, fl, th, tl, h, l) == 0)
							return 0;//已找到相邻两点
						//如果不能
						else
						{
							//返回1，重来一次
							return 1;
						}
					}
					else//与之前点击不相邻
					{
						return 1;
						/*
						//得到新选中球对应的内存地址，以及在cmd窗口中对应的坐标
						p = first + mousex - 1 + l_max*(mousey - 1);
						px = X + 4 * mousex - 2;
						py = Y + 2 * mousey - 1;

						//画成实心球
						gotoxy(hout, px, py);
						setcolor(hout, p->color + 5, 15);
						cout << "●";
						setcolor(hout, COLOR_BLACK, COLOR_WHITE);

						//更改fh,fl
						fh = mousey;
						fl = mousex;

						//重新循环
						 */
					}
				}
			}
		}
	}
}

void move_2_points(point * const first, const int X, const int Y, const int fh, const int fl, const int th, const int tl, const int h, const int l)//动画交换两球
{
	point *pf, *pt;
	int pfx, pfy, ptx, pty;

	pf = first + fl - 1 + l_max*(fh - 1);
	pt = first + tl - 1 + l_max*(th - 1);
	pfx = X + 4 * fl - 2;
	pfy = Y + 2 * fh - 1;
	ptx = X + 4 * tl - 2;
	pty = Y + 2 * th - 1;

	//上下交换
	if ((pf - pt == l_max) || (pt - pf == l_max))
	{
		Sleep(90);
		setcolor(hout, 15, 0);
		gotoxy(hout, ptx, pty);
		cout << "  ";
		gotoxy(hout, pfx, pfy);
		cout << "  ";

		gotoxy(hout, ptx, (pty + pfy) / 2);
		setcolor(hout, pf->color + 5, 0);
		cout << "〇";

		Sleep(90);
		setcolor(hout, 15, 0);
		gotoxy(hout, ptx, (pty + pfy) / 2);
		cout << "─┼";

		gotoxy(hout, ptx, pty);
		setcolor(hout, pt->color + 5, 0);
		cout << "〇";
		gotoxy(hout, pfx, pfy);
		setcolor(hout, pf->color + 5, 0);
		cout << "〇";

		setcolor(hout, COLOR_BLACK, COLOR_WHITE);
	}
	//左右交换
	else
	{
		Sleep(90);
		setcolor(hout, 15, 0);
		gotoxy(hout, ptx, pty);
		cout << "  ";
		gotoxy(hout, pfx, pfy);
		cout << "  ";

		gotoxy(hout, (ptx + pfx) / 2, pty);
		setcolor(hout, pf->color + 5, 0);
		cout << "〇";

		Sleep(90);
		setcolor(hout, 15, 0);
		gotoxy(hout, (ptx + pfx) / 2, pty);
		cout << " │";

		gotoxy(hout, ptx, pty);
		setcolor(hout, pt->color + 5, 0);
		cout << "〇";
		gotoxy(hout, pfx, pfy);
		setcolor(hout, pf->color + 5, 0);
		cout << "〇";

		setcolor(hout, COLOR_BLACK, COLOR_WHITE);
	}
}