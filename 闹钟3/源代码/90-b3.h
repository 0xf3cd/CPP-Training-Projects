#pragma once
/*1550431 ����� �ƿ�3��*/
//���ù���    ��       ��    ����
//                shen  ming
#include <iostream>
#include <iomanip>
#include <conio.h>
#include <time.h>
#include <math.h>
#include <fstream>
#include <Windows.h>
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")
#include "cmd_console_tools.h"
using namespace std;

const HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE); //ȡ��׼����豸��Ӧ�ľ��
const HANDLE hin = GetStdHandle(STD_INPUT_HANDLE);  //ȡ��׼�����豸��Ӧ�ľ��
const double pai = 3.1415926535898;
const double XtoY = 1.62;

struct now_time
{
	int year;
	int month;
	int day;
	int week;
	int hour;
	int minute;
	int second;
};

struct point
{
	int X;
	int Y;
	point *next = NULL;
};

struct alarm
{
	int type = 0;//1����ʱ 2���� 3ÿ�� 4������
	now_time *alarm_time=NULL;
	alarm *next=NULL;
	alarm*previous = NULL;
};

void get_now_time(now_time *saver);//��ȡ��ǰʱ��
int translate_string_to_num(char *c,int n);//��char���鴢�������תΪint������
void print_now_time(now_time *saver, const int X = 0, const int Y = 0);//Ĭ���ڴ������Ͻ������ǰʱ��
int generate_circle(point *&first, const int X, const int Y,const int R);//��X,YΪԲ�ģ�����һ��Բ�Ĺ켣�� �ڴ�������󷵻�-1
void free_points(point *&first);//�ͷŴ���켣��Ŀռ�
void draw_points(point*first, char x);//�����е㴦����ַ�x
int  generate_kedu(point *&first, const int X, const int Y, const int R,const int L);//��X,YΪԲ��,RΪ�뾶���ɵı��̵Ŀ̶ȣ��̶ȳ���ΪL �ڴ�������󷵻�-1
int  generate_zhen(now_time*saver,point *&h_first,point *&m_first,point *&s_first, const int X, const int Y);//����X,YΪԲ��,RΪ�뾶���ɵı����ϣ�����ʱ�����ָ�� �ڴ�������󷵻�-1
void until_time_change(now_time tm);
int generate_10_nums(point*num[11], const int c, const int k);//����ʮ�����ֵ�������� c,k������ �ڴ�������󷵻�-1
int combime_nums(now_time *tm, point *num[11],point *&all_num, const int k,const int X, const int Y);//�� X,Y �����ɼ�¼����������
void points_link_add_X_Y(point *&first, const int X, const int Y);//�����ƶ�(X,Y)
int copy_points_link(point *&source,point*&destination);//����
void combine_two_point_links(point *&a,point *&b);//������������
void clear_point_link(point *&a);//�������
int read_alarm_into_memory(fstream &saver,alarm *&head);//���ļ��е���Ϣ�����ڴ�
void free_alarm(alarm *&head);
void show_all_alarms(alarm *head,const int X,const int Y);//��X,Y�������������
int check_all_alarms(alarm *&head);//������������Ƿ�ʱ��
int two_time_compare(now_time *t1,now_time*t2);//�Ƚ�����ʱ���Ⱥ�
void play_music();
int new_alarm(alarm *&head);
void adjust_time(now_time*&t);//����ʱ��
void output_to_file(fstream &f,alarm*head);