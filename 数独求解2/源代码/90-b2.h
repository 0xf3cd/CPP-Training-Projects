#pragma once
/*1550431 �ƿ�3�� �����*/
//���й��ú������壬�Լ�ȫ��ʹ�õĳ������궨��
#include <iostream>
#include <conio.h>
#include <fstream>
#include <windows.h>
#include<stdio.h>
#include "cmd_console_tools.h"
using namespace std;

const HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE); //ȡ��׼����豸��Ӧ�ľ��
const HANDLE hin = GetStdHandle(STD_INPUT_HANDLE);  //ȡ��׼�����豸��Ӧ�ľ��
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

int get_files(char *name, char file_name[100][50], const int X,const int Y,int mode=1);//��ȡ��ǰĿ¼�������ļ���,����-1�������
int select_and_generate(point head[9][9], char file_name[100][50], const int X, const int Y, int &highlight, int &from, int mode =1);//���û������ļ�ѡ��,����������,������-1,���Ϸ�����0
void free_space(step *head);//�ͷŴ��沽��������
int check_valid(point *head);//return <0,conflict//�ж��Ƿ��г�ͻ����
point *point_address(point *from,int n);//���ش�from��ʼ��n��λ�õĵ�ַ
int check_ghl_valid(point *start, int mode);//return -1,conflict//�ж�1 �� 2 һ�� 3 һ���Ƿ��г�ͻ������(�ֱ�Ϊ�����Ͻǵĵ�ַ����һ�е�һ������Ԫ�ص�ַ)
void mark_highlight(point *start, int mode);//mode 1�� 2�� 3�� ��Ǹ��� 
void conflict_and_highlight_set_0(point *head);//conflict set 0
void draw_basic_sudoku(point *head, const int X, const int Y, int goxyornot = 0);//��X,Y������򵥵������ֲ����
void end_until_end(int X, int Y, char *note = "��С�������������End����...  ", int goxyornot =0);//������(X,Y)�����������С�����ʾ,����endʱ������֦
int check_if_a_char_ok(char c, char *note, char itshouldbefrom, char itshouldbeto);//�н���һ������
char capitalize(char c);//�����ĸ�Ĵ�д
void showcinwrong(int X, int Y, char *note, char *noteofwrong = "�����������������");//��ʾ�������,���ù��ظ���(X,Y),�ٴ����������С�����ʾ
int game_over(point *head);//�ж���Ϸ�Ƿ��������������򷵻�1������Ϊ0
int check_fulfill(point *address[9]);//���9��λ���Ƿ���1-9������һ��//����1��������
int get_user_input(int &pos, int &value, char *last_move);//��ȡ�û����룬�������bk����-1��������󷵻�0����ȷ����1
void draw_file_choice(const int X, const int Y, const int from, const int highlight, char file_name[100][50]);//�����ѡ�ļ��˵�
int save_and_apply_steps(point *head, step *&s_now, const step *const s_head,int &res, char *last_move);//��¼���������ģ�����-1��������ռ�ʧ��
void draw_complex_sudoku(point *head, const int X=0, const int Y=0, int goxyornot = 0);//��X,Y�����ͼ�λ��������ֲ����
void output_res(char *res, char *last_move, const int X, const int Y, int goxyornot = 0);//��X,Y������ƶ������ʾ
void all_char_set_0(char *x);//�ظ�����λΪβ0
int first_operation(point *head,int *&pos,int &fillable);//�ҳ���ͨ���ų���ȷ������������λ�ò�����1-9����ɺ�����һ����¼û���������ֵ�λ�õ����顣����-1��������ռ����
void first_of_all_fill_in(point *head);//�ҳ���ͨ���ų���ȷ������������λ�ò�����1-9
int check_this_pos_fillable(point *head, int pos);//�ҳ���һλ�����������(��λVALUEΪ0��ǰ����),pos 0-80
int auto_steps(point *head, step * s_head, int* pos, int fillable, const int X, const int Y,double &time);//�Զ��߲������ģ�����-1��������ռ�ʧ��,0����û�н�,1��ʾ���
int make_this_pos_possible_shuzu(point *head, int pos);//�Զ��������У��ҳ�ĳ��λ�������������,pos 0-80������0�����޿���������,-1����ռ�����ʧ��
void this_pos_set_0(point *this_pos);//����λ���������0
void free_possible(point*head);//�ͷ�possible����