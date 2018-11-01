#pragma once
/*1550431 王甯琪 计科3班*/
//全局变量，函数申明
#include <iostream>
#include "cmd_console_tools.h"
using namespace std;

const HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE); //取标准输出设备对应的句柄
const HANDLE hin = GetStdHandle(STD_INPUT_HANDLE);  //取标准输入设备对应的句柄
const double ytox = 5 / 3;

struct QR_point
{
	//默认全白，全可填入

	//int X;
	//int Y;//(X,Y)代表坐标
	int value=0;//0 白 1 黑
	int fillable=1;
	//QR_point *next=NULL;
};

struct one_char//临时储存字符串
{
	char x;
	one_char *next = NULL;
};

QR_point *generate_QR_code(int version);//生成二维码表盘（本质上是数组），并返回数组首地址，返回NULL代表出错
void free_QR_code(QR_point *head);//释放储存二维码信息的空间
void fill_in_Finder_Pattern(QR_point *qr, int version);//填入三个寻像图形，并填入分隔符
void fill_in_one_Finder_Pattern(QR_point *qr,const int version, const int h,const int l);//以(X,Y)为左上角的点，填入一个寻像图形
void fill_in_Timing_Pattern(QR_point *qr, int version);//填入定位图形
int fill_in_Alignment_Pattern(QR_point *qr, int version);//填入校正图形，空间申请失败返回-1
void fill_in_one_Alignment_Pattern(QR_point *qr, const int version, const int x, const int y);//填入一个校正图形，以(x-1,y-1)为中心
void fill_in_Format_Information(QR_point *qr, int version,char *info);//填入15个0101，代表MASK和纠错等级
void fill_in_Version_Information(QR_point *qr, int version);//填入版本信息
char* G2U(const char* gb2312);//将GB2312编码转换成UTF-8编码格式
char *get_input();//接受用户输入
void free_temp_char(one_char*head);//释放临时储存字符串的空间
int decide_version(char *saver);//传入UTF-8编码字符串，判断二维码的版本
char* translate_char_into_01(char *saver,int version);//传入UTF-8编码字符串，根据规则转换成0101，出错返回NULL
char *translate_int_into_01(unsigned int src, int bits);//将输入的一个数转换成一个由01构成的字符串
unsigned int turn_to_dec(int n, string Binary_string);//RS算法实现部分
unsigned char* RS_code(int n, int k, unsigned char *data_codewords);//RS算法实现部分
char *encode(char *src,int version);//最终编码
void devide_codewords_into_unsigned_char(char *src,unsigned char* saver);//将信息码的0101，8个一组，转换成unsigned char
void fill_in_all_bits(QR_point *qr, int version,char *final_code);//将01填入二维码表盘中
void add_mask(QR_point *qr, int version, int mask = 0);//加上掩膜
void output_QR_code(QR_point *qr, int version);//显示二维码图像