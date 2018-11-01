/*1550431 �ƿ�3�� �����*/
#include "90-b2.h"
//��������ڱ�CPP�ĺ���
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
		if (branch < 0 || branch>choice)
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
	cout << "-----------------------------------------------------\n1.�ַ�������Ϸ(�����˹���)\n"
		<< "2.ͼ�ν�����Ϸ(�����˹���)\n"
		<< "3.ͼ�ν����Զ���(��ʾ���̲�����ʱ)\n0.�˳�\n"
		<< "-----------------------------------------------------\n[��ѡ��0-3] ";

	branch = _getch() - '0';
	cout << branch << endl;
}

void which_way_to_go(int branch)
{
	system("cls");
	int flag, check, choice_X = 80, choice_Y = 3, complex_X = 3, complex_Y = 1, highlight, from, res, *pos, fillable;//XY��2-3С��ѡ���ļ���ڵ�����
	char file_name[100][50] = { 0 }, *all_res[] = { "���ɻ���Ŷ~\n" ,"������ͻ\n","����������ȷ\n" ,"��������Ŷ~\n" ,"��λ�ò��ɱ��\n" ," " }, last_move[40] = { 0 };
	point map[9][9];
	step *s_head = new(nothrow) step, *s_now=s_head;
	if (s_head == NULL)
	{
		system("cls");
		cout << "\n�ڴ�����ʧ��";
		end_until_end(0, 0);
		return;
	}

	flag = select_and_generate(map, file_name, choice_X, choice_Y, highlight, from, branch);
	if (flag == -1 || flag == 0)//ѡ���ļ�����������ʱ����(��������ռ�������ں����ڲ��Ѿ��ͷſռ�)(����ԭ�����ں����ڲ�������ʾ)
	{
		free_space(s_head);//�ͷŴ�����������в����Ŀռ�
		end_until_end(0, 0);
		return;
	}

	//���������������
	check = check_valid(*map);
	if (check < 0)//conflict
	{
		//print the map with the conflict points highlighted
		if (branch == 1)
			draw_basic_sudoku(*map, 0, 0);
		else
			draw_complex_sudoku(*map, complex_X, complex_Y, branch - 1);
		cout << "\nԭʼ�����ļ��д����޸���ȷ�����\n";
		end_until_end(0, 0);
		free_space(s_head);
		return;
	}

	//�ļ������һ��ʼ���г�ͻ������Ѿ��ų�
	//now,һ�����������Կ�ʼ

	//����û�����
	//����STEP����
	//���������и���

	if (branch == 1 || branch == 2)
	{
		res = 5;
		s_now = s_head;
		while (!game_over(*map))//����ѭ��(��������Ϸ��������ʱ)
		{
			if (branch == 1)//��ͼ
			{
				output_res(all_res[res], 0, 0, 0);
				draw_basic_sudoku(*map, 0, 0);
			}
			else
			{
				system("cls");
				output_res(all_res[res], last_move, complex_X, complex_Y, 1);
				all_char_set_0(last_move);
				draw_file_choice(choice_X, choice_Y, from, highlight, file_name);
				draw_complex_sudoku(*map, complex_X, complex_Y, branch - 1);
			}

			conflict_and_highlight_set_0(*map);	//��ͻ����

			//���봢�沽���Ŀռ�
			save_and_apply_steps(*map, s_now, s_head, res, last_move);
		}

		//�˳�ѭ�����ͷ�������Ŀռ�
		system("cls");
		if (branch == 1)//��ͼ
			draw_basic_sudoku(*map, 0, 0);
		else
		{
			system("cls");
			draw_file_choice(choice_X, choice_Y, from, highlight, file_name);
			draw_complex_sudoku(*map, complex_X, complex_Y, branch - 1);
		}
		cout << "\n��Ϸ����\n";
		free_space(s_head);

		end_until_end(0, 0);
	}
	else//����С��
	{
		double time;

		flag = first_operation(*map, pos, fillable);
		if (flag == -1)
		{
			end_until_end(0, 0);
			return;
		}
		else if (flag == 0)//��Ϸ���
		{
			system("cls");
			draw_file_choice(choice_X, choice_Y, from, highlight, file_name);
			draw_complex_sudoku(*map, complex_X, complex_Y, branch - 1);
			cout << "\n��Ϸ����\n";
			end_until_end(0, 0);
			return;
		}

		//δ�����Ϸ
		draw_file_choice(choice_X, choice_Y, from, highlight, file_name);
		draw_complex_sudoku(*map, complex_X, complex_Y, branch - 1);
		gotoxy(hout, complex_X, 0);
		
		flag = make_this_pos_possible_shuzu(*map, pos[0]);
		if (flag == -1)//�ڴ�����ʧ��
		{
			end_until_end(0, 0);
			return;
		}
		else if (flag == 0)//��һ���վ�û�п��������
		{
			system("cls");
			draw_file_choice(choice_X, choice_Y, from, highlight, file_name);
			draw_complex_sudoku(*map, complex_X, complex_Y, branch - 1);

			cout << "\n�������޽�\n";
			delete pos;
			end_until_end(0, 0);
			return;
		}

		flag = auto_steps(*map, s_head, pos, fillable,complex_X,complex_Y,time);
		
		if(flag==-1)//�ڴ�����ʧ��
		{
			delete pos;
			end_until_end(0, 0);
			return;
		}
		else if(flag==0)
		{
			cout << "\n�������޽�\n";
			delete pos;
			end_until_end(0, 0);
			return;
		}

		//�˳�ѭ�����ͷ�������Ŀռ�
		system("cls");
		draw_file_choice(choice_X, choice_Y, from, highlight, file_name);
		draw_complex_sudoku(*map, complex_X, complex_Y, branch - 1);

		cout << "\n��Ϸ����\n";
		cout << "��ʱ" << double(time) << "ms" << endl;
		free_possible(*map);
		free_space(s_head);
		delete pos;

		end_until_end(0, 0);
		return;
	}
}
