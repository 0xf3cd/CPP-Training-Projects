/*1550431 �ƿ�3�� �����*/
#include "90-b2.h"
#include <ctime>
//��ŶԼ�¼�����������ͳ�ơ������ĺ���

int select_and_generate(point head[9][9], char file_name[100][50], const int X,const int Y,int &highlight,int &from,int mode)//���û������ļ�ѡ��,����������,������-1,���Ϸ�����0
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

		strcat_s(delete_, "all.txt");//����ɾ�����浱ǰĿ¼�������ļ����ֵ�txt�ļ���ָ��//ִ����ɺ�ɾ�����ɵ�txt�ļ�

		if (mode == 1)
		{
			i = 0;
			cout << "������������Ŀ�ļ���(�س���ʾĬ��sudoku.txt):";
			while ((x = char(getchar())) != '\n')
			{
				*(file_choose + i) = x;
				i++;
			}
		}
		else//2-3С�⣬��ʱֻ��ֻ���˴����ļ�����char *����
		{
			while(file_name[file_amounts][0]!=0)//�õ����з���Ҫ����ļ���
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
					gotoxy(hout, 0, 0);//��λ
					break;
				}
			}
		}

		fin.open(file_choose, ios::in);
		if (fin.is_open() == 0)
		{
			cout << "\n�ļ���ʧ��\n\n";
			Sleep(500);
			return -1;
		}
		else
			break;
	}
	std::system(delete_);//delete txt

	//��ʱ�����ʼ�������ļ��Ѿ���

	for (j = 0; j < l_max; j++)//������������������б�
	{
		for (k = 0; k < h_max; k++)
		{
			fin >> i;
			if (i)//�����һλ��Ϊ0�����ǲ��ܸ���
			{
				if (i < 0 || i>9)
				{
					cout << "�ļ����Ϸ�\n";
					return 0;
				}

				head[j][k].value = i;
				head[j][k].changable = 0;
			}
			if (fin.fail())//���ִ����ַ�
			{
				cout << "�ļ����Ϸ�\n";
				return 0;
			}
		}
	}

	//���ˣ�����������������������
	fin.close();
	return 1;
}

int check_valid(point *head)//return <0,conflict//�ж��Ƿ��г�ͻ����
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

int check_ghl_valid(point *start, int mode)//return -1,conflict//�ж�1 �� 2 һ�� 3 һ�� �Ƿ��г�ͻ������(�ֱ�Ϊ�����Ͻǵĵ�ַ����һ�е�һ������Ԫ�ص�ַ)
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

	for (i = 0; i < 9; i++)//�������з�0���ֲ�
		if (address[i]->value)
			check[address[i]->value]++;

	for (i = 0; i < 9; i++)
	{
		if (check[address[i]->value] > 1)//1��������Ѿ�����
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

void mark_highlight(point *start, int mode)//mode 1�� 2�� 3�� ��Ǹ��� 
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

int game_over(point *head)//�ж���Ϸ�Ƿ��������������򷵻�1������Ϊ0
{
	int i, j,k,gong_position[9]= { 1,2,3,10,11,12,19,20,21};
	point *address[9];

	//ÿһ��
	for(i=1;i<=3;i++)
	{
		for(j=1;j<=3;j++)
		{
			for(k=0;k<9;k++)//���ɵ�i�ŵ�j�����оŸ�Ԫ�صĵ�ַ����
			{
				address[k] = head + 27 * i - 27 + 3 * j - 3 + gong_position[k] - 1;
			}

			if (check_fulfill(address) == 0)
				return 0;
		}
	}

	//ÿһ��
	for(i=1;i<=9;i++)
	{
		for(j=1;j<=9;j++)
		{
			address[j - 1] = head - 1 + 9 * i - 8 - 1 + j;
		}

		if (check_fulfill(address) == 0)
			return 0;
	}

	//ÿһ��
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

int check_fulfill(point *address[9])//���9��λ���Ƿ���1-9������һ��//����1��������
{
	int i, show_up[10] = { 0 };

	for(i=0;i<9;i++)//��¼�Ÿ�λ���У�0-9���ֵ��ܴ���
		show_up[address[i]->value]++;

	for(i=1;i<=9;i++)
	{
		if (show_up[i] != 1)//���1-9��һ��������2�����ϣ���û�г��֣�����������������0
			return 0;
	}

	return 1;
}

int save_and_apply_steps(point *head,step *&s_now, const step *const s_head,int &res,char *last_move)//��¼���������ģ�����-1��������ռ�ʧ��
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

		if (check_valid(head) < 0)//����ͻ
			res = 1;
		else
			res = 2;
		return 0;
	}
	else if(flag==0)//�������
	{
		res = 3;
		return 0;
	}
	else//������ȷ
	{
		if ((head + pos)->changable)
		{
			s_next = new(nothrow) step;
			if (s_next == NULL)
			{
				system("cls");
				cout<< "\n�ڴ�����ʧ��";
				return -1;
			}

			//�ռ�����ɹ�
			s_now->next = s_next;
			s_next->previous = s_now;

			s_now->position = pos;//����˴β��������λ��
			s_now->change_from = (head + pos)->value;//��¼����ǰ��ֵ
			(head + pos)->value = value;//�޸�ֵ

			if (check_valid(head) < 0)//����ͻ
				res = 1;
			else
				res =2;

			s_now = s_next;//��������ת��
		}
		else//��λ�ò��ɱ��
			res = 4;

		return 0;
	}
}

