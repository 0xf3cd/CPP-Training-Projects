/*1550431 计科3班 王甯琪*/
#include "90-b2.h"
//定义仅用于本CPP的函数
void menu(int &branch);
void which_way_to_go(int branch);

int main()
{
	int branch = -1;

	while (1)
	{
		system("cls");
		setconsoleborder(hout, 120, 40);
		setfontsize(hout, L"点阵字体", 15);
		menu(branch);//输出菜单，并得到用户输入的选项

		if (branch == 0)
			break;
		if (branch < 0 || branch>choice)
			branch = -1;
		else
		{
			which_way_to_go(branch);//进入菜单项
			branch = -1;
		}
	}

	return 0;
}


void menu(int &branch)
{
	cout << "-----------------------------------------------------\n1.字符界面游戏(带回退功能)\n"
		<< "2.图形界面游戏(带回退功能)\n"
		<< "3.图形界面自动解(显示过程并带延时)\n0.退出\n"
		<< "-----------------------------------------------------\n[请选择0-3] ";

	branch = _getch() - '0';
	cout << branch << endl;
}

void which_way_to_go(int branch)
{
	system("cls");
	int flag, check, choice_X = 80, choice_Y = 3, complex_X = 3, complex_Y = 1, highlight, from, res, *pos, fillable;//XY是2-3小题选择文件框口的坐标
	char file_name[100][50] = { 0 }, *all_res[] = { "不可回退哦~\n" ,"产生冲突\n","本次输入正确\n" ,"输入有误哦~\n" ,"该位置不可变更\n" ," " }, last_move[40] = { 0 };
	point map[9][9];
	step *s_head = new(nothrow) step, *s_now=s_head;
	if (s_head == NULL)
	{
		system("cls");
		cout << "\n内存申请失败";
		end_until_end(0, 0);
		return;
	}

	flag = select_and_generate(map, file_name, choice_X, choice_Y, highlight, from, branch);
	if (flag == -1 || flag == 0)//选择文件或生成链表时出错(若是申请空间出错，则在函数内部已经释放空间)(错误原因已在函数内部进行显示)
	{
		free_space(s_head);//释放储存对数独进行操作的空间
		end_until_end(0, 0);
		return;
	}

	//正常生成完毕链表
	check = check_valid(*map);
	if (check < 0)//conflict
	{
		//print the map with the conflict points highlighted
		if (branch == 1)
			draw_basic_sudoku(*map, 0, 0);
		else
			draw_complex_sudoku(*map, complex_X, complex_Y, branch - 1);
		cout << "\n原始数据文件有错，请修改正确后继续\n";
		end_until_end(0, 0);
		free_space(s_head);
		return;
	}

	//文件出错或一开始便有冲突的情况已经排除
	//now,一切正常，可以开始

	//检查用户输入
	//建立STEP链表
	//对数独进行更改

	if (branch == 1 || branch == 2)
	{
		res = 5;
		s_now = s_head;
		while (!game_over(*map))//进入循环(不满足游戏结束条件时)
		{
			if (branch == 1)//画图
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

			conflict_and_highlight_set_0(*map);	//冲突置零

			//申请储存步数的空间
			save_and_apply_steps(*map, s_now, s_head, res, last_move);
		}

		//退出循环，释放所申请的空间
		system("cls");
		if (branch == 1)//画图
			draw_basic_sudoku(*map, 0, 0);
		else
		{
			system("cls");
			draw_file_choice(choice_X, choice_Y, from, highlight, file_name);
			draw_complex_sudoku(*map, complex_X, complex_Y, branch - 1);
		}
		cout << "\n游戏结束\n";
		free_space(s_head);

		end_until_end(0, 0);
	}
	else//第三小题
	{
		double time;

		flag = first_operation(*map, pos, fillable);
		if (flag == -1)
		{
			end_until_end(0, 0);
			return;
		}
		else if (flag == 0)//游戏完成
		{
			system("cls");
			draw_file_choice(choice_X, choice_Y, from, highlight, file_name);
			draw_complex_sudoku(*map, complex_X, complex_Y, branch - 1);
			cout << "\n游戏结束\n";
			end_until_end(0, 0);
			return;
		}

		//未完成游戏
		draw_file_choice(choice_X, choice_Y, from, highlight, file_name);
		draw_complex_sudoku(*map, complex_X, complex_Y, branch - 1);
		gotoxy(hout, complex_X, 0);
		
		flag = make_this_pos_possible_shuzu(*map, pos[0]);
		if (flag == -1)//内存申请失败
		{
			end_until_end(0, 0);
			return;
		}
		else if (flag == 0)//第一个空就没有可填入的数
		{
			system("cls");
			draw_file_choice(choice_X, choice_Y, from, highlight, file_name);
			draw_complex_sudoku(*map, complex_X, complex_Y, branch - 1);

			cout << "\n该数独无解\n";
			delete pos;
			end_until_end(0, 0);
			return;
		}

		flag = auto_steps(*map, s_head, pos, fillable,complex_X,complex_Y,time);
		
		if(flag==-1)//内存申请失败
		{
			delete pos;
			end_until_end(0, 0);
			return;
		}
		else if(flag==0)
		{
			cout << "\n该数独无解\n";
			delete pos;
			end_until_end(0, 0);
			return;
		}

		//退出循环，释放所申请的空间
		system("cls");
		draw_file_choice(choice_X, choice_Y, from, highlight, file_name);
		draw_complex_sudoku(*map, complex_X, complex_Y, branch - 1);

		cout << "\n游戏结束\n";
		cout << "用时" << double(time) << "ms" << endl;
		free_possible(*map);
		free_space(s_head);
		delete pos;

		end_until_end(0, 0);
		return;
	}
}
