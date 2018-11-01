/*1550431 �ƿ�3�� �����*/
#include "90-b1.h"
//��Ź��ߺ����Լ����õĺ���

int panduan(const int X, const int Y, char *note, const int xiao, const int da)//note��ʾ��ʾ������ַ���
{
	int n = 0;
	char x;

	while (1)
	{
		showcinwrong(X, Y, note, "");//���֮ǰ�����������µ�������Ϣ

		cin >> x;
		while (1)
		{
			if (x == '\n')
				break;

			if (int(x) > 57 || int(x) < 48)
			{
				cin.clear();
				cin.ignore(1024, '\n');
				showcinwrong(X, Y, note);
				n = 0;
				cin >> x;
				continue;
			}
			else
				n = n * 10 + (int(x) - 48);

			x = char(getchar());
		}

		if (n < xiao || n > da)
		{
			cout << "�Ƿ����룬����������";
			n = 0;
		}
		else
			break;//û�в��Ϸ��ַ�����������ֵ����xiao,da֮�����˳���
	}

	gotoxy(hout, X, Y + 1);
	cout << "                      ";//����֮ǰ���ܳ��ֵķǷ�������ʾ

	return n;
}

void showcinwrong(int X, int Y, char *note, char *noteofwrong)//��ʾ�������,���ù��ظ���(X,Y),�ٴ����������С�����ʾ
{
	gotoxy(hout, X, Y);
	cout << note << "                                    \n";//����֮ǰ�������¼
	cout << noteofwrong;
	gotoxy(hout, X, Y);
	cout << note;
}

int randomly_return_color()//�������1-9������9����ɫ
{
	return (rand() % 9 + 1);
}

void end_until_end(int X, int Y, char *note, int goxyornot)//������(X,Y)�����������С�����ʾ,����endʱ������֦,Ĭ��ת����(X,Y)
{
	int last_x, last_y;
	char c1, c2, c3, c;

	if (goxyornot)
		gotoxy(hout, X, Y);
	else
		cout << '\n';

	getxy(hout, last_x, last_y);
	cout << note;
	while (1)
	{
		cin >> c1;
		if (!check_if_a_char_ok(c1, note, 'e', 'e'))
		{
			showcinwrong(last_x, last_y, note);
			continue;
		}

		c2 = char(getchar());
		if (!check_if_a_char_ok(c2, note, 'n', 'n'))
		{
			showcinwrong(last_x, last_y, note);
			continue;
		}

		c3 = char(getchar());
		if (!check_if_a_char_ok(c3, note, 'd', 'd'))
		{
			showcinwrong(last_x, last_y, note);
			continue;
		}

		c = char(getchar());
		if (c != '\n')
		{
			cin.clear();
			cin.ignore(1024, '\n');
			showcinwrong(last_x, last_y, note);
			continue;
		}

		break;
	}
}


int check_if_a_char_ok(char c, char *note, char itshouldbefrom, char itshouldbeto)
{
	char ought;

	if (c == '\n')
	{
		return 0;
	}
	for (ought = itshouldbefrom; ought <= itshouldbeto; ought++)
	{
		if (c == ought)
			return 1;
	}
	if (itshouldbefrom >= 'a'&&itshouldbefrom <= 'z')//�������ʱ��ĸ������Դ�Сд
	{
		for (ought = capitalize(itshouldbefrom); ought <= capitalize(itshouldbeto); ought++)
		{
			if (c == ought)
				return 1;
		}
	}

	cin.clear();
	cin.ignore(1024, '\n');
	return 0;
}

char capitalize(char c)//�����ĸ�Ĵ�д
{
	if (c >= 'a'&&c <= 'z')
		return c - 'a' + 'A';

	return c;
}

void wait_an_enter()//�ȴ��س���
{
	while (1)
	{
		if (_getch() == '\r')
			break;
	}
}

int sum_up_highlight(point *const first, const int h, const int l)//���ر���ǵ���ĸ���
{
	int i, j, counts = 0;
	point *p;

	for (i = 0; i < h; i++)
	{
		p = first + l_max*i;
		for (j = 0; j < l; j++)
		{
			if (p->highlight)
				counts++;

			p++;
		}
	}

	return counts;
}

