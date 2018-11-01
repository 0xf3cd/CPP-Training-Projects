/*1550431 计科3班 王甯琪*/
#include "90-b2.h"
#include <ctime>
//存放对记录数独链表进行统计、操作的函数

int select_and_generate(point head[9][9], char file_name[100][50], const int X,const int Y,int &highlight,int &from,int mode)//让用户进行文件选择,并生成链表,出错返回-1,不合法返回0
{
	int i, j, k,file_amounts = 0,select=1,min=8;
	char delete_[50] = { "del " };
	ifstream fin;
	highlight = 1;
	from = 1;

	while (1)
	{
		char x, file_choose[50] = "sudoku.txt";

		if (get_files("all.txt",file_name,X,Y,mode) == -1)
			return -1;

		strcat_s(delete_, "all.txt");//制作删除保存当前目录下所有文件名字的txt文件的指令//执行完成后删除生成的txt文件

		if (mode == 1)
		{
			i = 0;
			cout << "请输入数独题目文件名(回车表示默认sudoku.txt):";
			while ((x = char(getchar())) != '\n')
			{
				*(file_choose + i) = x;
				i++;
			}
		}
		else//2-3小题，此时只是只做了储存文件名的char *数组
		{
			while(file_name[file_amounts][0]!=0)//得到所有符合要求的文件数
			{
				file_amounts++;
			}

			if (file_amounts < min)
				min = file_amounts;

			while (1)
			{
				draw_file_choice(X, Y, from, highlight, file_name);

				x = _getch();
				if (x == -32)//up down left right
				{
					x = _getch();
					if (x == 72)//up
					{
						if (highlight > 1)
							highlight--;
						else if(highlight==1)
						{
							if (from > 1)
								from--;
						}

						if (select > 1)
							select--;
					}
					else if (x == 80)//down
					{
						if (highlight < min)
							highlight++;
						else if(highlight==min)
						{
							if (from < file_amounts - 7)
								from++;
						}

						if (select <file_amounts)
							select++;
					}
				}
				else if (x == '\r')
				{
					strcpy_s(file_choose, file_name[select-1]);
					gotoxy(hout, 0, 0);//归位
					break;
				}
			}
		}

		fin.open(file_choose, ios::in);
		if (fin.is_open() == 0)
		{
			cout << "\n文件打开失败\n\n";
			Sleep(500);
			return -1;
		}
		else
			break;
	}
	std::system(delete_);//delete txt

	//此时储存初始数独的文件已经打开

	for (j = 0; j < l_max; j++)//制作储存数独情况的列表
	{
		for (k = 0; k < h_max; k++)
		{
			fin >> i;
			if (i)//如果这一位不为0，则标记不能更变
			{
				if (i < 0 || i>9)
				{
					cout << "文件不合法\n";
					return 0;
				}

				head[j][k].value = i;
				head[j][k].changable = 0;
			}
			if (fin.fail())//出现错误字符
			{
				cout << "文件不合法\n";
				return 0;
			}
		}
	}

	//至此，储存情况的链表已制作完毕
	fin.close();
	return 1;
}

int check_valid(point *head)//return <0,conflict//判断是否有冲突数字
{
	int i, check[10] = { 0 }, gong_to_check[9] = { 1,4,7,28,31,34,55,58,61 }, conflict = 0;

	for (i = 0; i < 9; i++)//gong
		conflict += check_ghl_valid((head+ gong_to_check[i]-1), 1);

	for (i = 1; i <= 9; i++)//lie
		conflict += check_ghl_valid(head+i-1, 3);

	for (i = 1; i <= 9; i++)//hang
		conflict += check_ghl_valid(head-1+ 9 * i - 8, 2);

	return conflict;
}

