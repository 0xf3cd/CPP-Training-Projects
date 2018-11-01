#pragma once
/*1550431 计科3班 王甯琪*/
//所有公用函数定义，以及全局使用的常量、宏定义
#include <iostream>
#include <conio.h>
#include <fstream>
#include <windows.h>
#include<stdio.h>
#include "cmd_console_tools.h"
using namespace std;

const HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE); //取标准输出设备对应的句柄
const HANDLE hin = GetStdHandle(STD_INPUT_HANDLE);  //取标准输入设备对应的句柄
const int choice = 3, h_max = 9,l_max=9;

struct point
{
	int value = 0;
	int changable = 1;
	int conflict = 0;
	int highlight = 0;
	int all_fillable = 0;
	int now_fill = 0;
	int *possible=NULL;
};

struct step
{
	int position=1;
	int change_from;
	step *previous = NULL;
	step *next=NULL;
};

int get_files(char *name, char file_name[100][50], const int X,const int Y,int mode=1);//获取当前目录下所有文件名,返回-1代表出错
int select_and_generate(point head[9][9], char file_name[100][50], const int X, const int Y, int &highlight, int &from, int mode =1);//让用户进行文件选择,并生成链表,出错返回-1,不合法返回0
void free_space(step *head);//释放储存步数的链表
int check_valid(point *head);//return <0,conflict//判断是否有冲突数字
point *point_address(point *from,int n);//返回从from开始第n个位置的地址
int check_ghl_valid(point *start, int mode);//return -1,conflict//判断1 宫 2 一行 3 一列是否有冲突的数字(分别为宫左上角的地址、第一行第一列所有元素地址)
void mark_highlight(point *start, int mode);//mode 1宫 2行 3列 标记高亮 
void conflict_and_highlight_set_0(point *head);//conflict set 0
void draw_basic_sudoku(point *head, const int X, const int Y, int goxyornot = 0);//在X,Y处输出简单的数独分布情况
void end_until_end(int X, int Y, char *note = "本小题结束，请输入End继续...  ", int goxyornot =0);//在坐标(X,Y)处输出结束本小题的提示,输入end时跳出分枝
int check_if_a_char_ok(char c, char *note, char itshouldbefrom, char itshouldbeto);//承接上一个函数
char capitalize(char c);//输出字母的大写
void showcinwrong(int X, int Y, char *note, char *noteofwrong = "输入错误，请重新输入");//提示输入错误,并让光标回复到(X,Y),再次输出结束本小题的提示
int game_over(point *head);//判断游戏是否结束，如果结束则返回1，否则为0
int check_fulfill(point *address[9]);//检查9个位置是否是1-9各出现一次//返回1代表满足
int get_user_input(int &pos, int &value, char *last_move);//读取用户输入，如果输入bk返回-1，输入错误返回0，正确返回1
void draw_file_choice(const int X, const int Y, const int from, const int highlight, char file_name[100][50]);//输出可选文件菜单
int save_and_apply_steps(point *head, step *&s_now, const step *const s_head,int &res, char *last_move);//记录步数并更改，返回-1代表申请空间失败
void draw_complex_sudoku(point *head, const int X=0, const int Y=0, int goxyornot = 0);//在X,Y处输出图形化的数独分布情况
void output_res(char *res, char *last_move, const int X, const int Y, int goxyornot = 0);//在X,Y处输出移动后的提示
void all_char_set_0(char *x);//回复所有位为尾0
int first_operation(point *head,int *&pos,int &fillable);//找出能通过排除法确定的所有数独位置并填入1-9。完成后生成一个记录没有填入数字的位置的数组。返回-1代表申请空间错误
void first_of_all_fill_in(point *head);//找出能通过排除法确定的所有数独位置并填入1-9
int check_this_pos_fillable(point *head, int pos);//找出这一位能填入的数字(该位VALUE为0的前提下),pos 0-80
int auto_steps(point *head, step * s_head, int* pos, int fillable, const int X, const int Y,double &time);//自动走步并更改，返回-1代表申请空间失败,0代表没有解,1表示完成
int make_this_pos_possible_shuzu(point *head, int pos);//自动求解过程中，找出某个位置能填入的数字,pos 0-80。返回0代表无可填入数字,-1代表空间申请失败
void this_pos_set_0(point *this_pos);//将该位相关数据置0
void free_possible(point*head);//释放possible数组