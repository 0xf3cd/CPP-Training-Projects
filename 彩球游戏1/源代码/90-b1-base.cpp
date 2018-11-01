/*1550431 计科3班 王甯琪*/
#include "90-b1.h"
//存放对记录球盘进行统计、操作的函数

void randomly_generate_map(point * const first, const int h, const int l)//在一定范围内的随机初始化颜色
{
	int i, j;
	point *p;

	srand(unsigned(time(NULL)));
	for (i = 0; i < h; i++)
	{
		p = first + l_max*i;//指向第i行首个元素
		for (j = 0; j < l; j++)
		{
			p->color = randomly_return_color();
			p++;//指向后一个元素
		}
	}
}

int find_removable_points(point * const first, const int h, const int l)//找到可以消除的球，返回数量，将成员highlight置1，并标记得分情况
{
	int i, j;
	point *p;

	for (i = 0; i <= h - 3; i++)//寻找竖向同色球
	{
		p = first + l_max*i;
		for (j = 0; j < l; j++)
		{
			if (p->highlight == 0)//未被标记时,寻找同色球
				how_many_same_color(1, p, h - i);

			p++;
		}
	}

	for (i = 0; i < h; i++)//寻找横向同色球
	{
		p = first + l_max*i;
		for (j = 0; j <= l - 3; j++)
		{
			if (p->highlight == 0)//未被标记时,寻找同色球
				how_many_same_color(2, p, l - j);

			p++;
		}
	}

	return sum_up_highlight(first, h, l);//返回被标记的球的个数
}

int how_many_same_color(int direction, point *const from, const int rest_balls)//从from指向的球开始，1、2分别 refers to 下、右，返回值为找到的同色球个数（小于等于3返回0），符合要求则同时标记
{
	int counts = 0, i, color;
	point *p = from;

	if (direction == 1)//竖向
	{
		color = p->color;

		for (i = 1; i <= rest_balls; i++)
		{
			if (p->color == color)
				counts++;
			else
				break;

			p = p + l_max;//指向这一列的下一个球
		}

		if (counts >= 3)//如若发现竖向连续三个及以上同色球，则进行标记
		{
			p = from;
			for (i = 1; i <= counts; i++)
			{
				p->highlight = 1;
				p->score++;
				p = p + l_max;
			}

			return counts;
		}
	}

	if (direction == 2)//横向
	{
		color = p->color;

		for (i = 1; i <= rest_balls; i++)
		{
			if (p->color == color)
				counts++;
			else
				break;

			p = p + 1;//指向这一行的下一个球
		}

		if (counts >= 3)//如若发现横向连续三个及以上同色球，则进行标记
		{
			p = from;
			for (i = 1; i <= counts; i++)
			{
				p->highlight = 1;
				p->score++;
				p = p + 1;
			}

			return counts;
		}
	}

	return 0;
}

void move_points(point *const first, const int h, const int l)//消除同色的，并下落
{
	point *p;
	int i, j, removable;

	for (i = h - 1; i >= 0; i--)//由下而上，由左而右
	{
		p = first + l_max*i;
		for (j = 0; j < l; j++)
		{
			if (p->highlight)
			{
				removable = how_many_highlighted_upwards(p, i + 1);
				move_downwards(p - removable*l_max, i + 1 - removable, removable);
			}

			p++;
		}
	}
}

void move_downwards(point *const p, const int amount, const int spaces)//把p指向的球及其上面的所有球，共amount个，向下移动spaces个位置
{
	int i;
	point *now = p;//now refers to the point now being operated

	for (i = 0; i < amount; i++)//下移
	{
		(now + spaces*l_max)->highlight = now->highlight;
		(now + spaces*l_max)->color = now->color;

		now -= l_max;//指向上移
	}

	now = p - (amount - 1)*l_max;//now points to the first ball of the 列
	for (i = 0; i < spaces; i++)//将空出的位置置0
	{
		now->color = 0;
		now->highlight = 0;

		now += l_max;//指向下移
	}
}

void fill_empty_points(point *const first, const int h, const int l)//填充空位
{
	int i, j;
	point *p;

	srand(unsigned(time(NULL)));
	for (i = 0; i < h; i++)
	{
		p = first + i*l_max;
		for (j = 0; j < l; j++)
		{
			if (p->color == 0)
			{
				p->highlight = 1;
				p->color = randomly_return_color();
			}

			p++;
		}
	}
}

void all_highlight_set_0(point *const first, const int h, const int l)//所有位置highlight置零
{
	int i, j;
	point *p;

	for (i = 0; i < h; i++)
	{
		p = first + i*l_max;
		for (j = 0; j < l; j++)
		{
			p->highlight = 0;
			p++;
		}
	}
}

void all_key_highlight_set_0(point *const first, const int h, const int l)//所有位置key_highlight置零
{
	int i, j;
	point *p;

	for (i = 0; i < h; i++)
	{
		p = first + i*l_max;
		for (j = 0; j < l; j++)
		{
			p->key_highlight = 0;
			p++;
		}
	}
}

void all_downwards_set_0(point *const first, const int h, const int l)//所有位置downwards置零
{
	int i, j;
	point *p;

	for (i = 0; i < h; i++)
	{
		p = first + i*l_max;
		for (j = 0; j < l; j++)
		{
			p->downwards = 0;
			p++;
		}
	}
}

void sum_up_downwards(point*first, const int h, const int l)//将所有球的downwards属性标记上
{
	point *p = first;
	int i, j, k;

	for (i = h - 1; i >= 0; i--)
	{
		for (j = 0; j < l; j++)
		{
			if ((p + i*l_max + j)->highlight)
			{
				for (k = 0; k <= i - 1; k++)
					((p + k*l_max + j)->downwards)++;

				(p + i*l_max + j)->highlight = 0;
				(p + i*l_max + j)->color = 0;
			}
		}
	}
}

void all_score_set_0(point *const first, const int h, const int l)//所有位置score置零
{
	int i, j;
	point *p;

	for (i = 0; i < h; i++)
	{
		p = first + i*l_max;
		for (j = 0; j < l; j++)
		{
			p->score = 0;
			p++;
		}
	}
}