int check_ghl_valid(point *start, int mode)//return -1,conflict//判断1 宫 2 一行 3 一列 是否有冲突的数字(分别为宫左上角的地址、第一行第一列所有元素地址)
{
	point *address[9];
	int i, j, counts = 0, check[10] = { 0 }, conflict = 0;

	if (mode == 1)
	{
		for (i = 0; i < 3; i++)
		{
			for (j = 1; j <= 3; j++)
			{
				address[counts] = start - 1 + 9 * i + j;
				counts++;
			}
		}
	}
	else if (mode == 2)
		for (j = 1; j <= 9; j++)
			address[j - 1] = start - 1 + j;
	else
	{
		for (j = 1; j <= 9; j++)
			address[j - 1] = start - 1 + 9 * j - 8;
	}

	for (i = 0; i < 9; i++)//储存所有非0数分布
		if (address[i]->value)
			check[address[i]->value]++;

	for (i = 0; i < 9; i++)
	{
		if (check[address[i]->value] > 1)//1代表该数已经存在
		{
			address[i]->conflict = 1;
			conflict = -1;
		}
	}


	if (mode == 1)
	{
		counts = 0;
		for (i = 0; i < 3; i++)
		{
			for (j = 1; j <= 3; j++)
			{
				if ((start-1+ 9 * i + j)->conflict)
					counts++;

					if(counts>=2)
						mark_highlight(start, 1);
			}
		}
	}
	else if (mode == 2)
	{
		counts = 0;
		for (j = 1; j <= 9; j++)
		{
			if ((start-1+ j)->conflict)
				counts++;

			if (counts >= 2)
				mark_highlight(start, 2);
		}
	}
	else
	{
		counts = 0;
		for (j = 1; j <= 9; j++)
			if ((start-1+ 9 * j - 8)->conflict)
				counts++;

		if (counts >= 2)
			mark_highlight(start, 3);
	}

	return conflict;
}

void mark_highlight(point *start, int mode)//mode 1宫 2行 3列 标记高亮 
{
	int i, j;

	if (mode == 1)
		for (i = 0; i < 3; i++)
			for (j = 1; j <= 3; j++)
				(start - 1 + 9 * i + j)->highlight = 1;
	else if (mode == 2)
		for (i = 1; i <= 9; i++)
			(start - 1 + i)->highlight = 1;
	else
		for (i = 1; i <= 9; i++)
			(start - 1 + 9 * i - 8)->highlight = 1;
}

int game_over(point *head)//判断游戏是否结束，如果结束则返回1，否则为0
{
	int i, j,k,gong_position[9]= { 1,2,3,10,11,12,19,20,21};
	point *address[9];

	//每一宫
	for(i=1;i<=3;i++)
	{
		for(j=1;j<=3;j++)
		{
			for(k=0;k<9;k++)//生成第i排第j个宫中九个元素的地址数组
			{
				address[k] = head + 27 * i - 27 + 3 * j - 3 + gong_position[k] - 1;
			}

			if (check_fulfill(address) == 0)
				return 0;
		}
	}

	//每一行
	for(i=1;i<=9;i++)
	{
		for(j=1;j<=9;j++)
		{
			address[j - 1] = head - 1 + 9 * i - 8 - 1 + j;
		}

		if (check_fulfill(address) == 0)
			return 0;
	}

	//每一列
	for (i = 1; i <= 9; i++)
	{
		for (j = 1; j <= 9; j++)
		{
			address[j - 1] = head - 1 + i - 1 + 9 * j - 8;
		}

		if (check_fulfill(address) == 0)
			return 0;
	}

	return 1;
}

int check_fulfill(point *address[9])//检查9个位置是否是1-9各出现一次//返回1代表满足
{
	int i, show_up[10] = { 0 };

	for(i=0;i<9;i++)//记录九个位置中，0-9出现的总次数
		show_up[address[i]->value]++;

	for(i=1;i<=9;i++)
	{
		if (show_up[i] != 1)//如果1-9有一个数出现2次以上，或没有出现，则不满足条件，返回0
			return 0;
	}

	return 1;
}

