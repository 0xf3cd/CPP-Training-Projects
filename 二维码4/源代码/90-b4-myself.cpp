/*1550431 ����� �ƿ�3��*/
//��ά�룬�Լ�ʵ��
#define _CRT_SECURE_NO_WARNINGS
#include "90-b4.h"

QR_point*generate_QR_code(int version)//���ɶ�ά����̣������������飩�������������׵�ַ
{
	int L = 17 + version * 4;//L����ÿ��ģ������(n+2)*(n+2)��������Alignment Patterns�ĸ���������������������ͼ�γ�ͻ�������
	QR_point *head = new(nothrow) QR_point[L*L];
	char Format_Information[] = "101010000010010"; //"010010000010101";

	if(head==NULL)
	{
		cout << "\n��̬�ڴ�����ʧ��\n";
		return NULL;
	}

	//����ɹ�
	fill_in_Finder_Pattern(head, version);//ͬʱ����SEPERATOR
	if(fill_in_Alignment_Pattern(head, version)==-1)
	{
		free_QR_code(head);
		return NULL;
	}
	fill_in_Timing_Pattern(head, version);
	fill_in_Format_Information(head,version, Format_Information );
	fill_in_Version_Information(head, version);
	return head;
}

void free_QR_code(QR_point *head)//�ͷŴ����ά����Ϣ�Ŀռ�
{
	delete[]head;
}

void fill_in_Finder_Pattern(QR_point *qr, int version)//��������Ѱ��ͼ��
{
	int pos = 17 + 4 * version - 6,i,L=4*version+17;

	fill_in_one_Finder_Pattern(qr,version, 1, 1);
	for(i=0;i<8;i++)//seperator
	{
		(qr + i*L + 7)->value = 0;
		(qr + i*L + 7)->fillable = 0;
	}
	for (i = 0; i<7; i++)
	{
		(qr + 7*L+ i)->value = 0;
		(qr + 7 * L + i)->fillable = 0;
	}

	fill_in_one_Finder_Pattern(qr, version, 1, pos);
	for (i = 0; i<8; i++)//seperator
	{
		(qr + i*L + L-8)->value = 0;
		(qr + i*L + L-8)->fillable = 0;
	}
	for (i = 0; i<7; i++)
	{
		(qr + 7 * L + L-7+i)->value = 0;
		(qr + 7 * L + L-7+i)->fillable = 0;
	}

	fill_in_one_Finder_Pattern(qr, version, pos, 1);
	for (i = 0; i<8; i++)//seperator
	{
		(qr + (L-8+i)*L + 7)->value = 0;
		(qr + (L - 8 + i)*L + 7)->fillable = 0;
	}
	for (i = 0; i<7; i++)
	{
		(qr + (L-8) * L + i)->value = 0;
		(qr + (L - 8) * L + i)->fillable = 0;
	}
}

void fill_in_Version_Information(QR_point *qr, int version)//����汾��Ϣ
{
	if (version < 7)
		return;

	char info[3][19] = { "100110011110000010","111000011100010000","000100011000110111" };
	int L = 17 + 4 * version, i, j,v=version-7;

	for(i=0;i<3;i++)
	{
		for(j=0;j<6;j++)
		{
			(qr + j*L + L - 9 - i)->value = info[v][6 * i + j] - '0';
			(qr + j*L + L - 9 - i)->fillable = 0;
		}
	}

	for (i = 0; i<3; i++)
	{
		for (j = 0; j<6; j++)
		{
			(qr + (L-9-i)*L+j)->value = info[v][6 * i + j] - '0';
			(qr + (L - 9 - i)*L + j)->fillable = 0;
		}
	}
}

void fill_in_one_Finder_Pattern(QR_point *qr,const int version, const int h, const int l)//��(X,Y)Ϊ���Ͻǵĵ㣬����һ��Ѱ��ͼ��
{
	//��������
	int i, j,now_h=h-1,now_l=l-1,L=17+4*version;

	//�����
	for(i=0;i<7;i++)
	{
		qr[now_h*L+now_l + i].value = 1;//��ɫ
		//qr[now_h][now_l + i].fillable = 0;//��������
	}
	for (i = 0; i<7; i++)
	{
		qr[(now_h+6) * L + now_l + i].value = 1;//��ɫ
		//qr[now_h+6][now_l + i].fillable = 0;//��������
	}
	for (i = 1; i<6; i++)
	{
		qr[(now_h+i)*L + now_l].value = 1;//��ɫ
		//qr[now_h+i][now_l].fillable = 0;//��������
	}
	for (i = 1; i<6; i++)
	{
		qr[(now_h + i)*L + now_l+6].value = 1;//��ɫ
		//qr[now_h + i][now_l+6].fillable = 0;//��������
	}

	//���ڲ�С������
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			qr[(now_h + 2 + i)*L + now_l + 2 + j].value = 1;
		}
	}

	for(i=0;i<7;i++)
	{
		for(j=0;j<7;j++)
		{
			qr[(now_h + i)*L + now_l + j].fillable = 0;
		}
	}
}

