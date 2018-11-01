/*1550431 ����� �ƿ�3��*/
//���Ӳ���
#include "90-b3.h"

int read_alarm_into_memory(fstream &saver, alarm *&head)//���ļ��е���Ϣ�����ڴ�
{
	alarm*now, *next;
	head = new(nothrow) alarm;
	if(head == NULL)
	{
		system("cls");
		cout << "��̬�ڴ�����ʧ��";
		return -1;
	}

	now = head;

	saver.clear();
	while(saver.peek()!=EOF)
	{
		now->alarm_time = new(nothrow) now_time;
		if(now->alarm_time==NULL)
		{
			system("cls");
			cout << "��̬�ڴ�����ʧ��";
			free_alarm(head);
			return -1;
		}
		saver >> now->type;
		saver >> now->alarm_time->year;
		saver >> now->alarm_time->month;
		saver >> now->alarm_time->day;
		saver >> now->alarm_time->week;
		saver >> now->alarm_time->hour;
		saver >> now->alarm_time->minute;
		saver >> now->alarm_time->second;

		next = new(nothrow) alarm;
		if (now->alarm_time == NULL)
		{
			system("cls");
			cout << "��̬�ڴ�����ʧ��";
			free_alarm(head);
			return -1;
		}

		now->next = next;
		now->next->previous = now;
		now = next;
	}

	now->type = 0;//���һ�����Ӵ���Ϊ��typeΪ0�������

	return 1;
}

void show_all_alarms(alarm *head, const int X, const int Y)//��X,Y�������������
{
	alarm*now;
	now_time now_t;
	int counts = 0;

	now = head;

	gotoxy(hout, X, Y);
	cout << "��ǰ��������:";
	counts++;

	get_now_time(&now_t);

	while(now->type)
	{
		gotoxy(hout, X, Y + counts++);
		cout << "����: ";
		switch(now->type)
		{
			//1����ʱ 2���� 3ÿ�� 4������
			case(1):
				cout << "����ʱ ";
				break;
			case(2):
				cout << "���� ";
				break;
			case(3):
				cout << "ÿ�� ";
				break;
			default:
				cout << "������ ";
					break;
		}

		cout << "����ʱ��: ";
		if (now->type == 1 || now->type == 2)
			cout << now->alarm_time->year << "�� " << now->alarm_time->month << "�� " << now->alarm_time->day << "�� " << now->alarm_time->hour << "ʱ " << now->alarm_time->minute << "�� " << now->alarm_time->second << "��";
		else
			cout <<  now->alarm_time->hour << "ʱ " << now->alarm_time->minute << "�� " << now->alarm_time->second << "��";


		now = now->next;
	}
}

int check_all_alarms(alarm *&head)//������������Ƿ�ʱ��
{
	alarm*now = head,*t;
	now_time now_t;
	int flag = 0;
	get_now_time(&now_t);

	now = head;
	while (now->type != 0 && now->next != NULL)
	{
		if(two_time_compare(&now_t,now->alarm_time)==-1)
		{
			now = now->next;
			continue;
		}
		else
		{
			if (now->type == 1 || now->type == 2) 
			{
				flag = 1;
				t = now;
				if (now->previous != NULL)
				{
					now->previous->next = now->next;
					now->next->previous = now->previous;
				}
				else
					head = now->next;

				now = t->next;
				delete t->alarm_time;
				delete t;
			}
			else if(now->type == 4)//������
			{
				if(now_t.week!=6&&now_t.week!=0)
				{
					flag = 1;
					now->alarm_time->day++;
					adjust_time(now->alarm_time);
				}
				now = now->next;
			}
			else if(now->type == 3)
			{
				flag = 1;
				now = now->next;
				now->alarm_time->day++;
				adjust_time(now->alarm_time);
			}
		}
	}

	return flag;
}

int new_alarm(alarm *&head)
{
	int i,j,k;
	alarm *new_head=new(nothrow) alarm;
	if (new_head== NULL)
	{
		system("cls");
		cout << "��̬�ڴ�����ʧ��";
		//free_alarm(head);
		return -1;
	}
	new_head->alarm_time = new(nothrow) now_time;
	if (new_head->alarm_time == NULL)
	{
		system("cls");
		cout << "��̬�ڴ�����ʧ��";
		//free_alarm(head);
		delete new_head;
		return -1;
	}

	system("cls");
	cout << "�������������� 1����ʱ 2���� 3ÿ�� 4������:";
	cin >> i;
	if (i < 1 || i>4)
	{
		cout << "�������";
		Sleep(1000);
		delete new_head->alarm_time;
		delete new_head;
		return 1;
	}

	new_head->type = i;

	if(i==1)
	{
		cout << "�����뵹��ʱСʱ��(0-23):";
		cin >>j;
		if (j <0||j>23)
		{
			cout << "�������";
			Sleep(1000);
			delete new_head->alarm_time;
			delete new_head;
			return 1;
		}

		cout << "�����뵹��ʱ������(0-59):";
		cin >> k;
		if (k <0 || k>59)
		{
			cout << "�������";
			Sleep(1000);
			delete new_head->alarm_time;
			delete new_head;
			return 1;
		}

		get_now_time(new_head->alarm_time);
		new_head->alarm_time->hour += j;
		new_head->alarm_time->minute += k;
		adjust_time(new_head->alarm_time);
	}
	else
	{
		cout << "����������Сʱ��(0-23):";
		cin >> j;
		if (j < 0 || j>23)
		{
			cout << "�������";
			Sleep(1000);
			delete new_head->alarm_time;
			delete new_head;
			return 1;
		}

		cout << "���������ӷ�����(0-59):";
		cin >> k;
		if (k < 0 || k>59)
		{
			cout << "�������";
			Sleep(1000);
			delete new_head->alarm_time;
			delete new_head;
			return 1;
		}

		get_now_time(new_head->alarm_time);
		if ((j < new_head->alarm_time->hour) || (j == new_head->alarm_time->hour&&k <= new_head->alarm_time->minute))
		{
			new_head->alarm_time->hour = j;
			new_head->alarm_time->minute = k;
			new_head->alarm_time->day++;
			adjust_time(new_head->alarm_time);
		}
		else
		{
			new_head->alarm_time->hour = j;
			new_head->alarm_time->minute = k;
		}
	}

	new_head->next = head;
	head->previous = new_head;
	head = new_head;

	return 1;
}