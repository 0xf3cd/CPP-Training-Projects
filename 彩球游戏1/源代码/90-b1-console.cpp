/*1550431 �ƿ�3�� �����*/
#include "90-b1.h"
//��ſ����������ͼ�ĺ���

void draw_basic_map(const int X, const int Y, point *const first, int h, int l, int gotoxyornot, int show_highlight)
{
	int i, j;
	point *p = first;
	if (gotoxyornot == 1)
		gotoxy(hout, X, Y);
	else
		cout << "\n";

	cout << "  |";//��һ�����
	for (i = 1; i <= l; i++)
	{
		cout << "  ";
		cout << i;
	}
	cout << " \n";

	cout << "--+";//�ڶ������
	for (i = 1; i <= 3 * l + 1; i++)
	{
		cout << '-';
	}
	cout << '\n';

	if (show_highlight)
	{
		for (i = 0; i < h; i++)//ʣ�µ����
		{
			p = first + i*l_max;//ָ���i+1��
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

				p++;//ָ��֮���һ����
			}
			cout << '\n';
		}
	}
	else
	{
		for (i = 0; i < h; i++)//ʣ�µ����
		{
			p = first + i*l_max;//ָ���i+1��
			cout << char('A' + i) << " |";
			for (j = 0; j < l; j++)
			{
				cout << "  ";
				cout << p->color;

				p++;//ָ��֮���һ����
			}
			cout << '\n';
		}
	}
}

void draw_primary_map(point *const first, const int X, const int Y, const int h, const int l)//��������ͼ�Σ��޷ָ���
{
	int i, j;
	point *p;

	gotoxy(hout, X, Y);
	setcolor(hout, 15, 0);
	cout << "�X";//��һ�����
	for (i = 1; i <= l; i++)
	{
		cout << "�T";
	}
	cout << "�[\n";

	for (i = 1; i <= h; i++)//�м䲿�����
	{
		p = first + l_max*(i - 1);
		gotoxy(hout, X, Y + i);
		cout << "�U";
		for (j = 1; j <= l; j++)
		{
			setcolor(hout, p->color + 5, 0);
			cout << "��";
			p++;
		}
		setcolor(hout, 15, 0);
		cout << "�U\n";
	}

	gotoxy(hout, X, Y + h + 1);//�ƶ������һ�е�λ��
	setcolor(hout, 15, 0);
	cout << "�^";//���һ�����
	for (i = 1; i <= l; i++)
	{
		cout << "�T";
	}
	cout << "�a\n";

	setcolor(hout, COLOR_BLACK, COLOR_WHITE);
}

void draw_complex_map(point * const first, const int X, const int Y, const int h, const int l)//��������ͼ��
{
	int i, j;
	point *p;

	gotoxy(hout, X, Y);
	setcolor(hout, 15, 0);
	cout << "�X";//��һ�����
	for (i = 1; i <= l - 1; i++)
	{
		cout << "�T�h";
	}
	cout << "�T�[\n";

	for (i = 1; i <= h - 1; i++)//�м䲿�ֵİ׵����
	{
		gotoxy(hout, X, Y - 1 + 2 * i);
		cout << "�U";
		for (j = 1; j <= l - 1; j++)
		{
			cout << "  ��";
		}
		cout << "  �U\n";

		gotoxy(hout, X, Y + 2 * i);
		cout << "�c";
		for (j = 1; j <= l - 1; j++)
		{
			cout << "����";
		}
		cout << "���f\n";
	}

	{//�����һ�пհ����
		gotoxy(hout, X, Y + 2 * h - 1);
		cout << "�U";
		for (j = 1; j <= l - 1; j++)
		{
			cout << "  ��";
		}
		cout << "  �U\n";
	}

	for (i = 1; i <= h; i++)//�м䲿�ֵ����
	{
		p = first + l_max*(i - 1);
		for (j = 1; j <= l; j++)
		{
			gotoxy(hout, X + 4 * j - 2, Y + 2 * i - 1);
			if (p->color)
			{
				setcolor(hout, p->color + 5, 0);
				cout << "��";
			}
			else
			{
				setcolor(hout, 15, 0);
				cout << "  ";
			}
			p++;
		}
	}

	gotoxy(hout, X, Y + 2 * h);//�ƶ������һ�е�λ��
	setcolor(hout, 15, 0);
	cout << "�^";//���һ�����
	for (i = 1; i <= l - 1; i++)
	{
		cout << "�T�k";
	}
	cout << "�T�a\n";

	setcolor(hout, COLOR_BLACK, COLOR_WHITE);
}