void fill_in_Timing_Pattern(QR_point *qr, int version)//���붨λͼ��
{
	int L = 17 + 4 * version, i, black_or_white = 1;

	for(i=8;i<=L-9;i++)
	{
		(qr + 6 * L + i)->value = black_or_white % 2;
		(qr + 6 * L + i)->fillable = 0;
		black_or_white++;
	}

	black_or_white = 1;
	for (i = 8; i <= L - 9; i++)
	{
		(qr + 6+i*L)->value = black_or_white % 2;
		(qr + 6 + i*L)->fillable = 0;
		black_or_white++;
	}
}

int fill_in_Alignment_Pattern(QR_point *qr, int version)//����У��ͼ�Σ��ռ�����ʧ�ܷ���-1
{
	//ע���������ۣ�version=1��version!=1
	if (version == 1)
		return 1;

	int L=17+4*version,n = version / 7,i,j,*saver,d;//dΪAlignment Pattern���ĵ�ļ��
	saver = new(nothrow) int[n + 2];
	if(saver==NULL)
	{
		system("cls");
		cout << "��̬�ڴ�����ʧ��\n";
		return -1;
	}

	if ( (4 * (version + 1)) % (n + 1)==0)//����
		d = (4 * (version + 1)) / (n + 1);
	else
	{
		d = (4 * (version + 1) / (n + 1)) + 1;
		if (d % 2 == 1)
			d++;
	}

	for(i=n+1;i>=1;i--)
	{
		saver[i] = L - 6 - d*(n+1-i);
	}
	saver[0] = 7;

	for(i=0;i<n+2;i++)
	{
		for(j=0;j<n+2;j++)
		{
			if ((qr + (saver[i]-1)*L + saver[j]-1)->fillable)
				fill_in_one_Alignment_Pattern(qr, version, saver[i], saver[j]);
		}
	}

	delete[]saver;
	return 1;
}

void fill_in_one_Alignment_Pattern(QR_point *qr, const int version, const int x, const int y)//����һ��У��ͼ�Σ���(x-1,y-1)Ϊ����
{
	int X = x - 1, Y = y - 1,i,j,L=17+4*version;

	for(i=X-2;i<=X+2;i++)
	{
		for(j=Y-2;j<=Y+2;j++)
		{
			(qr + i*L + j)->value = 1;
			(qr + i*L + j)-> fillable = 0;
		}
	}

	for (i = X - 1; i <= X + 1; i++)
	{
		for (j = Y - 1; j <= Y + 1; j++)
		{
			(qr + i*L + j)->value = 0;
			//(qr + i*L + j)->fillable = 0;
		}
	}

	(qr + X*L + Y)->value = 1;
}

void output_QR_code(QR_point *qr, int version)//��ʾ��ά��ͼ��
{
	int L = 17 + 4 * version,i,j;

	for(i=0;i<L;i++)
	{
		for(j=0;j<L;j++)
		{
			if ((qr+i*L+j)->value)//��
				setcolor(hout, COLOR_BLACK,COLOR_BLACK);
			else
				setcolor(hout, COLOR_HWHITE,COLOR_HWHITE);

			//for (k = 0; k < 3; k++)
			//{
				gotoxy(hout,  2 * (j+2),i+2);
				cout << "  ";
			//}

			//Sleep(10);
			//cout << (qr + i*L + j)->value;
		}
		//cout << endl;
	}

	setcolor(hout, COLOR_HWHITE, COLOR_HWHITE);
	for(i=0;i<2;i++)
	{
		for(j=0;j<L+4;j++)
		{
			gotoxy(hout, 2 * j, i);
			cout << "  ";
		}
	}

	for (i = L+2; i<L+4; i++)
	{
		for (j = 0; j<L + 4; j++)
		{
			gotoxy(hout, 2 * j, i);
			cout << "  ";
		}
	}

	for (i = 2; i < L + 2; i++)
	{
		gotoxy(hout, 0, i);
		cout << "    ";

		gotoxy(hout, 4+L*2, i);
		cout << "    ";
	}

	cout << endl << endl << endl;
	setcolor(hout, COLOR_BLACK, COLOR_WHITE);
}