int save_and_apply_steps(point *head,step *&s_now, const step *const s_head,int &res,char *last_move)//记录步数并更改，返回-1代表申请空间失败
{
	step *s_next;
	int pos, value,flag;
	
	flag=get_user_input(pos, value,last_move);
	if(flag==-1)//bk
	{
		if (s_now == s_head)
		{
			res= 0;
			return 0;
		}

		(head + (s_now->previous)->position)->value = (s_now->previous)->change_from;
		s_next = s_now;
		s_now = s_now->previous;
		delete s_next;

		if (check_valid(head) < 0)//检查冲突
			res = 1;
		else
			res = 2;
		return 0;
	}
	else if(flag==0)//输入错误
	{
		res = 3;
		return 0;
	}
	else//输入正确
	{
		if ((head + pos)->changable)
		{
			s_next = new(nothrow) step;
			if (s_next == NULL)
			{
				system("cls");
				cout<< "\n内存申请失败";
				return -1;
			}

			//空间申请成功
			s_now->next = s_next;
			s_next->previous = s_now;

			s_now->position = pos;//保存此次操作对象的位置
			s_now->change_from = (head + pos)->value;//记录操作前的值
			(head + pos)->value = value;//修改值

			if (check_valid(head) < 0)//检查冲突
				res = 1;
			else
				res =2;

			s_now = s_next;//工作重心转移
		}
		else//该位置不可变更
			res = 4;

		return 0;
	}
}

int first_operation(point *head, int *&pos, int &fillable)//找出能通过排除法确定的所有数独位置并填入1-9。完成后生成一个记录没有填入数字的位置的数组。返回-1代表申请空间错误
{
	int i,j;
	first_of_all_fill_in(head);// 找出所有可以初步填入的位置，并填入答案（摒除法）

	fillable = 0;
	for(i=0;i<h_max*l_max;i++)
	{
		if (!(head + i)->value)
			fillable++;
	}

	if (!fillable)//全被填满
		return 0;

	pos = new(nothrow) int[fillable];
	if(pos==NULL)
	{
		system("cls");
		cout << "\n内存申请失败";
		return -1;
	}

	//内存申请成功
	j = 0;
	for (i = 0; i<h_max*l_max; i++)
	{
		if (!(head + i)->value)
		{
			pos[j] = i;
			j++;
		}
	}

	return 1;
}

void first_of_all_fill_in(point *head)//找出能通过排除法确定的所有数独位置并填入1-9
{
	int i,t_value,over=1;

	for(i=0;i<h_max*l_max;i++)
	{
		if((head+i)->value==0)
		{
			t_value=check_this_pos_fillable(head, i);

			if(t_value!=-1)//找到可填入的唯一值
			{
				over = 0;
				(head + i)->value = t_value;
			}
		}
	}

	if (over)
		return;
	else
		first_of_all_fill_in(head);
}

int check_this_pos_fillable(point *head,int pos)//找出这一位能填入的数字(该位VALUE为0的前提下),pos 0-80
{
	int h, l, possible[10] = { 1,1,1,1,1,1,1,1,1,1 }, i, j, counts = 0;
	point *now;
	h = 1 + (pos / 9);
	l = pos + 1 - 9 * (h - 1);
	//该位是h行l个元素

	//行
	now = head + 9 * h - 9;//指向该行第一个元素
	for(i=0;i<9;i++)
	{
		if ((now + i)->value)
			possible[(now + i)->value] = 0;
	}
	
	//列
	now = head + l-1;//指向该列第一个元素
	for(i=0;i<9;i++)
	{
		if ((now + 9 * i)->value)
			possible[(now + 9 * i)->value] = 0;
	}

	//宫
	now = head+((h-1)/3)*27+((l-1)/3)*3;//指向该宫第一个元素
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			if ((now + 9 * i + j)->value)
				possible[(now + 9 * i + j)->value] = 0;
		}
	}

	for(i=1;i<=9;i++)
	{
		if (possible[i])
			counts++;
	}

	if (counts == 1)//该位填入的值只有1种可能
	{
		for (i = 1; i <= 9; i++)
		{
			if (possible[i])
				return i;
		}
	}

	return -1;
}

void this_pos_set_0(point *x)//将该位相关数据置0
{
	x->value = 0;
	x->all_fillable = 0;
	x->now_fill = 0;
	delete x->possible;
	x->possible = NULL;
}