void turn_emptyball_to_fullball(point * const first, const int X, const int Y, const int h, const int l)//��highlight=1�Ŀ������ʵ����
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
				cout << "��";
			}
			p++;
		}
	}

	setcolor(hout, COLOR_BLACK, COLOR_WHITE);
}

void draw_remove_points(point *const first, const int X, const int Y, const int h, const int l)//��downwards��Ϊ0����ɾ������ʾ����
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
				cout << "��";
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
void draw_move_points(point *first, const int X, const int Y, const int h, const int l)//��������
{
	point *p,*tp;
	int i, j,k, removable;

	for (i = h - 1; i >= 0; i--)//���¶��ϣ��������
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

void draw_move_downwards(point *const first, const int h, const int l, const int X, const int Y)//��pָ�����������������򣬹�amount���������ƶ�spaces��λ�ã���ʾ����,(x,y)Ϊp����
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

void draw_move_a_point(const int color, const int fx, const int fy, const int tx, const int ty)//��̬��ʾ��һ�����(fx,fy)->(tx,ty)
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
		cout << "��";
		Sleep(15);
		gotoxy(hout, fx, i + 1);
		setcolor(hout, 15, 0);
		cout << "����";
		gotoxy(hout, fx, i + 2);
		setcolor(hout, color + 5, 0);
		cout << "��";
		Sleep(15);
	}

	setcolor(hout, COLOR_BLACK, COLOR_WHITE);
}

void draw_fill_empty_points(point *const first, const int X, const int Y, const int h, const int l)//�����ȱλ�ã���ʾ��̬
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
				cout << "��";
			}
			p++;
		}
	}

	setcolor(hout, COLOR_BLACK, COLOR_WHITE);
}

void draw_keys_highlight_points(point *const first, const int X, const int Y, const int h, const int l)//��ʾ������ʾ
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
				cout << "��";
			}
			p++;
		}
	}

	setcolor(hout, COLOR_BLACK, COLOR_WHITE);
}

void show_mouse_position(const int last_x, const int last_y, char mouseh, char mousel)//��(last_x,last_y),�������̺�һ�д�����������λ��
{
	gotoxy(hout, last_x, last_y);
	cout << "                                                        ";
	gotoxy(hout, last_x, last_y);
	cout << "��ǰλ�ã�" << mouseh << "��" << mousel << "��";
}

void show_scores_gotten(point *const first, const int X, const int Y, const int h, const int l)//��������һ�ţ�ע�⣡��������һ�ţ��������������������������
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
	cout << "��ǰ����Ϊ:" << scores << "  �Ҽ��˳�";
}