char *get_input()//�����û�����
{
	int counts = 0,i;
	char x,*input;
	one_char *now=new(nothrow) one_char,*head=now,*next;
	cout << "��������Ҫ���ɶ�ά����ַ���\n";

	if(now==NULL)
	{
		cout << "��̬�ڴ�����ʧ��\n";
		return NULL;
	}

	while((x=getchar())!='\n')
	{
		counts++;
		now->x = x;

		next = new(nothrow) one_char;
		if (next == NULL)
		{
			cout << "��̬�ڴ�����ʧ��\n";
			free_temp_char(head);
			return NULL;
		}

		now->next = next;
		now = next;
	}//��ѭ��ʱ��nowָ��һ��������

	now->x = '\0';

	input = new(nothrow) char[counts + 1];
	if(input==NULL)
	{
		cout << "��̬�ڴ�����ʧ��\n";
		free_temp_char(head);
		return NULL;
	}

	now = head;
	for(i=0;i<=counts;i++)
	{
		input[i] = now->x;
		now = now->next;
	}//�Զ�����β��

	free_temp_char(head);
	return input;
}

void free_temp_char(one_char*head)//�ͷ���ʱ�����ַ����Ŀռ�
{
	one_char*now=head, *next=head->next;

	while(next!=NULL)
	{
		delete now;
		now = next;
		next = now->next;
	}
	delete now;
}

int decide_version(char *saver)//����UTF-8�����ַ������ж϶�ά��İ汾
{
	//������M��������
	//version9��������1456λ���㹻100�ֽ�ʹ��
	int length = strlen(saver),bits=8*length;

	if (bits <= 128)
		return 1;

	if (bits <= 224)
		return 2;

	if (bits <= 352)
		return 3;

	if (bits <= 512)
		return 4;

	if (bits <= 688)
		return 5;

	if (bits <= 864)
		return 6;

	if (bits <= 992)
		return 7;

	if (bits <= 1232)
		return 8;

	return 9;
}

char* translate_char_into_01(char *saver,int version)//����UTF-8�����ַ��������ݹ���ת����0101��������NULL
{
	int codewords[9] = { 16,28,44,64,86,108,124,154,182 };
	//saver = G2U(saver);//��ʱsaver��������Ŀռ䣬�����Ҫ�ͷ�
	//cout << saver << endl;
	int i,left, length = strlen(saver), result_length = 8*codewords[version-1]+1;//= 4 + (version <= 9 ? 8 : 16) + 8 * length;
	char *result = new(nothrow) char[result_length + 1],*temp, padding_bytes_1[] = "11101100", padding_bytes_2[] = "00010001";
	if(result==NULL)
	{
		cout << "\n��̬�ڴ�����ʧ��\n";
		//delete[]saver;
		return NULL;
	}

	result[0] = '\0';
	strcat(result, "0100");

	temp = translate_int_into_01(length, (version <= 9 ? 8 : 16));
	if(temp==NULL)
	{
		cout << "\n��̬�ڴ�����ʧ��\n";
		//delete[]saver;
		delete[]result;
		return NULL;
	}
	//if success
	strcat(result, temp);
	delete[] temp;

	for(i=0;i<length;i++)
	{
		temp = translate_int_into_01(saver[i], 8);
		if (temp == NULL)
		{
			cout << "\n��̬�ڴ�����ʧ��\n";
			//delete[]saver;
			delete[]result;
			return NULL;
		}

		strcat(result, temp);
		delete[] temp;
	}

	strcat(result,"0000");//������
	left = codewords[version - 1] - strlen(result) / 8;//�õ�ʣ��λ

	for(i=1;i<=left/2;i++)
	{
		strcat(result, padding_bytes_1);
		strcat(result, padding_bytes_2);
	}

	if(left%2==1)
		strcat(result, padding_bytes_1);

	//result[result_length] = '\0';

	return result;
}

char *translate_int_into_01(unsigned int src, int bits)//�������һ����ת����һ����01���ɵ��ַ���
{
	int i,temp;
	char *t = new(nothrow) char[bits + 1];
	if(t==NULL)
	{
		cout << "\n��̬�ڴ�����ʧ��\n";
		return NULL;
	}

	t[bits] = '\0';
	for(i=bits-1;i>=0;i--)
	{
		temp = src % 2;//temp��src��������ʽ�е�ĩλ
		t[i] = '0' + temp;
		src -= temp;
		src /= 2;
	}

	return t;
}

