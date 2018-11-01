/*1550431 计科3班 王甯琪*/
#include "90-b1.h"

//定义仅用于本CPP的函数
void menu(int &branch);
void which_way_to_go(int branch);
//部分菜单项要求在正式开始前，经过系列调整，使得调整后的球盘不存在三个及以上连续的同色球
//因为代码较多，同时有多个菜单项使用，所以单独封装成函数
void for_start(point * const map, const int h, const int l, const int X, const int Y, const int last_x, const int last_y, const int whether_wait_for_enter = 1);//最后参数默认置1，部分步骤需要等待回车键按下
void add_up_scores_and_go_on(point * const map, const int h, const int l, const int X, const int Y);//统计交换后得分并且进行新的输出

int main()
{
	int branch = -1;

	while (1)
	{
		system("cls");
		setconsoleborder(hout, 90, 40);
		setfontsize(hout, L"点阵字体", 15);
		menu(branch);//输出菜单，并得到用户输入的选项

		if (branch == 0)
			break;
		if (branch < 0 || branch>9)
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
	cout << "-----------------------------------------------------\n1.内部数组，生成初始状态，寻找是否有初始可消除项\n2.内部数组，消除初始可消除项后非0项下落并用0填充\n"
		<< "3.内部数组，消除初始可消除项后查找消除提示\n4.n*n的框架(无分隔线)，显示初始状态，随机显示5个球\n5.n*n的框架(有分隔线)，显示初始状态\n"
		<< "6.n*n的框架(有分隔线)，显示初始状态及初始可消除项\n7.n*n的框架(有分隔线)，消除初始可消除项后显示消除提示\n8.cmd图形界面完整版\n"
		<< "9.从文件中读取数据以验证查找消除提示的算法的正确性\n0.退出\n-----------------------------------------------------\n[请选择0-9] ";

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
		h = panduan(0, 0, "请输入行数(5 - 9)：", h_min, h_max);
		l = panduan(0, 1, "请输入列数(5 - 9)：", l_min, l_max);
	}

	switch (branch)
	{
		case(1):
		case(2):
			cout << "\n初始球盘：\n";
			randomly_generate_map(*map, h, l);//在一定范围内填上球
			draw_basic_map(X, Y, *map, h, l, 0);//最后置0,接着已经输出内容继续输出
			cout << "按回车键进行寻找初始可消除项的操作...";
			wait_an_enter();
			if (!find_removable_points(*map, h, l))
			{
				cout << "\n无可消除项/(ㄒoㄒ)/~~\n";
			}
			else
			{
				cout << "\n初始可消除项（不同色标识）：\n";
				draw_basic_map(X, Y, *map, h, l, 0, 1);//接着已经输出内容继续输出,高亮输出

				if (branch == 2)//继续后续的除零操作
				{
					cout << "按回车键进行消除、下落操作...";
					wait_an_enter();
					system("cls");
					move_points(*map, h, l);//得到移动后的球盘，空位color为0
					draw_basic_map(X, Y, *map, h, l, 0, 1);//清屏后输出,高亮输出
					cout << "\n按回车键进行补充操作...\n";
					wait_an_enter();
					fill_empty_points(*map, h, l);
					draw_basic_map(X, Y, *map, h, l, 0, 1);//接着已经输出内容继续输出,高亮输出
					all_highlight_set_0(*map, h, l);
				}
			}
			end_until_end(X, Y, "本小题结束，请输入End继续...  ", 0);
			break;

		case(3):
			randomly_generate_map(*map, h, l);//在一定范围内填上球
			if (!find_removable_points(*map, h, l))
			{
				cout << "\n无可消除项/(ㄒoㄒ)/~~\n";
			}
			else
			{
				while (1)
				{
					cout << "\n初始可消除项（不同色标识）：\n";
					draw_basic_map(X, Y, *map, h, l, 0, 1);//接着已经输出内容继续输出,高亮输出
					//反复消除可以消除的球并重新填入
					cout << "按回车键进行消除、下落操作...";
					wait_an_enter();
					//system("cls");
					move_points(*map, h, l);//得到移动后的球盘，空位color为0
					draw_basic_map(X, Y, *map, h, l, 0, 1);//清屏后输出,高亮输出
					cout << "\n按回车键进行补充操作...\n";
					wait_an_enter();
					fill_empty_points(*map, h, l);
					draw_basic_map(X, Y, *map, h, l, 0, 1);//接着已经输出内容继续输出,高亮输出
					all_highlight_set_0(*map, h, l);

					if (!find_removable_points(*map, h, l))
						break;
				}
			}

			cout << "初始已无可消除项\n\n可选择的消除提示（不同色标识）：\n";
			keys_highlight(*map, h, l);
			draw_basic_map(X, Y, *map, h, l, 0, 1);//接着已经输出内容继续输出,高亮输出
			all_key_highlight_set_0(*map, h, l);
			end_until_end(X, Y, "本小题结束，请输入End继续...  ", 0);
			break;

		case(4):
			cout << "\n初始球盘：\n";
			randomly_generate_map(*map, h, l);//在一定范围内填上球
			draw_basic_map(X, Y, *map, h, l, 0);//最后置0,接着已经输出内容继续输出

			cout << "\n按回车键显示图形...";
			wait_an_enter();

			setfontsize(hout, L"新宋体", 20);
			setconsoleborder(hout, 46, 25);
			system("cls");

			draw_primary_map(*map, X, Y, h, l);

			end_until_end(X, Y, "本小题结束，请输入End继续...  ", 0);
			break;

		case(5):
			cout << "\n初始球盘：\n";
			randomly_generate_map(*map, h, l);//在一定范围内填上球
			draw_basic_map(X, Y, *map, h, l, 0);//最后置0,接着已经输出内容继续输出

			cout << "\n按回车键显示图形...";
			wait_an_enter();

			setfontsize(hout, L"新宋体", 20);
			setconsoleborder(hout, 46, 25);
			system("cls");
			draw_complex_map(*map, X, Y, h, l);

			end_until_end(X, Y, "本小题结束，请输入End继续...  ", 0);
			break;

		case(6):
			cout << "\n初始球盘：\n";
			randomly_generate_map(*map, h, l);//在一定范围内填上球
			draw_basic_map(X, Y, *map, h, l, 0);//最后置0,接着已经输出内容继续输出

			cout << "\n按回车键显示图形...";
			wait_an_enter();

			setfontsize(hout, L"新宋体", 20);
			setconsoleborder(hout, 46, 25);
			system("cls");

			draw_complex_map(*map, X, Y + 1, h, l);
			getxy(hout, last_x, last_y);

			if (!find_removable_points(*map, h, l))//没有可消除项
			{
				gotoxy(hout, X, Y);
				cout << "未找到初始可消除项";
			}
			else
			{
				turn_emptyball_to_fullball(*map, X, Y + 1, h, l);
				all_highlight_set_0(*map, h, l);
			}

			end_until_end(last_x, last_y, "本小题结束，请输入End继续...  ");
			break;

		case(7):
			X = 0;
			Y = 1;
			cout << "\n初始球盘：\n";
			randomly_generate_map(*map, h, l);//在一定范围内填上球
			draw_basic_map(X, Y, *map, h, l, 0);//最后置0,接着已经输出内容继续输出

			cout << "\n按回车键显示图形...";
			wait_an_enter();

			setfontsize(hout, L"新宋体", 22);
			setconsoleborder(hout, 46, 25);
			system("cls");

			draw_complex_map(*map, X, Y, h, l);
			getxy(hout, last_x, last_y);

			for_start(*map, h, l, X, Y, last_x, last_y);//循环消除满足条件的得分球，直至无法消除

			gotoxy(hout, last_x, last_y);
			cout << "按回车键显示可消除项提示...           \n";
			wait_an_enter();

			//查找提示
			keys_highlight(*map, h, l);
			draw_keys_highlight_points(*map, X, Y, h, l);
			all_key_highlight_set_0(*map, h, l);

			end_until_end(last_x, last_y, "本小题结束，请输入End继续...     ");
			break;

		case(8):
			X = 0;
			Y = 1;
			setfontsize(hout, L"新宋体", 22);
			setconsoleborder(hout, 46, 25);
			system("cls");

			randomly_generate_map(*map, h, l);//在一定范围内填上球
			draw_complex_map(*map, X, Y, h, l);
			getxy(hout, last_x, last_y);

			//循环消除满足条件的得分球，直至无法消除
			//最后置零，代表消除同色球已到达开局条件的过程不需要空格键参与
			for_start(*map, h, l, X, Y, last_x, last_y, 0);

			//查找提示
			keys_highlight(*map, h, l);
			draw_keys_highlight_points(*map, X, Y, h, l);
			all_key_highlight_set_0(*map, h, l);
			all_score_set_0(*map, h, l);

			show_scores_gotten(*map, X, Y, h, l);

			while (1)
			{
				if (game_over(*map, h, l) == 0)
					break;//游戏结束

				//以下步骤：
				//1. 得到点击的两个球的坐标
				//2. 输出鼠标所处的坐标
				//返回特定值-1代表按下了右键，返回0代表找到了相邻的合法球对，返回1代表所选的相邻球交换后不能带来消除
				judge = from_mouse_get_position(*map, last_x, last_y, X, Y, h, l, fh, fl, th, tl);
				show_scores_gotten(*map, X, Y, h, l);

				if (judge == -1)//按下右键
					break;
				else if (judge == 1)//所选相邻两球交换后无法带来消除
				{
					draw_complex_map(*map, X, Y, h, l);

					//查找提示
					all_key_highlight_set_0(*map, h, l);
					keys_highlight(*map, h, l);
					draw_keys_highlight_points(*map, X, Y, h, l);
					all_key_highlight_set_0(*map, h, l);
					all_score_set_0(*map, h, l);
					continue;
				}
				else//所选相邻两球交换后能够带来消除
				{
					//动画
					move_2_points(*map, X, Y, fh, fl, th, tl, h, l);
					add_up_scores_and_go_on(*map, h, l, X, Y);//统计交换、消除后的得分，并输出

					draw_complex_map(*map, X, Y, h, l);

					//查找提示
					keys_highlight(*map, h, l);
					draw_keys_highlight_points(*map, X, Y, h, l);
					all_key_highlight_set_0(*map, h, l);
					all_score_set_0(*map, h, l);

					continue;
				}
			}

			end_until_end(last_x, last_y + 1, "游戏结束，请输入End继续...     ");
			break;

		case(9):
			setconsoleborder(hout, 90, 50);
			char num[100], ought[17] = { "test\\" }, ought1[17] = { 0 }, ought2[17] = { 0 };
			ifstream fin, finans;

			cout << "请输入学号(输入 1651234 对应会打开 test\1651234.dat 文件)\n";
			cin >> num;

			if (strlen(num) != 7)
				cout << "文件打开失败";
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
					cout << "文件打开失败";
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
					//文件读入完毕
					cout << "初始数组：";
					draw_basic_map(X, Y, *map, h, l, 0, 0);

					//由菜单项3复制而来
					keys_highlight(*map, h, l);
					cout << "\n可选择的消除提示（不同色标识）：\n";
					draw_basic_map(X, Y, *map, h, l, 0, 1);//接着已经输出内容继续输出,高亮输出
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

					cout << "\n答案文件的内容:\n";
					draw_basic_map(X, Y, *map, h, l, 0, 1);//接着已经输出内容继续输出,高亮输出
				}
			}

			end_until_end(X, Y, "本小题结束，请输入End继续...  ", 0);
			break;
	}
}