int auto_steps(point *head, step * s_head, int* pos,int fillable,const int X,const int Y,double &time)//自动走步并更改，返回-1代表申请空间失败,0代表没有解,1表示完成
{
	DWORD t1, t2;
	t1= GetTickCount();

	int now_pos=1,flag,i,times=0,counts=0;
	step *s_now = s_head;

	while(1)
	{
		/*times++;

		if(times==1000)
		{
			times = 0;
			counts++;
			system("cls");
			draw_complex_sudoku(head, X, Y, 1);
			gotoxy(hout, X, Y + 29);
			cout << "搜索次数:" << counts;
		}*/
		
		if(now_pos==fillable)//到达最后一个
		{
			flag = make_this_pos_possible_shuzu(head, pos[now_pos - 1]);
			if (flag == -1)
				return -1;
			else if(flag==1)//normally get
			{
				for(i=0;i<(head+ pos[now_pos - 1])->all_fillable;i++)
				{
					(head + pos[now_pos - 1])->value = *((head + pos[now_pos - 1])->possible + (head + pos[now_pos - 1])->now_fill);
					(head + pos[now_pos - 1])->now_fill++;

					if (game_over(head))
					{
						 t2 = GetTickCount();
					     time= double((t2 - t1));
						return 1;//find it!
					}
				}

				//未找到，置零、回溯
				while ((head + pos[now_pos - 1])->now_fill == (head + pos[now_pos - 1])->all_fillable)//如果这一位已经填完或者无数可填的话
				{
					if (now_pos == 1)
						return 0;//无解

					this_pos_set_0(head + pos[now_pos - 1]);//将这一位清零
					while ((s_now->previous)->position == now_pos)//步数记录回溯，清除
					{
						s_now = s_now->previous;
						delete s_now->next;
						s_now->next = NULL;
					}

					now_pos--;
				}

				//现在now_pos对应的位置可以取下一个可行值了
				//记录这一步的操作
				s_now->position = now_pos;
				s_now->change_from = (head + pos[now_pos - 1])->value;

				//对该位置进行数值更改
				(head + pos[now_pos - 1])->value = *((head + pos[now_pos - 1])->possible + (head + pos[now_pos - 1])->now_fill);
				(head + pos[now_pos - 1])->now_fill++;

				//对步数链表进行操作
				s_now->next = new(nothrow) step;
				if (s_now->next == NULL)
				{
					system("cls");
					cout << "\n内存申请失败";
					return -1;
				}
				(s_now->next)->previous = s_now;
				s_now = s_now->next;

				//位置下移
				now_pos++;
			}
			else //flag==0
			{
				while ((head + pos[now_pos - 1])->now_fill == (head + pos[now_pos - 1])->all_fillable)//如果这一位已经填完或者无数可填的话
				{
					if (now_pos == 1)
						return 0;//无解

					this_pos_set_0(head + pos[now_pos - 1]);//将这一位清零
					while ((s_now->previous)->position == now_pos)//步数记录回溯，清除
					{
						s_now = s_now->previous;
						delete s_now->next;
						s_now->next = NULL;
					}

					now_pos--;
				}

				//现在now_pos对应的位置可以取下一个可行值了
				//记录这一步的操作
				s_now->position = now_pos;
				s_now->change_from = (head + pos[now_pos - 1])->value;

				//对该位置进行数值更改
				(head + pos[now_pos - 1])->value = *((head + pos[now_pos - 1])->possible + (head + pos[now_pos - 1])->now_fill);
				(head + pos[now_pos - 1])->now_fill++;

				//对步数链表进行操作
				s_now->next = new(nothrow) step;
				if (s_now->next == NULL)
				{
					system("cls");
					cout << "\n内存申请失败";
					return -1;
				}
				(s_now->next)->previous = s_now;
				s_now = s_now->next;

				//位置下移
				now_pos++;
			}
		}
		else//未达最后一个
		{
			flag=make_this_pos_possible_shuzu(head, pos[now_pos-1]);
			if(flag==-1)
				return -1;
			else if(flag==0)//无数可填
			{
				//int a, b;
				//a = now_pos;
				while((head+pos[now_pos-1])->now_fill== (head + pos[now_pos - 1])->all_fillable)//如果这一位已经填完或者无数可填的话
				{
					if (now_pos == 1)
						return 0;//无解

					this_pos_set_0(head + pos[now_pos - 1]);//将这一位清零
					while ((s_now->previous)->position==now_pos)//步数记录回溯，清除
					{
						s_now = s_now->previous;
						delete s_now->next;
						s_now->next = NULL;
					}

					now_pos--;
				}

				/*b= now_pos;
				gotoxy(hout, 0, 0);
				cout << a << ' ' << b<<' ';
				cout << (s_now->previous)->position;
				getchar();*/

				//现在now_pos对应的位置可以取下一个可行值了
				//记录这一步的操作
				s_now->position = now_pos;
				s_now->change_from = (head + pos[now_pos - 1])->value;

				//对该位置进行数值更改
				(head + pos[now_pos - 1])->value = *((head + pos[now_pos - 1])->possible + (head + pos[now_pos - 1])->now_fill);
				(head + pos[now_pos - 1])->now_fill++;

				//对步数链表进行操作
				s_now->next = new(nothrow) step;
				if (s_now->next == NULL)
				{
					system("cls");
					cout << "\n内存申请失败";
					return -1;
				}
				(s_now->next)->previous = s_now;
				s_now = s_now->next;

				//位置下移
				now_pos++;
			}
			else//正常得到possible数组
			{
				//记录这一步的操作
				s_now->position = now_pos;
				s_now->change_from = (head + pos[now_pos - 1])->value;

				//对该位置进行数值更改
				(head + pos[now_pos - 1])->value = *((head + pos[now_pos - 1])->possible + (head + pos[now_pos - 1])->now_fill);
				(head + pos[now_pos - 1])->now_fill++;

				//对步数链表进行操作
				s_now->next = new(nothrow) step;
				if(s_now->next==NULL)
				{
					system("cls");
					cout << "\n内存申请失败";
					return -1;
				}
				(s_now->next)->previous = s_now;
				s_now = s_now->next;

				//位置下移
				now_pos++;
			}
		}
	}
}