int first_operation(point *head, int *&pos, int &fillable)//�ҳ���ͨ���ų���ȷ������������λ�ò�����1-9����ɺ�����һ����¼û���������ֵ�λ�õ����顣����-1��������ռ����
{
	int i,j;
	first_of_all_fill_in(head);// �ҳ����п��Գ��������λ�ã�������𰸣��������

	fillable = 0;
	for(i=0;i<h_max*l_max;i++)
	{
		if (!(head + i)->value)
			fillable++;
	}

	if (!fillable)//ȫ������
		return 0;

	pos = new(nothrow) int[fillable];
	if(pos==NULL)
	{
		system("cls");
		cout << "\n�ڴ�����ʧ��";
		return -1;
	}

	//�ڴ�����ɹ�
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

void first_of_all_fill_in(point *head)//�ҳ���ͨ���ų���ȷ������������λ�ò�����1-9
{
	int i,t_value,over=1;

	for(i=0;i<h_max*l_max;i++)
	{
		if((head+i)->value==0)
		{
			t_value=check_this_pos_fillable(head, i);

			if(t_value!=-1)//�ҵ��������Ψһֵ
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

int check_this_pos_fillable(point *head,int pos)//�ҳ���һλ�����������(��λVALUEΪ0��ǰ����),pos 0-80
{
	int h, l, possible[10] = { 1,1,1,1,1,1,1,1,1,1 }, i, j, counts = 0;
	point *now;
	h = 1 + (pos / 9);
	l = pos + 1 - 9 * (h - 1);
	//��λ��h��l��Ԫ��

	//��
	now = head + 9 * h - 9;//ָ����е�һ��Ԫ��
	for(i=0;i<9;i++)
	{
		if ((now + i)->value)
			possible[(now + i)->value] = 0;
	}
	
	//��
	now = head + l-1;//ָ����е�һ��Ԫ��
	for(i=0;i<9;i++)
	{
		if ((now + 9 * i)->value)
			possible[(now + 9 * i)->value] = 0;
	}

	//��
	now = head+((h-1)/3)*27+((l-1)/3)*3;//ָ��ù���һ��Ԫ��
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

	if (counts == 1)//��λ�����ֵֻ��1�ֿ���
	{
		for (i = 1; i <= 9; i++)
		{
			if (possible[i])
				return i;
		}
	}

	return -1;
}

void this_pos_set_0(point *x)//����λ���������0
{
	x->value = 0;
	x->all_fillable = 0;
	x->now_fill = 0;
	delete x->possible;
	x->possible = NULL;
}

int auto_steps(point *head, step * s_head, int* pos,int fillable,const int X,const int Y,double &time)//�Զ��߲������ģ�����-1��������ռ�ʧ��,0����û�н�,1��ʾ���
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
			cout << "��������:" << counts;
		}*/
		
		if(now_pos==fillable)//�������һ��
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

				//δ�ҵ������㡢����
				while ((head + pos[now_pos - 1])->now_fill == (head + pos[now_pos - 1])->all_fillable)//�����һλ�Ѿ����������������Ļ�
				{
					if (now_pos == 1)
						return 0;//�޽�

					this_pos_set_0(head + pos[now_pos - 1]);//����һλ����
					while ((s_now->previous)->position == now_pos)//������¼���ݣ����
					{
						s_now = s_now->previous;
						delete s_now->next;
						s_now->next = NULL;
					}

					now_pos--;
				}

				//����now_pos��Ӧ��λ�ÿ���ȡ��һ������ֵ��
				//��¼��һ���Ĳ���
				s_now->position = now_pos;
				s_now->change_from = (head + pos[now_pos - 1])->value;

				//�Ը�λ�ý�����ֵ����
				(head + pos[now_pos - 1])->value = *((head + pos[now_pos - 1])->possible + (head + pos[now_pos - 1])->now_fill);
				(head + pos[now_pos - 1])->now_fill++;

				//�Բ���������в���
				s_now->next = new(nothrow) step;
				if (s_now->next == NULL)
				{
					system("cls");
					cout << "\n�ڴ�����ʧ��";
					return -1;
				}
				(s_now->next)->previous = s_now;
				s_now = s_now->next;

				//λ������
				now_pos++;
			}
			else //flag==0
			{
				while ((head + pos[now_pos - 1])->now_fill == (head + pos[now_pos - 1])->all_fillable)//�����һλ�Ѿ����������������Ļ�
				{
					if (now_pos == 1)
						return 0;//�޽�

					this_pos_set_0(head + pos[now_pos - 1]);//����һλ����
					while ((s_now->previous)->position == now_pos)//������¼���ݣ����
					{
						s_now = s_now->previous;
						delete s_now->next;
						s_now->next = NULL;
					}

					now_pos--;
				}

				//����now_pos��Ӧ��λ�ÿ���ȡ��һ������ֵ��
				//��¼��һ���Ĳ���
				s_now->position = now_pos;
				s_now->change_from = (head + pos[now_pos - 1])->value;

				//�Ը�λ�ý�����ֵ����
				(head + pos[now_pos - 1])->value = *((head + pos[now_pos - 1])->possible + (head + pos[now_pos - 1])->now_fill);
				(head + pos[now_pos - 1])->now_fill++;

				//�Բ���������в���
				s_now->next = new(nothrow) step;
				if (s_now->next == NULL)
				{
					system("cls");
					cout << "\n�ڴ�����ʧ��";
					return -1;
				}
				(s_now->next)->previous = s_now;
				s_now = s_now->next;

				//λ������
				now_pos++;
			}
		}
		else//δ�����һ��
		{
			flag=make_this_pos_possible_shuzu(head, pos[now_pos-1]);
			if(flag==-1)
				return -1;
			else if(flag==0)//��������
			{
				//int a, b;
				//a = now_pos;
				while((head+pos[now_pos-1])->now_fill== (head + pos[now_pos - 1])->all_fillable)//�����һλ�Ѿ����������������Ļ�
				{
					if (now_pos == 1)
						return 0;//�޽�

					this_pos_set_0(head + pos[now_pos - 1]);//����һλ����
					while ((s_now->previous)->position==now_pos)//������¼���ݣ����
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

				//����now_pos��Ӧ��λ�ÿ���ȡ��һ������ֵ��
				//��¼��һ���Ĳ���
				s_now->position = now_pos;
				s_now->change_from = (head + pos[now_pos - 1])->value;

				//�Ը�λ�ý�����ֵ����
				(head + pos[now_pos - 1])->value = *((head + pos[now_pos - 1])->possible + (head + pos[now_pos - 1])->now_fill);
				(head + pos[now_pos - 1])->now_fill++;

				//�Բ���������в���
				s_now->next = new(nothrow) step;
				if (s_now->next == NULL)
				{
					system("cls");
					cout << "\n�ڴ�����ʧ��";
					return -1;
				}
				(s_now->next)->previous = s_now;
				s_now = s_now->next;

				//λ������
				now_pos++;
			}
			else//�����õ�possible����
			{
				//��¼��һ���Ĳ���
				s_now->position = now_pos;
				s_now->change_from = (head + pos[now_pos - 1])->value;

				//�Ը�λ�ý�����ֵ����
				(head + pos[now_pos - 1])->value = *((head + pos[now_pos - 1])->possible + (head + pos[now_pos - 1])->now_fill);
				(head + pos[now_pos - 1])->now_fill++;

				//�Բ���������в���
				s_now->next = new(nothrow) step;
				if(s_now->next==NULL)
				{
					system("cls");
					cout << "\n�ڴ�����ʧ��";
					return -1;
				}
				(s_now->next)->previous = s_now;
				s_now = s_now->next;

				//λ������
				now_pos++;
			}
		}
	}
}

int make_this_pos_possible_shuzu(point *head, int pos)//�Զ��������У��ҳ�ĳ��λ�������������,pos 0-80������0�����޿���������,-1����ռ�����ʧ��
{
	int h, l, possible[10] = { 1,1,1,1,1,1,1,1,1,1 }, i, j,k, counts = 0;
	point *now;
	h = 1 + (pos / 9);
	l = pos + 1 - 9 * (h - 1);
	//��λ��h��l��Ԫ��

	//��
	now = head + 9 * h - 9;//ָ����е�һ��Ԫ��
	for (i = 0; i<9; i++)
	{
		if ((now + i)->value)
			possible[(now + i)->value] = 0;
	}

	//��
	now = head + l - 1;//ָ����е�һ��Ԫ��
	for (i = 0; i<9; i++)
	{
		if ((now + 9 * i)->value)
			possible[(now + 9 * i)->value] = 0;
	}

	//��
	now = head + ((h - 1) / 3) * 27 + ((l - 1) / 3) * 3;//ָ��ù���һ��Ԫ��
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
			cout << "\n�ڴ�����ʧ��";
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