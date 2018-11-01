/*1550431 王甯琪 计科3班*/
//公用的工具函数
#define  _CRT_SECURE_NO_WARNINGS
#include "90-b3.h"

void get_now_time(now_time *saver)//获取当前时间
{
	char time_saver[16] = { 0 };
	time_t t = time(0);

	strftime(time_saver,16, "%Y%m%d%w%H%M%S", localtime(&t));

	saver->year=translate_string_to_num(&time_saver[0], 4);
	saver->month=translate_string_to_num(&time_saver[4], 2);
	saver->day=translate_string_to_num(&time_saver[6], 2);
	saver->week=translate_string_to_num(&time_saver[8], 1);
	saver->hour= translate_string_to_num(&time_saver[9], 2);
	saver->minute= translate_string_to_num(&time_saver[11], 2);
	saver->second= translate_string_to_num(&time_saver[13], 2);
}

int translate_string_to_num(char *c, int n)//将char数组储存的数字转为int形数字
{
	int i, value = 0;

	for(i=0;i<n;i++)
	{
		value *= 10;
		value += c[i] - '0';
	}

	return value;
}

void print_now_time(now_time *saver, const int X , const int Y )//默认在窗口左上角输出当前时间
{
	gotoxy(hout, X, Y);

	cout << "当前时间: "
		<< saver->year << "年 "
		<< saver->month << "月 "
		<< saver->day << "日 ";

	cout << "星期";
	switch(saver->day)
	{
		case(1):
			cout << "一 ";
			break;
		case(2):
			cout << "二 ";
			break;
		case(3):
			cout << "三 ";
			break;
		case(4):
			cout << "四 ";
			break;
		case(5):
			cout << "五 ";
			break;
		case(6):
			cout << "六 ";
			break;
		default:
			cout << "日 ";
			break;
	}

	cout << saver->hour << "时 "
		<< saver->minute << "分 "
		<< saver->second << "秒";
}

void free_points(point *&first)//释放储存轨迹点的空间
{
	point *now,*next;
	now = first;

	while(now!=NULL)
	{
		next = now->next;
		delete now;
		now = next;
	}
}

void draw_points(point*first, char x)//在所有点处输出字符x
{
	point *now;
	now = first;

	while (now != NULL)
	{
		gotoxy(hout, now->X, now->Y);
		cout << x;

		now = now->next;
	}
}

void until_time_change(now_time tm)
{
	now_time tm2;

	while(1)
	{
		if (_kbhit())
			break;

		get_now_time(&tm2);

		if (tm2.second!= tm.second)
			break;
	}
}

void points_link_add_X_Y(point *&first, const int X, const int Y)//整体移动(X,Y)
{
	point *now;
	now = first;

	while (now != NULL)
	{
		now->X += X;
		now->Y += Y;

		now =now-> next;
	}
}

int copy_points_link(point *&source, point*&destination)//复制
{
	point *now, *d_now,*d_next;
	now = source;

	if (now == NULL)
		return 1;

	destination = new(nothrow) point;
	if(destination==NULL)
	{
		system("cls");
		cout << "动态内存申请失败";
		return -1;
	}
	d_now = destination;
		
	while (now ->next!= NULL)
	{
		d_now->X=now->X;
		d_now->Y=now->Y;

		d_next= new(nothrow) point;
		if (d_next == NULL)
		{
			system("cls");
			cout << "动态内存申请失败";
			//free_points(destination);
			return -1;
		}

		d_now->next = d_next;
		d_now = d_next;

		now = now->next;
	}

	d_now->X = now->X;
	d_now->Y = now->Y;

	//destination = d_now;

	return 1;
}

void combine_two_point_links(point *&a, point *&b)//连接两个链表
{
	point*last = a;

	while(last->next!=NULL)
	{
		last = last->next;
	}//出循环时，到达a的最后一个元素

	last->next = b;
}

void clear_point_link(point *&a)//清空链表
{
	if (a == NULL)
		return;

	point *now, *next;
	now = a->next;

	while(now!=NULL)
	{
		next = now->next;

		delete now;

		now = next;
	}
}

void free_alarm(alarm *&head)
{
	alarm *now, *next;

	now = head;
	while(now!=NULL)
	{
		next = now->next;
	
		if (now->alarm_time != NULL)
			delete now->alarm_time;

		delete now;
		now = now->next;
	}

	head = NULL;
	return;
}

int two_time_compare(now_time *t1, now_time*t2)//比较两个时间先后
{
	if (t1->year > t2->year)
		return 1;
	else	if (t1->year < t2->year)
		return -1;

	if (t1->month > t2->month)
		return 1;
	else	if (t1->month < t2->month)
		return -1;

	if (t1->day > t2->day)
		return 1;
	else	if (t1->day < t2->day)
		return -1;

	if (t1->hour > t2->hour)
		return 1;
	else	if (t1->hour < t2->hour)
		return -1;

	if (t1->minute > t2->minute)
		return 1;
	else	if (t1->minute < t2->minute)
		return -1;

	if (t1->second > t2->second)
		return 1;
	else	if (t1->second < t2->second)
		return -1;

	return 0;
}

void play_music()
{
	system("cls");
	cout << "时间到,5秒后自动返回\n";

	PlaySoundA(TEXT(".\\1550431\\Luka.wav"), NULL, SND_FILENAME);
}

void adjust_time(now_time*&t)//调整时间
{
	int day[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	if ((t->year % 4 == 0 && t->year % 100 != 0)|| t->year%400==0)
	{
		day[1]++;
	}

	if (t->second >= 60)
	{
		t->second -= 60;
		t->minute++;
	}

	if (t->minute>= 60)
	{
		t->minute -= 60;
		t->hour++;
	}

	if(t->hour>=24)
	{
		t->hour -= 24;
		t->day++;
		t->week++;
		if (t->week == 7)
			t->week = 0;
	}

	if(t->day>day[t->month-1])
	{
		t->day = 1;
		t->month++;
	}

	if(t->month>12)
	{
		t->month = 1;
		t->year++;
	}
}

void output_to_file(fstream &f, alarm*head)
{
	alarm *now=head;
	f.clear();

	while(now->type)
	{
		f << now->type << ' ';
		f << now->alarm_time->year << ' ';
		f << now->alarm_time->month << ' ';
		f << now->alarm_time->day << ' ';
		f << now->alarm_time->week << ' ';
		f << now->alarm_time->hour << ' ';
		f << now->alarm_time->minute << ' ';
		f << now->alarm_time->second << '\n';

		now = now->next;
	}
}