int make_this_pos_possible_shuzu(point *head, int pos)//自动求解过程中，找出某个位置能填入的数字,pos 0-80。返回0代表无可填入数字,-1代表空间申请失败
{
	int h, l, possible[10] = { 1,1,1,1,1,1,1,1,1,1 }, i, j,k, counts = 0;
	point *now;
	h = 1 + (pos / 9);
	l = pos + 1 - 9 * (h - 1);
	//该位是h行l个元素

	//行
	now = head + 9 * h - 9;//指向该行第一个元素
	for (i = 0; i<9; i++)
	{
		if ((now + i)->value)
			possible[(now + i)->value] = 0;
	}

	//列
	now = head + l - 1;//指向该列第一个元素
	for (i = 0; i<9; i++)
	{
		if ((now + 9 * i)->value)
			possible[(now + 9 * i)->value] = 0;
	}

	//宫
	now = head + ((h - 1) / 3) * 27 + ((l - 1) / 3) * 3;//指向该宫第一个元素
	for (i = 0; i<3; i++)
	{
		for (j = 0; j<3; j++)
		{
			if ((now + 9 * i + j)->value)
				possible[(now + 9 * i + j)->value] = 0;
		}
	}

	for (i = 1; i <= 9; i++)
	{
		if (possible[i])
			counts++;
	}

	if(counts)
	{
		(head + pos)->all_fillable = counts;

		(head + pos)->possible = new(nothrow) int[counts];
		if((head + pos)->possible==NULL)
		{
			system("cls");
			cout << "\n内存申请失败";
			return -1;
		}

		k = 0;
		for (i = 1; i <= 9; i++)
		{
			if (possible[i])
			{
				*((head + pos)->possible + k) = i;
				k++;
			}
		}

		return 1;
	}

	return 0;
}