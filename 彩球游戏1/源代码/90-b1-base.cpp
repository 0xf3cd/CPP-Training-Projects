/*1550431 �ƿ�3�� �����*/
#include "90-b1.h"
//��ŶԼ�¼���̽���ͳ�ơ������ĺ���

void randomly_generate_map(point * const first, const int h, const int l)//��һ����Χ�ڵ������ʼ����ɫ
{
	int i, j;
	point *p;

	srand(unsigned(time(NULL)));
	for (i = 0; i < h; i++)
	{
		p = first + l_max*i;//ָ���i���׸�Ԫ��
		for (j = 0; j < l; j++)
		{
			p->color = randomly_return_color();
			p++;//ָ���һ��Ԫ��
		}
	}
}

int find_removable_points(point * const first, const int h, const int l)//�ҵ������������򣬷�������������Աhighlight��1������ǵ÷����
{
	int i, j;
	point *p;

	for (i = 0; i <= h - 3; i++)//Ѱ������ͬɫ��
	{
		p = first + l_max*i;
		for (j = 0; j < l; j++)
		{
			if (p->highlight == 0)//δ�����ʱ,Ѱ��ͬɫ��
				how_many_same_color(1, p, h - i);

			p++;
		}
	}

	for (i = 0; i < h; i++)//Ѱ�Һ���ͬɫ��
	{
		p = first + l_max*i;
		for (j = 0; j <= l - 3; j++)
		{
			if (p->highlight == 0)//δ�����ʱ,Ѱ��ͬɫ��
				how_many_same_color(2, p, l - j);

			p++;
		}
	}

	return sum_up_highlight(first, h, l);//���ر���ǵ���ĸ���
}

int how_many_same_color(int direction, point *const from, const int rest_balls)//��fromָ�����ʼ��1��2�ֱ� refers to �¡��ң�����ֵΪ�ҵ���ͬɫ�������С�ڵ���3����0��������Ҫ����ͬʱ���
{
	int counts = 0, i, color;
	point *p = from;

	if (direction == 1)//����
	{
		color = p->color;

		for (i = 1; i <= rest_balls; i++)
		{
			if (p->color == color)
				counts++;
			else
				break;

			p = p + l_max;//ָ����һ�е���һ����
		}

		if (counts >= 3)//��������������������������ͬɫ������б��
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

	if (direction == 2)//����
	{
		color = p->color;

		for (i = 1; i <= rest_balls; i++)
		{
			if (p->color == color)
				counts++;
			else
				break;

			p = p + 1;//ָ����һ�е���һ����
		}

		if (counts >= 3)//�������ֺ�����������������ͬɫ������б��
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

void move_points(point *const first, const int h, const int l)//����ͬɫ�ģ�������
{
	point *p;
	int i, j, removable;

	for (i = h - 1; i >= 0; i--)//���¶��ϣ��������
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

void move_downwards(point *const p, const int amount, const int spaces)//��pָ�����������������򣬹�amount���������ƶ�spaces��λ��
{
	int i;
	point *now = p;//now refers to the point now being operated

	for (i = 0; i < amount; i++)//����
	{
		(now + spaces*l_max)->highlight = now->highlight;
		(now + spaces*l_max)->color = now->color;

		now -= l_max;//ָ������
	}

	now = p - (amount - 1)*l_max;//now points to the first ball of the ��
	for (i = 0; i < spaces; i++)//���ճ���λ����0
	{
		now->color = 0;
		now->highlight = 0;

		now += l_max;//ָ������
	}
}

void fill_empty_points(point *const first, const int h, const int l)//����λ
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

void all_highlight_set_0(point *const first, const int h, const int l)//����λ��highlight����
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

void all_key_highlight_set_0(point *const first, const int h, const int l)//����λ��key_highlight����
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

void all_downwards_set_0(point *const first, const int h, const int l)//����λ��downwards����
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

void sum_up_downwards(point*first, const int h, const int l)//���������downwards���Ա����
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

void all_score_set_0(point *const first, const int h, const int l)//����λ��score����
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