void for_start(point * const map, const int h, const int l, const int X, const int Y, const int last_x, const int last_y, const int whether_wait_for_enter)//最后参数默认置1，部分步骤需要等待回车键按下
{
	if (!find_removable_points(map, h, l))//没有可消除项
	{
		gotoxy(hout, X, Y - 1);
		cout << "未找到初始可消除项";
	}
	else
	{
		while (1)
		{
			turn_emptyball_to_fullball(map, X, Y, h, l);

			//反复消除可以消除的球并重新填入
			if (whether_wait_for_enter)
			{
				gotoxy(hout, last_x, last_y);
				cout << "按回车键进行消除、下落操作...";
				wait_an_enter();
			}

			//动画消除球，同时数组消除球ok
			draw_remove_points(map, X, Y, h, l);

			//球下移,换思路，遍历所有点，求每个球应该下移的个数，最后一起下移
			sum_up_downwards(map, h, l);
			draw_move_downwards(map, h, l, X, Y);
			all_downwards_set_0(map, h, l);

			if (whether_wait_for_enter)
			{
				gotoxy(hout, last_x, last_y);
				cout << "按回车键进行补充操作...           \n";
				wait_an_enter();
			}

			//动态补充ok
			draw_fill_empty_points(map, X, Y, h, l);

			if (!find_removable_points(map, h, l))
			{
				if (whether_wait_for_enter)
				{
					gotoxy(hout, X, Y - 1);
					cout << "已无可消除项";
				}
				break;
			}
		}
	}
}


void add_up_scores_and_go_on(point * const map, const int h, const int l, const int X, const int Y)//统计交换后得分并且进行新的输出
{
	while (find_removable_points(map, h, l))
	{
		turn_emptyball_to_fullball(map, X, Y, h, l);

		//统计得分
		show_scores_gotten(map, X, Y, h, l);

		//动画消除球，同时数组消除球ok
		draw_remove_points(map, X, Y, h, l);

		//球下移,换思路，遍历所有点，求每个球应该下移的个数，最后一起下移
		sum_up_downwards(map, h, l);
		draw_move_downwards(map, h, l, X, Y);
		all_downwards_set_0(map, h, l);

		//动态补充ok
		draw_fill_empty_points(map, X, Y, h, l);

		if (!find_removable_points(map, h, l))
			break;
	}
}