int how_many_highlighted_upwards(point *const from, const int rest_balls)//ͳ�ƴ�ĳ���������������������ĵ�
{
	int i, counts = 0;
	point *p = from;

	for (i = 1; i <= rest_balls; i++)
	{
		if (p->highlight)
			counts++;
		else
			break;

		p -= l_max;//ָ������һ����
	}

	return counts;
}

void keys_highlight(point * const first, const int h, const int l)//�ҳ����в���� ��,which �������������÷֣����������Զ���Ӿ䣩
{
	point *p, *tem;
	int i, j, color_t;

	//�ȼ�����һ���
	for (i = 0; i < h; i++)
	{
		p = first + i*l_max;
		for (j = 0; j < l - 1; j++)
		{
			tem = p + 1;
			//���Խ���
			color_t = p->color;
			p->color = tem->color;
			tem->color = color_t;

			if (find_removable_points(first, h, l))//���ֿ���������
			{
				p->key_highlight = 1;
				tem->key_highlight = 1;
			}
			all_highlight_set_0(first, h, l);
			all_score_set_0(first, h, l);

			//�����˻���������������
			color_t = p->color;
			p->color = tem->color;
			tem->color = color_t;

			p++;
		}
	}

	//�������»���
	for (i = 0; i < h - 1; i++)
	{
		p = first + i*l_max;
		for (j = 0; j < l; j++)
		{
			tem = p + l_max;
			//���Խ���
			color_t = p->color;
			p->color = tem->color;
			tem->color = color_t;

			if (find_removable_points(first, h, l))//���ֿ���������
			{
				p->key_highlight = 1;
				tem->key_highlight = 1;
			}
			all_highlight_set_0(first, h, l);
			all_score_set_0(first, h, l);

			//�����˻���������������
			color_t = p->color;
			p->color = tem->color;
			tem->color = color_t;

			p++;
		}
	}
}

int whether_after_move_get_score(point *const first, const int fh, const int fl, const int th, const int tl, const int h, const int l)//�ж������򽻻����Ƿ�����÷�
{
	//����0�����ҵ������ڵĺϷ���ԣ�����1������ѡ�������򽻻����ܴ�������
	point *pf, *pt;
	int color_t;

	pf = first + fl - 1 + l_max*(fh - 1);
	pt = first + tl - 1 + l_max*(th - 1);

	//������ɫ
	color_t = pf->color;
	pf->color = pt->color;
	pt->color = color_t;

	if (find_removable_points(first, h, l))
	{
		//�����жϽ������Ƿ��е÷ֹ����в�����Ӱ��
		all_highlight_set_0(first, h, l);
		all_score_set_0(first, h, l);

		//���û�����
		//color_t = pf->color;
		//pf->color = pt->color;
		//pt->color = color_t;

		return 0;
	}
	else
	{
		//������
		color_t = pf->color;
		pf->color = pt->color;
		pt->color = color_t;

		return 1;
	}
}

int game_over(point *const first, const int h, const int l)//�ж���Ϸ�Ƿ����,����0�������
{
	point *p, *tem;
	int i, j, color_t, counts = 0;

	//�ȼ�����һ���
	for (i = 0; i < h; i++)
	{
		p = first + i*l_max;
		for (j = 0; j < l - 1; j++)
		{
			tem = p + 1;
			//���Խ���
			color_t = p->color;
			p->color = tem->color;
			tem->color = color_t;

			if (find_removable_points(first, h, l))//���ֿ���������
			{
				p->key_highlight = 1;
				tem->key_highlight = 1;
				counts++;
			}
			all_highlight_set_0(first, h, l);
			all_score_set_0(first, h, l);

			//�����˻���������������
			color_t = p->color;
			p->color = tem->color;
			tem->color = color_t;

			p++;
		}
	}

	//�������»���
	for (i = 0; i < h - 1; i++)
	{
		p = first + i*l_max;
		for (j = 0; j < l; j++)
		{
			tem = p + l_max;
			//���Խ���
			color_t = p->color;
			p->color = tem->color;
			tem->color = color_t;

			if (find_removable_points(first, h, l))//���ֿ���������
			{
				p->key_highlight = 1;
				tem->key_highlight = 1;
				counts++;
			}
			all_highlight_set_0(first, h, l);
			all_score_set_0(first, h, l);

			//�����˻���������������
			color_t = p->color;
			p->color = tem->color;
			tem->color = color_t;

			p++;
		}
	}

	return counts;
}