int from_mouse_get_position(point * const first, const int last_x, const int last_y, const int X, const int Y, const int h, const int l, int &fh, int &fl, int &th, int &tl)//�õ����ٿص��ƶ�������λ��
{
	//�����ض�ֵ-1���������Ҽ�������0�����ҵ������ڵĺϷ���ԣ�����1������ѡ�������򽻻����ܴ�������������������
	point *p;
	int mousex, mousey, mousevalue, px, py;

	while (1)//���Ҫ�ƶ���������
	{
		enable_mouse(hin);
		mousevalue = read_mouse(hin, mousex, mousey);

		if (mousevalue == 3)//�����Ҽ������branch
			return -1;

		if ((mousex = (mousex - X) / 2) % 2 == 1 && (mousey = mousey - Y) % 2 == 1)//�õ�������ڷ����λ�ã����������ߣ�
		{
			mousex = (mousex + 1) / 2;
			mousey = (mousey + 1) / 2;

			if (mousex >= 1 && mousex <= l  && mousey >= 1 && mousey <= h)//��ͼ�������ڣ����߿�
			{
				show_mouse_position(last_x, last_y, 'A' + mousey - 1, '1' + mousex - 1);

				if (mousevalue == FROM_LEFT_1ST_BUTTON_PRESSED)//�����������ͬʱ������
				{
					//���ص�һ��ѡ���������
					fh = mousey;
					fl = mousex;

					//�õ�ѡ�����Ӧ���ڴ��ַ���Լ���cmd�����ж�Ӧ������
					p = first + fl - 1 + l_max*(fh - 1);
					px = X + 4 * fl - 2;
					py = Y + 2 * fh - 1;

					//����ʵ����
					gotoxy(hout, px, py);
					setcolor(hout, p->color + 5, 15);
					cout << "��";
					setcolor(hout, COLOR_BLACK, COLOR_WHITE);

					break;//�õ���λ������ѭ��
				}
			}
		}
	}

	while (1)//�õ�Ŀ������
	{
		enable_mouse(hin);
		mousevalue = read_mouse(hin, mousex, mousey);

		if (mousevalue == 3)//�����Ҽ������branch6
			return -1;

		if ((mousex = (mousex - X) / 2) % 2 == 1 && (mousey = mousey - Y) % 2 == 1)//�õ�������ڷ����λ�ã����������ߣ�
		{
			mousex = (mousex + 1) / 2;
			mousey = (mousey + 1) / 2;

			if (mousex >= 1 && mousex <= l  && mousey >= 1 && mousey <= h)//��ͼ�������ڣ����߿�
			{
				show_mouse_position(last_x, last_y, 'A' + mousey - 1, '1' + mousex - 1);

				//�ж�����
				if (mousevalue == FROM_LEFT_1ST_BUTTON_PRESSED)//�����������ͬʱ������
				{
					th = mousey;
					tl = mousex;

					if ((fh - th == 1) || (fh - th == -1) || (fl - tl == 1) || (fl - tl == -1))//��֮ǰ�������
					{
						//��������������������
						if (whether_after_move_get_score(first, fh, fl, th, tl, h, l) == 0)
							return 0;//���ҵ���������
						//�������
						else
						{
							//����1������һ��
							return 1;
						}
					}
					else//��֮ǰ���������
					{
						return 1;
						/*
						//�õ���ѡ�����Ӧ���ڴ��ַ���Լ���cmd�����ж�Ӧ������
						p = first + mousex - 1 + l_max*(mousey - 1);
						px = X + 4 * mousex - 2;
						py = Y + 2 * mousey - 1;

						//����ʵ����
						gotoxy(hout, px, py);
						setcolor(hout, p->color + 5, 15);
						cout << "��";
						setcolor(hout, COLOR_BLACK, COLOR_WHITE);

						//����fh,fl
						fh = mousey;
						fl = mousex;

						//����ѭ��
						 */
					}
				}
			}
		}
	}
}

void move_2_points(point * const first, const int X, const int Y, const int fh, const int fl, const int th, const int tl, const int h, const int l)//������������
{
	point *pf, *pt;
	int pfx, pfy, ptx, pty;

	pf = first + fl - 1 + l_max*(fh - 1);
	pt = first + tl - 1 + l_max*(th - 1);
	pfx = X + 4 * fl - 2;
	pfy = Y + 2 * fh - 1;
	ptx = X + 4 * tl - 2;
	pty = Y + 2 * th - 1;

	//���½���
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
		cout << "��";

		Sleep(90);
		setcolor(hout, 15, 0);
		gotoxy(hout, ptx, (pty + pfy) / 2);
		cout << "����";

		gotoxy(hout, ptx, pty);
		setcolor(hout, pt->color + 5, 0);
		cout << "��";
		gotoxy(hout, pfx, pfy);
		setcolor(hout, pf->color + 5, 0);
		cout << "��";

		setcolor(hout, COLOR_BLACK, COLOR_WHITE);
	}
	//���ҽ���
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
		cout << "��";

		Sleep(90);
		setcolor(hout, 15, 0);
		gotoxy(hout, (ptx + pfx) / 2, pty);
		cout << " ��";

		gotoxy(hout, ptx, pty);
		setcolor(hout, pt->color + 5, 0);
		cout << "��";
		gotoxy(hout, pfx, pfy);
		setcolor(hout, pf->color + 5, 0);
		cout << "��";

		setcolor(hout, COLOR_BLACK, COLOR_WHITE);
	}
}