/*1550431 �ƿ�3�� �����*/
#include "90-b1.h"

//��������ڱ�CPP�ĺ���
void menu(int &branch);
void which_way_to_go(int branch);
//���ֲ˵���Ҫ������ʽ��ʼǰ������ϵ�е�����ʹ�õ���������̲���������������������ͬɫ��
//��Ϊ����϶࣬ͬʱ�ж���˵���ʹ�ã����Ե�����װ�ɺ���
void for_start(point * const map, const int h, const int l, const int X, const int Y, const int last_x, const int last_y, const int whether_wait_for_enter = 1);//������Ĭ����1�����ֲ�����Ҫ�ȴ��س�������
void add_up_scores_and_go_on(point * const map, const int h, const int l, const int X, const int Y);//ͳ�ƽ�����÷ֲ��ҽ����µ����

int main()
{
	int branch = -1;

	while (1)
	{
		system("cls");
		setconsoleborder(hout, 90, 40);
		setfontsize(hout, L"��������", 15);
		menu(branch);//����˵������õ��û������ѡ��

		if (branch == 0)
			break;
		if (branch < 0 || branch>9)
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
	cout << "-----------------------------------------------------\n1.�ڲ����飬���ɳ�ʼ״̬��Ѱ���Ƿ��г�ʼ��������\n2.�ڲ����飬������ʼ����������0�����䲢��0���\n"
		<< "3.�ڲ����飬������ʼ������������������ʾ\n4.n*n�Ŀ��(�޷ָ���)����ʾ��ʼ״̬�������ʾ5����\n5.n*n�Ŀ��(�зָ���)����ʾ��ʼ״̬\n"
		<< "6.n*n�Ŀ��(�зָ���)����ʾ��ʼ״̬����ʼ��������\n7.n*n�Ŀ��(�зָ���)��������ʼ�����������ʾ������ʾ\n8.cmdͼ�ν���������\n"
		<< "9.���ļ��ж�ȡ��������֤����������ʾ���㷨����ȷ��\n0.�˳�\n-----------------------------------------------------\n[��ѡ��0-9] ";

	branch = _getch() - '0';
	cout << branch << endl;
}

void which_way_to_go(int branch)
{
	system("cls");
	point map[h_max][l_max];
	int h, l, last_x, last_y, X = 0, Y = 0, fh, fl, th, tl, judge, i, j;

	if (branch != 9)
	{
		h = panduan(0, 0, "����������(5 - 9)��", h_min, h_max);
		l = panduan(0, 1, "����������(5 - 9)��", l_min, l_max);
	}

	switch (branch)
	{
		case(1):
		case(2):
			cout << "\n��ʼ���̣�\n";
			randomly_generate_map(*map, h, l);//��һ����Χ��������
			draw_basic_map(X, Y, *map, h, l, 0);//�����0,�����Ѿ�������ݼ������
			cout << "���س�������Ѱ�ҳ�ʼ��������Ĳ���...";
			wait_an_enter();
			if (!find_removable_points(*map, h, l))
			{
				cout << "\n�޿�������/(��o��)/~~\n";
			}
			else
			{
				cout << "\n��ʼ���������ͬɫ��ʶ����\n";
				draw_basic_map(X, Y, *map, h, l, 0, 1);//�����Ѿ�������ݼ������,�������

				if (branch == 2)//���������ĳ������
				{
					cout << "���س��������������������...";
					wait_an_enter();
					system("cls");
					move_points(*map, h, l);//�õ��ƶ�������̣���λcolorΪ0
					draw_basic_map(X, Y, *map, h, l, 0, 1);//���������,�������
					cout << "\n���س������в������...\n";
					wait_an_enter();
					fill_empty_points(*map, h, l);
					draw_basic_map(X, Y, *map, h, l, 0, 1);//�����Ѿ�������ݼ������,�������
					all_highlight_set_0(*map, h, l);
				}
			}
			end_until_end(X, Y, "��С�������������End����...  ", 0);
			break;

		case(3):
			randomly_generate_map(*map, h, l);//��һ����Χ��������
			if (!find_removable_points(*map, h, l))
			{
				cout << "\n�޿�������/(��o��)/~~\n";
			}
			else
			{
				while (1)
				{
					cout << "\n��ʼ���������ͬɫ��ʶ����\n";
					draw_basic_map(X, Y, *map, h, l, 0, 1);//�����Ѿ�������ݼ������,�������
					//����������������������������
					cout << "���س��������������������...";
					wait_an_enter();
					//system("cls");
					move_points(*map, h, l);//�õ��ƶ�������̣���λcolorΪ0
					draw_basic_map(X, Y, *map, h, l, 0, 1);//���������,�������
					cout << "\n���س������в������...\n";
					wait_an_enter();
					fill_empty_points(*map, h, l);
					draw_basic_map(X, Y, *map, h, l, 0, 1);//�����Ѿ�������ݼ������,�������
					all_highlight_set_0(*map, h, l);

					if (!find_removable_points(*map, h, l))
						break;
				}
			}

			cout << "��ʼ���޿�������\n\n��ѡ���������ʾ����ͬɫ��ʶ����\n";
			keys_highlight(*map, h, l);
			draw_basic_map(X, Y, *map, h, l, 0, 1);//�����Ѿ�������ݼ������,�������
			all_key_highlight_set_0(*map, h, l);
			end_until_end(X, Y, "��С�������������End����...  ", 0);
			break;

		case(4):
			cout << "\n��ʼ���̣�\n";
			randomly_generate_map(*map, h, l);//��һ����Χ��������
			draw_basic_map(X, Y, *map, h, l, 0);//�����0,�����Ѿ�������ݼ������

			cout << "\n���س�����ʾͼ��...";
			wait_an_enter();

			setfontsize(hout, L"������", 20);
			setconsoleborder(hout, 46, 25);
			system("cls");

			draw_primary_map(*map, X, Y, h, l);

			end_until_end(X, Y, "��С�������������End����...  ", 0);
			break;

		case(5):
			cout << "\n��ʼ���̣�\n";
			randomly_generate_map(*map, h, l);//��һ����Χ��������
			draw_basic_map(X, Y, *map, h, l, 0);//�����0,�����Ѿ�������ݼ������

			cout << "\n���س�����ʾͼ��...";
			wait_an_enter();

			setfontsize(hout, L"������", 20);
			setconsoleborder(hout, 46, 25);
			system("cls");
			draw_complex_map(*map, X, Y, h, l);

			end_until_end(X, Y, "��С�������������End����...  ", 0);
			break;

		case(6):
			cout << "\n��ʼ���̣�\n";
			randomly_generate_map(*map, h, l);//��һ����Χ��������
			draw_basic_map(X, Y, *map, h, l, 0);//�����0,�����Ѿ�������ݼ������

			cout << "\n���س�����ʾͼ��...";
			wait_an_enter();

			setfontsize(hout, L"������", 20);
			setconsoleborder(hout, 46, 25);
			system("cls");

			draw_complex_map(*map, X, Y + 1, h, l);
			getxy(hout, last_x, last_y);

			if (!find_removable_points(*map, h, l))//û�п�������
			{
				gotoxy(hout, X, Y);
				cout << "δ�ҵ���ʼ��������";
			}
			else
			{
				turn_emptyball_to_fullball(*map, X, Y + 1, h, l);
				all_highlight_set_0(*map, h, l);
			}

			end_until_end(last_x, last_y, "��С�������������End����...  ");
			break;

		case(7):
			X = 0;
			Y = 1;
			cout << "\n��ʼ���̣�\n";
			randomly_generate_map(*map, h, l);//��һ����Χ��������
			draw_basic_map(X, Y, *map, h, l, 0);//�����0,�����Ѿ�������ݼ������

			cout << "\n���س�����ʾͼ��...";
			wait_an_enter();

			setfontsize(hout, L"������", 22);
			setconsoleborder(hout, 46, 25);
			system("cls");

			draw_complex_map(*map, X, Y, h, l);
			getxy(hout, last_x, last_y);

			for_start(*map, h, l, X, Y, last_x, last_y);//ѭ���������������ĵ÷���ֱ���޷�����

			gotoxy(hout, last_x, last_y);
			cout << "���س�����ʾ����������ʾ...           \n";
			wait_an_enter();

			//������ʾ
			keys_highlight(*map, h, l);
			draw_keys_highlight_points(*map, X, Y, h, l);
			all_key_highlight_set_0(*map, h, l);

			end_until_end(last_x, last_y, "��С�������������End����...     ");
			break;

		case(8):
			X = 0;
			Y = 1;
			setfontsize(hout, L"������", 22);
			setconsoleborder(hout, 46, 25);
			system("cls");

			randomly_generate_map(*map, h, l);//��һ����Χ��������
			draw_complex_map(*map, X, Y, h, l);
			getxy(hout, last_x, last_y);

			//ѭ���������������ĵ÷���ֱ���޷�����
			//������㣬��������ͬɫ���ѵ��￪�������Ĺ��̲���Ҫ�ո������
			for_start(*map, h, l, X, Y, last_x, last_y, 0);

			//������ʾ
			keys_highlight(*map, h, l);
			draw_keys_highlight_points(*map, X, Y, h, l);
			all_key_highlight_set_0(*map, h, l);
			all_score_set_0(*map, h, l);

			show_scores_gotten(*map, X, Y, h, l);

			while (1)
			{
				if (game_over(*map, h, l) == 0)
					break;//��Ϸ����

				//���²��裺
				//1. �õ�����������������
				//2. ����������������
				//�����ض�ֵ-1���������Ҽ�������0�����ҵ������ڵĺϷ���ԣ�����1������ѡ�������򽻻����ܴ�������
				judge = from_mouse_get_position(*map, last_x, last_y, X, Y, h, l, fh, fl, th, tl);
				show_scores_gotten(*map, X, Y, h, l);

				if (judge == -1)//�����Ҽ�
					break;
				else if (judge == 1)//��ѡ�������򽻻����޷���������
				{
					draw_complex_map(*map, X, Y, h, l);

					//������ʾ
					all_key_highlight_set_0(*map, h, l);
					keys_highlight(*map, h, l);
					draw_keys_highlight_points(*map, X, Y, h, l);
					all_key_highlight_set_0(*map, h, l);
					all_score_set_0(*map, h, l);
					continue;
				}
				else//��ѡ�������򽻻����ܹ���������
				{
					//����
					move_2_points(*map, X, Y, fh, fl, th, tl, h, l);
					add_up_scores_and_go_on(*map, h, l, X, Y);//ͳ�ƽ�����������ĵ÷֣������

					draw_complex_map(*map, X, Y, h, l);

					//������ʾ
					keys_highlight(*map, h, l);
					draw_keys_highlight_points(*map, X, Y, h, l);
					all_key_highlight_set_0(*map, h, l);
					all_score_set_0(*map, h, l);

					continue;
				}
			}

			end_until_end(last_x, last_y + 1, "��Ϸ������������End����...     ");
			break;

		case(9):
			setconsoleborder(hout, 90, 50);
			char num[100], ought[17] = { "test\\" }, ought1[17] = { 0 }, ought2[17] = { 0 };
			ifstream fin, finans;

			cout << "������ѧ��(���� 1651234 ��Ӧ��� test\1651234.dat �ļ�)\n";
			cin >> num;

			if (strlen(num) != 7)
				cout << "�ļ���ʧ��";
			else
			{
				strcat_s(ought, num);
				strcat_s(ought1, ought);
				strcat_s(ought2, ought);
				strcat_s(ought1, ".dat");
				strcat_s(ought2, ".ans");

				fin.open(ought1, ios::in);
				finans.open(ought2, ios::in);

				if (fin.is_open() == 0 || finans.is_open() == 0)
					cout << "�ļ���ʧ��";
				else
				{
					fin >> h >> l;
					for (i = 0; i < h; i++)
					{
						for (j = 0; j < l; j++)
						{
							fin >> (*map + j + i*l_max)->color;
						}
					}
					fin.close();
					//�ļ��������
					cout << "��ʼ���飺";
					draw_basic_map(X, Y, *map, h, l, 0, 0);

					//�ɲ˵���3���ƶ���
					keys_highlight(*map, h, l);
					cout << "\n��ѡ���������ʾ����ͬɫ��ʶ����\n";
					draw_basic_map(X, Y, *map, h, l, 0, 1);//�����Ѿ�������ݼ������,�������
					all_key_highlight_set_0(*map, h, l);

					for (i = 0; i < h; i++)
					{
						for (j = 0; j < l; j++)
						{
							finans >> (*map + j + i*l_max)->color;

							if ((*map + j + i*l_max)->color > 90)
							{
								(*map + j + i*l_max)->color -= 90;
								(*map + j + i*l_max)->highlight = 1;
							}
						}
					}
					finans.close();

					cout << "\n���ļ�������:\n";
					draw_basic_map(X, Y, *map, h, l, 0, 1);//�����Ѿ�������ݼ������,�������
				}
			}

			end_until_end(X, Y, "��С�������������End����...  ", 0);
			break;
	}
}

void for_start(point * const map, const int h, const int l, const int X, const int Y, const int last_x, const int last_y, const int whether_wait_for_enter)//������Ĭ����1�����ֲ�����Ҫ�ȴ��س�������
{
	if (!find_removable_points(map, h, l))//û�п�������
	{
		gotoxy(hout, X, Y - 1);
		cout << "δ�ҵ���ʼ��������";
	}
	else
	{
		while (1)
		{
			turn_emptyball_to_fullball(map, X, Y, h, l);

			//����������������������������
			if (whether_wait_for_enter)
			{
				gotoxy(hout, last_x, last_y);
				cout << "���س��������������������...";
				wait_an_enter();
			}

			//����������ͬʱ����������ok
			draw_remove_points(map, X, Y, h, l);

			//������,��˼·���������е㣬��ÿ����Ӧ�����Ƶĸ��������һ������
			sum_up_downwards(map, h, l);
			draw_move_downwards(map, h, l, X, Y);
			all_downwards_set_0(map, h, l);

			if (whether_wait_for_enter)
			{
				gotoxy(hout, last_x, last_y);
				cout << "���س������в������...           \n";
				wait_an_enter();
			}

			//��̬����ok
			draw_fill_empty_points(map, X, Y, h, l);

			if (!find_removable_points(map, h, l))
			{
				if (whether_wait_for_enter)
				{
					gotoxy(hout, X, Y - 1);
					cout << "���޿�������";
				}
				break;
			}
		}
	}
}


void add_up_scores_and_go_on(point * const map, const int h, const int l, const int X, const int Y)//ͳ�ƽ�����÷ֲ��ҽ����µ����
{
	while (find_removable_points(map, h, l))
	{
		turn_emptyball_to_fullball(map, X, Y, h, l);

		//ͳ�Ƶ÷�
		show_scores_gotten(map, X, Y, h, l);

		//����������ͬʱ����������ok
		draw_remove_points(map, X, Y, h, l);

		//������,��˼·���������е㣬��ÿ����Ӧ�����Ƶĸ��������һ������
		sum_up_downwards(map, h, l);
		draw_move_downwards(map, h, l, X, Y);
		all_downwards_set_0(map, h, l);

		//��̬����ok
		draw_fill_empty_points(map, X, Y, h, l);

		if (!find_removable_points(map, h, l))
			break;
	}
}