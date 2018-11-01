#pragma once
/*1550431 王甯琪 计科3班*/
//放置公共    申       明    部分
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

const HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE); //取标准输出设备对应的句柄
const HANDLE hin = GetStdHandle(STD_INPUT_HANDLE);  //取标准输入设备对应的句柄
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
	int type = 0;//1倒计时 2单次 3每日 4工作日
	now_time *alarm_time=NULL;
	alarm *next=NULL;
	alarm*previous = NULL;
};

void get_now_time(now_time *saver);//获取当前时间
int translate_string_to_num(char *c,int n);//将char数组储存的数字转为int形数字
void print_now_time(now_time *saver, const int X = 0, const int Y = 0);//默认在窗口左上角输出当前时间
int generate_circle(point *&first, const int X, const int Y,const int R);//以X,Y为圆心，生成一个圆的轨迹点 内存申请错误返回-1
void free_points(point *&first);//释放储存轨迹点的空间
void draw_points(point*first, char x);//在所有点处输出字符x
int  generate_kedu(point *&first, const int X, const int Y, const int R,const int L);//以X,Y为圆心,R为半径生成的表盘的刻度，刻度长度为L 内存申请错误返回-1
int  generate_zhen(now_time*saver,point *&h_first,point *&m_first,point *&s_first, const int X, const int Y);//在以X,Y为圆心,R为半径生成的表盘上，生成时分秒的指针 内存申请错误返回-1
void until_time_change(now_time tm);
int generate_10_nums(point*num[11], const int c, const int k);//生成十个数字的相对坐标 c,k代表长宽 内存申请错误返回-1
int combime_nums(now_time *tm, point *num[11],point *&all_num, const int k,const int X, const int Y);//在 X,Y 处生成记录输出点的链表
void points_link_add_X_Y(point *&first, const int X, const int Y);//整体移动(X,Y)
int copy_points_link(point *&source,point*&destination);//复制
void combine_two_point_links(point *&a,point *&b);//连接两个链表
void clear_point_link(point *&a);//清空链表
int read_alarm_into_memory(fstream &saver,alarm *&head);//将文件中的信息读入内存
void free_alarm(alarm *&head);
void show_all_alarms(alarm *head,const int X,const int Y);//在X,Y处输出所有闹钟
int check_all_alarms(alarm *&head);//检查所有闹钟是否到时间
int two_time_compare(now_time *t1,now_time*t2);//比较两个时间先后
void play_music();
int new_alarm(alarm *&head);
void adjust_time(now_time*&t);//调整时间
void output_to_file(fstream &f,alarm*head);