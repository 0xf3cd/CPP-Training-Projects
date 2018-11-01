#pragma once
/*1550431 ����� �ƿ�3��*/
//ȫ�ֱ�������������
#include <iostream>
#include "cmd_console_tools.h"
using namespace std;

const HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE); //ȡ��׼����豸��Ӧ�ľ��
const HANDLE hin = GetStdHandle(STD_INPUT_HANDLE);  //ȡ��׼�����豸��Ӧ�ľ��
const double ytox = 5 / 3;

struct QR_point
{
	//Ĭ��ȫ�ף�ȫ������

	//int X;
	//int Y;//(X,Y)��������
	int value=0;//0 �� 1 ��
	int fillable=1;
	//QR_point *next=NULL;
};

struct one_char//��ʱ�����ַ���
{
	char x;
	one_char *next = NULL;
};

QR_point *generate_QR_code(int version);//���ɶ�ά����̣������������飩�������������׵�ַ������NULL�������
void free_QR_code(QR_point *head);//�ͷŴ����ά����Ϣ�Ŀռ�
void fill_in_Finder_Pattern(QR_point *qr, int version);//��������Ѱ��ͼ�Σ�������ָ���
void fill_in_one_Finder_Pattern(QR_point *qr,const int version, const int h,const int l);//��(X,Y)Ϊ���Ͻǵĵ㣬����һ��Ѱ��ͼ��
void fill_in_Timing_Pattern(QR_point *qr, int version);//���붨λͼ��
int fill_in_Alignment_Pattern(QR_point *qr, int version);//����У��ͼ�Σ��ռ�����ʧ�ܷ���-1
void fill_in_one_Alignment_Pattern(QR_point *qr, const int version, const int x, const int y);//����һ��У��ͼ�Σ���(x-1,y-1)Ϊ����
void fill_in_Format_Information(QR_point *qr, int version,char *info);//����15��0101������MASK�;���ȼ�
void fill_in_Version_Information(QR_point *qr, int version);//����汾��Ϣ
char* G2U(const char* gb2312);//��GB2312����ת����UTF-8�����ʽ
char *get_input();//�����û�����
void free_temp_char(one_char*head);//�ͷ���ʱ�����ַ����Ŀռ�
int decide_version(char *saver);//����UTF-8�����ַ������ж϶�ά��İ汾
char* translate_char_into_01(char *saver,int version);//����UTF-8�����ַ��������ݹ���ת����0101��������NULL
char *translate_int_into_01(unsigned int src, int bits);//�������һ����ת����һ����01���ɵ��ַ���
unsigned int turn_to_dec(int n, string Binary_string);//RS�㷨ʵ�ֲ���
unsigned char* RS_code(int n, int k, unsigned char *data_codewords);//RS�㷨ʵ�ֲ���
char *encode(char *src,int version);//���ձ���
void devide_codewords_into_unsigned_char(char *src,unsigned char* saver);//����Ϣ���0101��8��һ�飬ת����unsigned char
void fill_in_all_bits(QR_point *qr, int version,char *final_code);//��01�����ά�������
void add_mask(QR_point *qr, int version, int mask = 0);//������Ĥ
void output_QR_code(QR_point *qr, int version);//��ʾ��ά��ͼ��