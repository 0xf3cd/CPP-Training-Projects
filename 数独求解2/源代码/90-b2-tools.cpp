/*1550431 计科3班 王甯琪*/
#include "90-b2.h"
//存放工具函数以及公用的函数

int get_files(char *name,char file_name[100][50], const int X, const int Y, int mode)//获取当前目录下所有文件名,返回-1代表出错
{
	char title[50]={"dir /b > "},filename[50];
	int lenth,no_file=0,i=0;
	ifstream fin;

	strcat_s(title, name);
	system(title);
	
	fin.open(name, ios::in);
	if(fin.is_open()==0)
	{
		cout << "\n文件打开失败\n";
		return -1;
	}

	//if打开成功
	if (mode == 1)
	{
		cout << "当前目录下符合sudoku*.txt的匹配文件有:\n";
		while (!fin.eof())
		{
			fin >> filename;
			lenth = strlen(filename);

			if ((strncmp(filename, "sudoku", 6) == 0) && (strncmp(&filename[lenth - 4], ".txt", 4) == 0))//如果文件名符合 sudoku*.txt形式则输出
			{
				no_file = 1;
				cout << filename << endl;
			}
		}
	}
	else//2-3小题制作储存文件名的char *数组
	{
		i = 0;
		while (!fin.eof())
		{
			fin >> filename;
			lenth = strlen(filename);

			if ((strncmp(filename, "sudoku", 6) == 0) && (strncmp(&filename[lenth - 4], ".txt", 4) == 0))//如果文件名符合 sudoku*.txt形式则输出
			{
				no_file = 1;
				strcpy_s(file_name[i], filename);
				i++;
			}
		}
	}
	
	if (no_file == 0)
	{
		cout << "无符合要求文件";
		Sleep(500);
		return -1;
	}
	
	fin.close();

	return 0;
}

void free_space(step *head)//释放储存步数的链表
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

void end_until_end(int X, int Y, char *note, int goxyornot)//在坐标(X,Y)处输出结束本小题的提示,输入end时跳出分枝,默认转移至(X,Y)
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
	if (itshouldbefrom >= 'a'&&itshouldbefrom <= 'z')//如果输入时字母，需忽略大小写
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

char capitalize(char c)//输出字母的大写
{
	if (c >= 'a'&&c <= 'z')
		return c - 'a' + 'A';

	return c;
}

void showcinwrong(int X, int Y, char *note, char *noteofwrong)//提示输入错误,并让光标回复到(X,Y),再次输出结束本小题的提示
{
	gotoxy(hout, X, Y);
	cout << note << "                                    \n";//消除之前的输入记录
	cout << noteofwrong;
	gotoxy(hout, X, Y);
	cout << note;
}

int get_user_input(int &pos,int &value, char *last_move)//读取用户输入，如果输入bk返回-1，输入错误返回0，正确返回1
{
	int counts = 0;
	char input[4]={0},x;
	cout << "请按行/列/值的方式输入(例如:5c6=第5行第c列为6)，输入bk表示回退一次：";

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

void all_char_set_0(char *x)//回复所有位为尾0
{
	int i = 0;

	while (*(x + i))
	{
		x[i] = '\0';
		i++;
	}
}

void free_possible(point*head)//释放possible数组
{
	int i;

	for(i=0;i<81;i++)
	{
		if ((head + i)->possible != NULL)
			delete[](head + i)->possible;
	}
}