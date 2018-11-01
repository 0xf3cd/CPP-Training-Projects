/*1550431 计科3班 王甯琪*/
#include "90-b1.h"
//存放工具函数以及公用的函数

int panduan(const int X, const int Y, char *note, const int xiao, const int da)//note表示提示输入的字符串
{
	int n = 0;
	char x;

	while (1)
	{
		showcinwrong(X, Y, note, "");//清除之前错误输入留下的输入信息

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
			cout << "非法输入，请重新输入";
			n = 0;
		}
		else
			break;//没有不合法字符，并且最后的值介于xiao,da之间则退出。
	}

	gotoxy(hout, X, Y + 1);
	cout << "                      ";//消除之前可能出现的非法输入提示

	return n;
}

void showcinwrong(int X, int Y, char *note, char *noteofwrong)//提示输入错误,并让光标回复到(X,Y),再次输出结束本小题的提示
{
	gotoxy(hout, X, Y);
	cout << note << "                                    \n";//消除之前的输入记录
	cout << noteofwrong;
	gotoxy(hout, X, Y);
	cout << note;
}

int randomly_return_color()//随机返回1-9，代表9种颜色
{
	return (rand() % 9 + 1);
}

void end_until_end(int X, int Y, char *note, int goxyornot)//在坐标(X,Y)处输出结束本小题的提示,输入end时跳出分枝,默认转移至(X,Y)
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
	if (itshouldbefrom >= 'a'&&itshouldbefrom <= 'z')//如果输入时字母，需忽略大小写
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

char capitalize(char c)//输出字母的大写
{
	if (c >= 'a'&&c <= 'z')
		return c - 'a' + 'A';

	return c;
}

void wait_an_enter()//等待回车键
{
	while (1)
	{
		if (_getch() == '\r')
			break;
	}
}

int sum_up_highlight(point *const first, const int h, const int l)//返回被标记的球的个数
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

int how_many_highlighted_upwards(point *const from, const int rest_balls)//统计从某点向上所有连续被标亮的点
{
	int i, counts = 0;
	point *p = from;

	for (i = 1; i <= rest_balls; i++)
	{
		if (p->highlight)
			counts++;
		else
			break;

		p -= l_max;//指向上面一个球
	}

	return counts;
}

void keys_highlight(point * const first, const int h, const int l)//找出所有彩球对 （,which 互换后能消除得分）（非限制性定语从句）
{
	point *p, *tem;
	int i, j, color_t;

	//先检查左右互换
	for (i = 0; i < h; i++)
	{
		p = first + i*l_max;
		for (j = 0; j < l - 1; j++)
		{
			tem = p + 1;
			//尝试交换
			color_t = p->color;
			p->color = tem->color;
			tem->color = color_t;

			if (find_removable_points(first, h, l))//发现可消除的球
			{
				p->key_highlight = 1;
				tem->key_highlight = 1;
			}
			all_highlight_set_0(first, h, l);
			all_score_set_0(first, h, l);

			//别忘了换回来！！！！！
			color_t = p->color;
			p->color = tem->color;
			tem->color = color_t;

			p++;
		}
	}

	//后检查上下互换
	for (i = 0; i < h - 1; i++)
	{
		p = first + i*l_max;
		for (j = 0; j < l; j++)
		{
			tem = p + l_max;
			//尝试交换
			color_t = p->color;
			p->color = tem->color;
			tem->color = color_t;

			if (find_removable_points(first, h, l))//发现可消除的球
			{
				p->key_highlight = 1;
				tem->key_highlight = 1;
			}
			all_highlight_set_0(first, h, l);
			all_score_set_0(first, h, l);

			//别忘了换回来！！！！！
			color_t = p->color;
			p->color = tem->color;
			tem->color = color_t;

			p++;
		}
	}
}

int whether_after_move_get_score(point *const first, const int fh, const int fl, const int th, const int tl, const int h, const int l)//判断两个球交换后，是否带来得分
{
	//返回0代表找到了相邻的合法球对，返回1代表所选的相邻球交换后不能带来消除
	point *pf, *pt;
	int color_t;

	pf = first + fl - 1 + l_max*(fh - 1);
	pt = first + tl - 1 + l_max*(th - 1);

	//交换颜色
	color_t = pf->color;
	pf->color = pt->color;
	pt->color = color_t;

	if (find_removable_points(first, h, l))
	{
		//消除判断交换后是否有得分过程中产生的影响
		all_highlight_set_0(first, h, l);
		all_score_set_0(first, h, l);

		//不用换回来
		//color_t = pf->color;
		//pf->color = pt->color;
		//pt->color = color_t;

		return 0;
	}
	else
	{
		//换回来
		color_t = pf->color;
		pf->color = pt->color;
		pt->color = color_t;

		return 1;
	}
}

int game_over(point *const first, const int h, const int l)//判断游戏是否结束,返回0代表结束
{
	point *p, *tem;
	int i, j, color_t, counts = 0;

	//先检查左右互换
	for (i = 0; i < h; i++)
	{
		p = first + i*l_max;
		for (j = 0; j < l - 1; j++)
		{
			tem = p + 1;
			//尝试交换
			color_t = p->color;
			p->color = tem->color;
			tem->color = color_t;

			if (find_removable_points(first, h, l))//发现可消除的球
			{
				p->key_highlight = 1;
				tem->key_highlight = 1;
				counts++;
			}
			all_highlight_set_0(first, h, l);
			all_score_set_0(first, h, l);

			//别忘了换回来！！！！！
			color_t = p->color;
			p->color = tem->color;
			tem->color = color_t;

			p++;
		}
	}

	//后检查上下互换
	for (i = 0; i < h - 1; i++)
	{
		p = first + i*l_max;
		for (j = 0; j < l; j++)
		{
			tem = p + l_max;
			//尝试交换
			color_t = p->color;
			p->color = tem->color;
			tem->color = color_t;

			if (find_removable_points(first, h, l))//发现可消除的球
			{
				p->key_highlight = 1;
				tem->key_highlight = 1;
				counts++;
			}
			all_highlight_set_0(first, h, l);
			all_score_set_0(first, h, l);

			//别忘了换回来！！！！！
			color_t = p->color;
			p->color = tem->color;
			tem->color = color_t;

			p++;
		}
	}

	return counts;
}