char *encode(char *src, int version)//���ձ���
{
	int codewords[9] = { 16,28,44,64,86,108,124,154,182 },
		error_correction_codewords[9] = { 10,16,26,36,48,64,72,88,110 };
	char *saver,*error_correction_saver,*temp;
	short i,n= codewords[version-1]+ error_correction_codewords[version-1], k= codewords[version-1];
	unsigned char *data, *error_correction;

	saver = new(nothrow) char[8 * (codewords[version - 1] + error_correction_codewords[version - 1]) + 1];
	if(saver==NULL)
	{
		cout << "��̬�ڴ�����ʧ��\n";
		return NULL;
	}

	error_correction_saver = new(nothrow) char[8 * error_correction_codewords[version - 1] + 1];
	if (error_correction_saver == NULL)
	{
		delete[] saver;
		cout << "��̬�ڴ�����ʧ��\n";
		return NULL;
	}

	saver[0] = '\0';
	strcat(saver, src);

	data = new(nothrow) unsigned char[k];
	devide_codewords_into_unsigned_char(src, data);//data�б�������Ϣ��ת��ɵ�unsigned char������

	error_correction = RS_code(n, k, data);

	for (i = 0; i<n-k; i++)
	{
		temp = translate_int_into_01(error_correction[i], 8);
		if (temp == NULL)
		{
			cout << "\n��̬�ڴ�����ʧ��\n";
			//delete[]saver;
			delete[]error_correction_saver;
			delete[]saver;
			return NULL;
		}

		strcat(saver, temp);
		delete[] temp;
	}

	delete[]error_correction_saver;
	return saver;
}

void devide_codewords_into_unsigned_char(char *src, unsigned char* saver)//����Ϣ���0101��8��һ�飬ת����unsigned char
{
	int counts = 0,all_codewords=strlen(src)/8,i,j;
	unsigned char temp;

	for(i=0;i<all_codewords;i++)
	{
		temp = 0;
		for(j=1;j<=8;j++)
		{
			temp *= 2;
			temp += src[counts++] - '0';
		}
		saver[i] = temp;
	}
}

void fill_in_Format_Information(QR_point *qr, int version,char *info)//����15��0101������MASK�;���ȼ�
{
	int L = 17 + 4 * version,i;

	for(i=0;i<6;i++)
	{
		(qr + 8 * L + i)->value = info[i] - '0';
		(qr + 8 * L + i)->fillable = 0;
	}

	(qr + 8 * L + 7)->value = info[6] - '0';
	(qr + 8 * L + 7)->fillable = 0;

	(qr + 8 * L + 8)->value = info[7] - '0';
	(qr + 8 * L + 8)->fillable = 0;

	(qr + 7 * L + 8)->value = info[8] - '0';
	(qr + 7 * L + 8)->fillable = 0;

	for(i=9;i<15;i++)
	{
		(qr + (14-i) * L + 8)->value = info[i] - '0';
		(qr + (14-i) * L + 8)->fillable = 0;
	}

	for (i = 0; i<7; i++)
	{
		(qr + (L-1-i) * L + 8)->value = info[i] - '0';
		(qr + (L - 1 - i) * L + 8)->fillable = 0;
	}

	//Dark Module
	(qr + (L - 8) * L + 8)->value = 1;
	(qr + (L - 8) * L + 8)->fillable = 0;

	for (i = 7; i<15; i++)
	{
		(qr + 8 * L + (L-15+i))->value = info[i] - '0';
		(qr + 8 * L + (L - 15 + i))->fillable = 0;
	}
}

void fill_in_all_bits(QR_point *qr, int version,char *final_code)//��01�����ά�������
{
	int length = strlen(final_code),L=17+4*version,i,counts=0,mode=1,x,y;

	for(i=L-1;i>=0;i-=2)
	{
		if(i==6)
		{
			i--;
			//continue;
		}
		if(mode==1)//down to up
		{
			x = i;
			y = L - 1;
			
			while (y >= 0)
			{
				if ((qr + y*L + x)->fillable == 1)
					(qr + y*L + x)->value = final_code[counts++] - '0';
				if (counts >= length)
					break;

				if ((qr + y*L + x-1)->fillable == 1)
					(qr + y*L + x - 1)->value = final_code[counts++] - '0';
				if (counts >= length)
					break;

				y--;
			}

			mode = 2;
		}
		else//up to down
		{
			x = i;
			y = 0;

			while (y <=L-1 )
			{
				if ((qr + y*L + x)->fillable == 1)
					(qr + y*L + x)->value = final_code[counts++] - '0';
				if (counts >= length)
					break;

				if ((qr + y*L + x - 1)->fillable == 1)
					(qr + y*L + x - 1)->value = final_code[counts++] - '0';
				if (counts >= length)
					break;

				y++;
			}
			
			mode = 1;
		}
	}
}

void add_mask(QR_point *qr, int version, int mask)//������Ĥ
{
	int i, j, L = 17 + 4 * version;

	for(i=0;i<L;i++)
	{
		for(j=0;j<L;j++)
		{
			if((qr + i*L + j)->fillable)
			{
				(qr + i*L + j)->value = ((qr + i*L + j)->value) ^ (((i + j) % 2) ^ 1);
			}
		}
	}
}