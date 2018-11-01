/*1550431 �ƿ�3�� �����*/
#include "90-b2.h"
//��Ź��ߺ����Լ����õĺ���

int get_files(char *name,char file_name[100][50], const int X, const int Y, int mode)//��ȡ��ǰĿ¼�������ļ���,����-1�������
{
	char title[50]={"dir /b > "},filename[50];
	int lenth,no_file=0,i=0;
	ifstream fin;

	strcat_s(title, name);
	system(title);
	
	fin.open(name, ios::in);
	if(fin.is_open()==0)
	{
		cout << "\n�ļ���ʧ��\n";
		return -1;
	}

	//if�򿪳ɹ�
	if (mode == 1)
	{
		cout << "��ǰĿ¼�·���sudoku*.txt��ƥ���ļ���:\n";
		while (!fin.eof())
		{
			fin >> filename;
			lenth = strlen(filename);

			if ((strncmp(filename, "sudoku", 6) == 0) && (strncmp(&filename[lenth - 4], ".txt", 4) == 0))//����ļ������� sudoku*.txt��ʽ�����
			{
				no_file = 1;
				cout << filename << endl;
			}
		}
	}
	else//2-3С�����������ļ�����char *����
	{
		i = 0;
		while (!fin.eof())
		{
			fin >> filename;
			lenth = strlen(filename);

			if ((strncmp(filename, "sudoku", 6) == 0) && (strncmp(&filename[lenth - 4], ".txt", 4) == 0))//����ļ������� sudoku*.txt��ʽ�����
			{
				no_file = 1;
				strcpy_s(file_name[i], filename);
				i++;
			}
		}
	}
	
	if (no_file == 0)
	{
		cout << "�޷���Ҫ���ļ�";
		Sleep(500);
		return -1;
	}
	
	fin.close();

	return 0;
}

void free_space(step *head)//�ͷŴ��沽��������
{
	step *now, *next;
	now = head;
	next = now->next;

	while (next != NULL)
	{
		delete now;
		now = next;
		next = now->next;
	}
	delete now;
}

void conflict_and_highlight_set_0(point *head)//conflict set 0
{
	int i;
	for (i = 1; i <= 81; i++)
	{
		(head-1+i)->conflict = 0;
		(head - 1 + i)->highlight = 0;
	}
}

void end_until_end(int X, int Y, char *note, int goxyornot)//������(X,Y)�����������С�����ʾ,����endʱ������֦,Ĭ��ת����(X,Y)
{
	int last_x, last_y;
	char c1, c2, c3, c;

	if (goxyornot)
		gotoxy(hout, X, Y);
	else
		cout << '\n';

	getxy(hout, last_x, last_y);
	cout << note;
	while (1)
	{
		cin >> c1;
		if (!check_if_a_char_ok(c1, note, 'e', 'e'))
		{
			showcinwrong(last_x, last_y, note);
			continue;
		}

		c2 = char(getchar());
		if (!check_if_a_char_ok(c2, note, 'n', 'n'))
		{
			showcinwrong(last_x, last_y, note);
			continue;
		}

		c3 = char(getchar());
		if (!check_if_a_char_ok(c3, note, 'd', 'd'))
		{
			showcinwrong(last_x, last_y, note);
			continue;
		}

		c = char(getchar());
		if (c != '\n')
		{
			cin.clear();
			cin.ignore(1024, '\n');
			showcinwrong(last_x, last_y, note);
			continue;
		}

		break;
	}
}

int check_if_a_char_ok(char c, char *note, char itshouldbefrom, char itshouldbeto)
{
	char ought;

	if (c == '\n')
	{
		return 0;
	}
	for (ought = itshouldbefrom; ought <= itshouldbeto; ought++)
	{
		if (c == ought)
			return 1;
	}
	if (itshouldbefrom >= 'a'&&itshouldbefrom <= 'z')//�������ʱ��ĸ������Դ�Сд
	{
		for (ought = capitalize(itshouldbefrom); ought <= capitalize(itshouldbeto); ought++)
		{
			if (c == ought)
				return 1;
		}
	}

	cin.clear();
	cin.ignore(1024, '\n');
	return 0;
}

char capitalize(char c)//�����ĸ�Ĵ�д
{
	if (c >= 'a'&&c <= 'z')
		return c - 'a' + 'A';

	return c;
}

void showcinwrong(int X, int Y, char *note, char *noteofwrong)//��ʾ�������,���ù��ظ���(X,Y),�ٴ����������С�����ʾ
{
	gotoxy(hout, X, Y);
	cout << note << "                                    \n";//����֮ǰ�������¼
	cout << noteofwrong;
	gotoxy(hout, X, Y);
	cout << note;
}

int get_user_input(int &pos,int &value, char *last_move)//��ȡ�û����룬�������bk����-1��������󷵻�0����ȷ����1
{
	int counts = 0;
	char input[4]={0},x;
	cout << "�밴��/��/ֵ�ķ�ʽ����(����:5c6=��5�е�c��Ϊ6)������bk��ʾ����һ�Σ�";

	while((x=getchar())!='\n')
	{
		if (counts < 3)
		{
			last_move[counts] = x;
			input[counts] = x;
		}

		counts++;
	}

	if(strcmp(input,"bk")==0)
	{
		pos = -1;
		return -1;
	}

	if (input[0] >= '1'&&input[0] <= '9')
	{
		if (input[1] >= 'a'&&input[1] <= 'z')
		{
			cout << input[3] << endl;
			if (input[2] >= '0'&&input[2] <= '9')
			{
				value = input[2] - '0';
				pos = (input[0] - '1') * 9 + input[1] - 'a';
				return 1;
			}
		}
	}

	return 0;
}

void all_char_set_0(char *x)//�ظ�����λΪβ0
{
	int i = 0;

	while (*(x + i))
	{
		x[i] = '\0';
		i++;
	}
}

void free_possible(point*head)//�ͷ�possible����
{
	int i;

	for(i=0;i<81;i++)
	{
		if ((head + i)->possible != NULL)
			delete[](head + i)->possible;
	}
}