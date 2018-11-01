/*1550431 ����� �ƿ�3��*/
//�������Ͳ˵����ֺ���
#include "90-b3.h"
void menu(int &branch);
void which_way_to_go(int branch);

int main()
{
	int branch = -1;

	while (1)
	{
		system("cls");
		setconsoleborder(hout, 120, 40);
		setfontsize(hout, L"��������", 15);
		menu(branch);//����˵������õ��û������ѡ��

		if (branch == 0)
			break;
		if (branch < 0 || branch>3)
			branch = -1;
		else
		{
			which_way_to_go(branch);//����˵���
			branch = -1;
		}
	}

	return 0;
}


void menu(int &branch)
{
	cout << "------------------------------------------------------------------------\n1.ָ��ʽʱ��(F9���˳� F11���л�������ʽʱ�� F12���л�������)\n"
		<< "2.����ʽʱ��(F9���˳� F10���л���ָ��ʽʱ�� F12���л�������)\n"
		<<"3.����(F9���˳� F10���л���ָ��ʽʱ�� F11���л�������ʽʱ��)\n0.�˳�\n"
		<< "------------------------------------------------------------------------\n[��ѡ��0-3] ";
	
	branch = _getch() - '0';
	cout << branch << endl;
}

void which_way_to_go(int branch)
{
	int flag, loop, temp, which = branch,i;
	const int central_X = 180, central_Y = 90, R = 80,num_X=-4,num_Y=15,num_c=20,num_k=16;
	now_time tm;
	point *circle_first, *kedu_first, *shizhen_first, *fenzhen_first, *miaozhen_first, *num[11],*all_num;
	fstream alarm_saver;
	alarm *alarm_head;

	if (generate_10_nums(num, num_c, num_k) == -1)
		return;

	alarm_saver.open(".\\1550431\\alarm.save",ofstream::out|ios::app);
	if(alarm_saver.is_open()==0)
	{
		system("cls");
		cout << "�ļ���ʧ��" << endl;
		Sleep(5000);
		return;
	}
	alarm_saver.close();

	while (which)
	{
		loop = 1;
		if(which==1)//ָ��ʽ
		{
			system("cls");
			setfontsize(hout, L"��������", 1);
			setconsoleborder(hout, 360, 180);
			//setfontsize(hout, L"��������", 1);

			flag = generate_circle(circle_first, central_X, central_Y, R);
			if (flag == -1)//����
				return;

			flag = generate_kedu(kedu_first, central_X, central_Y, R, 8);
			if (flag == -1)//����
			{
				free_points(circle_first);
				return;
			}

			get_now_time(&tm);//tm�д�����Щ��ʱ��Ԫ��
			flag = generate_zhen(&tm, shizhen_first, fenzhen_first, miaozhen_first, central_X, central_Y);
			if (flag == -1)//����
			{
				free_points(circle_first);
				free_points(kedu_first);
				return;
			}

			draw_points(circle_first, '.');
			draw_points(kedu_first, '.');
			draw_points(shizhen_first, '.');
			draw_points(fenzhen_first, '.');
			draw_points(miaozhen_first, '.');

			while (loop)
			{
				if (_kbhit())
				{
					temp = _getch();
					if (temp == 0)
					{
						temp = _getch();
						if (temp == 67)//F9
						{
							//loop = 0;
							which = 0;
							free_points(circle_first);
							free_points(kedu_first);
							free_points(shizhen_first);
							free_points(fenzhen_first);
							free_points(miaozhen_first);
							break;
						}
						else if (temp == 68)//F10
						{
							//loop = 0;
							which = 1;
							free_points(circle_first);
							free_points(kedu_first);
							free_points(shizhen_first);
							free_points(fenzhen_first);
							free_points(miaozhen_first);
							break;
							//break;
						}
					}
					else if (temp == 224)
					{
						temp = _getch();
						if (temp == 133)//F11
						{
							//loop = 0;
							which = 2;
							free_points(circle_first);
							free_points(kedu_first);
							free_points(shizhen_first);
							free_points(fenzhen_first);
							free_points(miaozhen_first);
							break;
							//break;
						}
						else if (temp == 134)//F12
						{
							//loop = 0;
							which = 3;
							free_points(circle_first);
							free_points(kedu_first);
							free_points(shizhen_first);
							free_points(fenzhen_first);
							free_points(miaozhen_first);
							break;
							//break;
						}
					}
				}

				draw_points(shizhen_first, ' ');
				draw_points(fenzhen_first, ' ');
				draw_points(miaozhen_first, ' ');
				free_points(shizhen_first);
				free_points(fenzhen_first);
				free_points(miaozhen_first);

				get_now_time(&tm);//tm�д�����Щ��ʱ��Ԫ��
				flag = generate_zhen(&tm, shizhen_first, fenzhen_first, miaozhen_first, central_X, central_Y);
				if (flag == -1)//����
				{
					free_points(circle_first);
					free_points(kedu_first);
					return;
				}

				draw_points(shizhen_first, '.');
				draw_points(fenzhen_first, '.');
				draw_points(miaozhen_first, '.');

				until_time_change(tm);
			}
		}
		else if(which==2)//����ʽ
		{
			system("cls");
			setfontsize(hout, L"��������", 1);
			setconsoleborder(hout, 180, 60);
			//setfontsize(hout, L"��������", 1);

			get_now_time(&tm);//tm�д�����Щ��ʱ��Ԫ��
			flag = combime_nums(&tm, num, all_num, num_k, num_X, num_Y);
			if(flag==-1)
			{
				for (i = 0; i < 11; i++)
					free_points(num[i]);
			}
			draw_points(all_num, '*');

			while (loop)
			{
				if (_kbhit())
				{
					temp = _getch();
					if (temp == 0)
					{
						temp = _getch();
						if (temp == 67)//F9
						{
							loop = 0;
							which = 0;
							//clear_point_link(all_num);
							free_points(all_num);
							break;
						}
						else if (temp == 68)//F10
						{
							loop = 0;
							which = 1;
							free_points(all_num);
							break;
						}
					}
					else if (temp == 224)
					{
						temp = _getch();
						if (temp == 133)//F11
						{
							loop = 0;
							which = 2;
							free_points(all_num);
							break;
						}
						else if (temp == 134)//F12
						{
							loop = 0;
							which = 3;
							free_points(all_num);
							break;
						}
					}
				}

				//getchar();
				draw_points(all_num, ' ');
				free_points(all_num);
				get_now_time(&tm);//tm�д�����Щ��ʱ��Ԫ��
				flag = combime_nums(&tm, num, all_num, num_k, num_X, num_Y);
				if (flag == -1)
				{
					for (i = 0; i < 11; i++)
						free_points(num[i]);
				}
				//getchar();
				draw_points(all_num, '*');

				until_time_change(tm);
			}
		}
		else//����
		{
			//play_music();
			alarm_saver.open(".\\1550431\\alarm.save");
			if (alarm_saver.is_open() == 0)
			{
				system("cls");
				cout << "�ļ���ʧ��" << endl;
				Sleep(5000);
				return;
			}
			//play_music();
			system("cls");
			setconsoleborder(hout, 120, 40);
			setfontsize(hout, L"��������", 15);

			if (read_alarm_into_memory(alarm_saver, alarm_head) == -1)
				return;
			while (check_all_alarms(alarm_head))
				;

			while (loop)
			{
				system("cls");

				if (_kbhit())
				{
					temp = _getch();
					if (temp == 0)
					{
						temp = _getch();
						if (temp == 67)//F9
						{
							which = 0;
							alarm_saver.close();
							alarm_saver.open(".\\1550431\\alarm.save", ios::out | ios::binary);
							output_to_file(alarm_saver, alarm_head);
							alarm_saver.close();
							break;
						}
						else if (temp == 68)//F10
						{
							which = 1;
							alarm_saver.close();
							alarm_saver.open(".\\1550431\\alarm.save", ios::out | ios::binary);
							output_to_file(alarm_saver, alarm_head);
							alarm_saver.close();
							break;
						}
						else if(temp==66)//F8
						{
							new_alarm(alarm_head);
							//alarm *rt = alarm_head;
							//show_all_alarms(alarm_head, 0, 4);
							//break;
						}
					}
					else if (temp == 224)
					{
						temp = _getch();
						if (temp == 133)//F11
						{
							which = 2;
							alarm_saver.close();
							alarm_saver.open(".\\1550431\\alarm.save", ios::out | ios::binary);
							output_to_file(alarm_saver, alarm_head);
							alarm_saver.close();
							break;
						}
						else if (temp == 134)//F12
						{
							which = 3;
							alarm_saver.close();
							alarm_saver.open(".\\1550431\\alarm.save", ios::out | ios::binary);
							output_to_file(alarm_saver, alarm_head);
							alarm_saver.close();
							break;
						}
					}
				}

				//Sleep(5000);

				show_all_alarms(alarm_head, 0, 4);
				if (check_all_alarms(alarm_head) == 1)
				{
					play_music();
					continue;
				}
				//Sleep(2000);
				//free_alarm(alarm_head);

				get_now_time(&tm);//tm�д�����Щ��ʱ��Ԫ��
				print_now_time(&tm);
				cout << "\n��F8�½�����,F9�˳�";
				until_time_change(tm);
			}
		}
	}
}