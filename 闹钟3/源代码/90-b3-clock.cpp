/*1550431 Íõå¸ç÷ ¼Æ¿Æ3°à*/
//Ê±ÖÓ²¿·Ö
#include "90-b3.h"

int generate_circle(point *&first, const int X, const int Y, const int R)//ÒÔX,YÎªÔ²ÐÄ£¬Éú³ÉÒ»¸ö°ë¾¶ÎªRµÄÔ²µÄ¹ì¼£µã ÄÚ´æÉêÇë´íÎó·µ»Ø-1
{
	point  *now, *next;
	double i, all = 1000.0;

	first = new(nothrow) point;
	if (first == NULL)
	{
		system("cls");
		cout << "¶¯Ì¬ÄÚ´æÉêÇëÊ§°Ü";
		return -1;
	}

	now = first;
	for (i = 1.0; i < all; i += 0.5)
	{
		now->X = int(X + XtoY*R*cos(2 * pai*i / all));
		now->Y = int(Y + R*sin(2 * pai*i / all));

		next = new(nothrow) point;
		if (next == NULL)
		{
			system("cls");
			cout << "¶¯Ì¬ÄÚ´æÉêÇëÊ§°Ü";
			free_points(first);
			return -1;
		}

		now->next = next;
		now = next;
	}
	now->X = X + R;
	now->Y = Y;

	return 1;
}

int  generate_kedu(point *&first, const int X, const int Y, const int R, const int L)//ÒÔX,YÎªÔ²ÐÄ,RÎª°ë¾¶Éú³ÉµÄ±íÅÌµÄ¿Ì¶È£¬¿Ì¶È³¤¶ÈÎªL ÄÚ´æÉêÇë´íÎó·µ»Ø-1
{
	point  *now, *next;
	int i, L_t;
	double j;

	first = new(nothrow) point;
	if (first == NULL)
	{
		system("cls");
		cout << "¶¯Ì¬ÄÚ´æÉêÇëÊ§°Ü";
		return -1;
	}

	now = first;
	for (i = 0; i < 12; i++)
	{
		L_t = (i % 3) ? L : L + 8;

		for (j = 1.0; j <= L_t; j += 0.5)
		{
			now->X = int(X + XtoY*(R - j)*cos(2 * pai*i / 12));
			now->Y = int(Y + (R - j)*sin(2 * pai*i / 12));

			next = new(nothrow) point;
			if (next == NULL)
			{
				system("cls");
				cout << "¶¯Ì¬ÄÚ´æÉêÇëÊ§°Ü";
				free_points(first);
				return -1;
			}

			now->next = next;
			now = next;
		}
	}
	now->X = X;
	now->Y = Y;

	return 1;
}

int  generate_zhen(now_time*saver, point *&h_first, point *&m_first, point *&s_first, const int X, const int Y)//ÔÚÒÔX,YÎªÔ²ÐÄ,RÎª°ë¾¶Éú³ÉµÄ±íÅÌÉÏ£¬Éú³ÉÊ±·ÖÃëµÄÖ¸Õë ÄÚ´æÉêÇë´íÎó·µ»Ø-1
{
	point*now, *next;
	int h_len = 40, m_len = 50, s_len = 60;
	double i;

	//setfontsize(hout, L"µãÕó×ÖÌå", 20);
	//cout << (saver->minute) << endl;
	//getchar();
	//getchar();

	//Ê±Õë²¿·Ö h_first h_len
	h_first = new(nothrow) point;
	if (h_first == NULL)
	{
		system("cls");
		cout << "¶¯Ì¬ÄÚ´æÉêÇëÊ§°Ü";
		return -1;
	}

	now = h_first;
	for (i = 0.5; i < h_len; i += 0.5)
	{
		now->X = int(X + XtoY*i*cos(2 * pai*(saver->hour % 12 - 3) / 12 + 2 * pai*saver->minute / 12 / 60));
		now->Y = int(Y + i*sin(2 * pai*(saver->hour % 12 - 3) / 12 + 2 * pai*saver->minute / 12 / 60));

		next = new(nothrow) point;
		if (next == NULL)
		{
			system("cls");
			cout << "¶¯Ì¬ÄÚ´æÉêÇëÊ§°Ü";
			free_points(h_first);
			return -1;
		}

		now->next = next;
		now = next;
	}
	now->X = int(X + XtoY*h_len*cos(2 * pai*(saver->hour % 12 - 3) / 12 + 2 * pai*saver->minute / 12 / 60));
	now->Y = int(Y + h_len*sin(2 * pai*(saver->hour % 12 - 3) / 12 + 2 * pai*saver->minute / 12 / 60));

	//·ÖÕë²¿·Ö m_first m_len
	m_first = new(nothrow) point;
	if (m_first == NULL)
	{
		system("cls");
		cout << "¶¯Ì¬ÄÚ´æÉêÇëÊ§°Ü";
		return -1;
	}

	now = m_first;
	for (i = 0.5; i < m_len; i += 0.5)
	{
		now->X = int(X + XtoY*i*cos(2 * pai*(saver->minute - 15) / 60 + 2 * pai*(saver->second) / 3600));
		now->Y = int(Y + i*sin(2 * pai*(saver->minute - 15) / 60 + 2 * pai*(saver->second) / 3600));

		next = new(nothrow) point;
		if (next == NULL)
		{
			system("cls");
			cout << "¶¯Ì¬ÄÚ´æÉêÇëÊ§°Ü";
			free_points(h_first);
			free_points(m_first);
			return -1;
		}

		now->next = next;
		now = next;
	}
	now->X = int(X + XtoY*m_len*cos(2 * pai*(saver->minute - 15) / 60 + 2 * pai*(saver->second) / 3600));
	now->Y = int(Y + m_len*sin(2 * pai*(saver->minute - 15) / 60 + 2 * pai*(saver->second) / 3600));

	//ÃëÕë²¿·Ö s_first s_len
	s_first = new(nothrow) point;
	if (s_first == NULL)
	{
		system("cls");
		cout << "¶¯Ì¬ÄÚ´æÉêÇëÊ§°Ü";
		return -1;
	}

	now = s_first;
	for (i = 0.5; i < s_len; i += 0.5)
	{
		now->X = int(X + XtoY*i*cos(2 * pai*(saver->second - 15) / 60));
		now->Y = int(Y + i*sin(2 * pai*(saver->second - 15) / 60));

		next = new(nothrow) point;
		if (next == NULL)
		{
			system("cls");
			cout << "¶¯Ì¬ÄÚ´æÉêÇëÊ§°Ü";
			free_points(h_first);
			free_points(m_first);
			return -1;
		}

		now->next = next;
		now = next;
	}
	now->X = int(X + XtoY*s_len*cos(2 * pai*(saver->second - 15) / 60));
	now->Y = int(Y + s_len*sin(2 * pai*(saver->second - 15) / 60));

	return 1;
}

int generate_10_nums(point*num[11], const int c, const int k)//Éú³ÉÊ®¸öÊý×ÖµÄÏà¶Ô×ø±ê c,k´ú±í³¤¿í ÄÚ´æÉêÇë´íÎó·µ»Ø-1
{
	int c_mid = c / 2, k_mid = k / 2, i, j,t;
	point*now, *next;

	for (i = 0; i < 11; i++)
	{
		num[i] = new(nothrow) point;
		if (num[i] == NULL)
		{
			system("cls");
			cout << "¶¯Ì¬ÄÚ´æÉêÇëÊ§°Ü";

			for (j = 0; j < i; j++)
				free_points(num[j]);

			return -1;
		}
	}

	//0
	now = num[0];
	for (i = 0; i < k; i++)
	{
		now->X = i;
		now->Y = 0;

		next = new(nothrow) point;
		if (next == NULL)
		{
			system("cls");
			cout << "¶¯Ì¬ÄÚ´æÉêÇëÊ§°Ü";

			for (j = 0; j < 11; j++)
				free_points(num[j]);

			return -1;
		}

		now->next = next;
		now = next;
	}

	for (i = 1; i < c; i++)
	{
		now->X = k - 1;
		now->Y = i;

		next = new(nothrow) point;
		if (next == NULL)
		{
			system("cls");
			cout << "¶¯Ì¬ÄÚ´æÉêÇëÊ§°Ü";

			for (j = 0; j < 11; j++)
				free_points(num[j]);

			return -1;
		}

		now->next = next;
		now = next;
	}

	for (i = k - 2; i >= 0; i--)
	{
		now->X = i;
		now->Y = c - 1;

		next = new(nothrow) point;
		if (next == NULL)
		{
			system("cls");
			cout << "¶¯Ì¬ÄÚ´æÉêÇëÊ§°Ü";

			for (j = 0; j < 11; j++)
				free_points(num[j]);

			return -1;
		}

		now->next = next;
		now = next;
	}

	for (i = c - 2; i > 1; i--)
	{
		now->X = 0;
		now->Y = i;

		next = new(nothrow) point;
		if (next == NULL)
		{
			system("cls");
			cout << "¶¯Ì¬ÄÚ´æÉêÇëÊ§°Ü";

			for (j = 0; j < 11; j++)
				free_points(num[j]);

			return -1;
		}

		now->next = next;
		now = next;
	}
	now->X = 0;
	now->Y = 1;

	//1
	now = num[1];

	for (i = 1; i < 4; i++)
	{
		now->X = k_mid - i;
		now->Y = 0;

		next = new(nothrow) point;
		if (next == NULL)
		{
			system("cls");
			cout << "¶¯Ì¬ÄÚ´æÉêÇëÊ§°Ü";

			for (j = 0; j < 11; j++)
				free_points(num[j]);

			return -1;
		}

		now->next = next;
		now = next;
	}

	for (i = 0; i < c - 1; i++)
	{
		now->X = k_mid;
		now->Y = i;

		next = new(nothrow) point;
		if (next == NULL)
		{
			system("cls");
			cout << "¶¯Ì¬ÄÚ´æÉêÇëÊ§°Ü";

			for (j = 0; j < 11; j++)
				free_points(num[j]);

			return -1;
		}

		now->next = next;
		now = next;
	}

	for (i = -5; i < 5; i++)
	{
		now->X = k_mid + i;
		now->Y = c - 1;

		next = new(nothrow) point;
		if (next == NULL)
		{
			system("cls");
			cout << "¶¯Ì¬ÄÚ´æÉêÇëÊ§°Ü";

			for (j = 0; j < 11; j++)
				free_points(num[j]);

			return -1;
		}

		now->next = next;
		now = next;
	}
	now->X = k_mid + 5;
	now->Y = c - 1;

	//2
	now = num[2];

	for (i = 0; i < k; i++)
	{
		now->X = i;
		now->Y = 0;

		next = new(nothrow) point;
		if (next == NULL)
		{
			system("cls");
			cout << "¶¯Ì¬ÄÚ´æÉêÇëÊ§°Ü";

			for (j = 0; j < 11; j++)
				free_points(num[j]);

			return -1;
		}

		now->next = next;
		now = next;

		now->X = i;
		now->Y = c_mid;

		next = new(nothrow) point;
		if (next == NULL)
		{
			system("cls");
			cout << "¶¯Ì¬ÄÚ´æÉêÇëÊ§°Ü";

			for (j = 0; j < 11; j++)
				free_points(num[j]);

			return -1;
		}

		now->next = next;
		now = next;

		now->X = i;
		now->Y = c - 1;

		next = new(nothrow) point;
		if (next == NULL)
		{
			system("cls");
			cout << "¶¯Ì¬ÄÚ´æÉêÇëÊ§°Ü";

			for (j = 0; j < 11; j++)
				free_points(num[j]);

			return -1;
		}

		now->next = next;
		now = next;
	}

	for (i = 1; i < c_mid; i++)
	{
		now->X = k - 1;
		now->Y = i;

		next = new(nothrow) point;
		if (next == NULL)
		{
			system("cls");
			cout << "¶¯Ì¬ÄÚ´æÉêÇëÊ§°Ü";

			for (j = 0; j < 11; j++)
				free_points(num[j]);

			return -1;
		}

		now->next = next;
		now = next;
	}

	for (i = c_mid + 1; i < c - 1; i++)
	{
		now->X = 0;
		now->Y = i;

		next = new(nothrow) point;
		if (next == NULL)
		{
			system("cls");
			cout << "¶¯Ì¬ÄÚ´æÉêÇëÊ§°Ü";

			for (j = 0; j < 11; j++)
				free_points(num[j]);

			return -1;
		}

		now->next = next;
		now = next;
	}
	now->X = 0;
	now->Y = c - 1;

	//3
	now = num[3];

	for (i = 0; i < c - 1; i++)
	{
		now->X = k - 1;
		now->Y = i;

		next = new(nothrow) point;
		if (next == NULL)
		{
			system("cls");
			cout << "¶¯Ì¬ÄÚ´æÉêÇëÊ§°Ü";

			for (j = 0; j < 11; j++)
				free_points(num[j]);

			return -1;
		}

		now->next = next;
		now = next;
	}

	for (i = 0; i < k - 1; i++)
	{
		now->X = i;
		now->Y = 0;

		next = new(nothrow) point;
		if (next == NULL)
		{
			system("cls");
			cout << "¶¯Ì¬ÄÚ´æÉêÇëÊ§°Ü";

			for (j = 0; j < 11; j++)
				free_points(num[j]);

			return -1;
		}

		now->next = next;
		now = next;

		now->X = i;
		now->Y = c_mid;

		next = new(nothrow) point;
		if (next == NULL)
		{
			system("cls");
			cout << "¶¯Ì¬ÄÚ´æÉêÇëÊ§°Ü";

			for (j = 0; j < 11; j++)
				free_points(num[j]);

			return -1;
		}

		now->next = next;
		now = next;

		now->X = i;
		now->Y = c - 1;

		next = new(nothrow) point;
		if (next == NULL)
		{
			system("cls");
			cout << "¶¯Ì¬ÄÚ´æÉêÇëÊ§°Ü";

			for (j = 0; j < 11; j++)
				free_points(num[j]);

			return -1;
		}

		now->next = next;
		now = next;
	}
	now->X = 0;
	now->Y = 0;

	//4
	now = num[4];

	for (i = 0; i <= c_mid; i++)
	{
		now->X = 0;
		now->Y = i;

		next = new(nothrow) point;
		if (next == NULL)
		{
			system("cls");
			cout << "¶¯Ì¬ÄÚ´æÉêÇëÊ§°Ü";

			for (j = 0; j < 11; j++)
				free_points(num[j]);

			return -1;
		}

		now->next = next;
		now = next;
	}

	for (i = 0; i < c; i++)
	{
		now->X = k - 1;
		now->Y = i;

		next = new(nothrow) point;
		if (next == NULL)
		{
			system("cls");
			cout << "¶¯Ì¬ÄÚ´æÉêÇëÊ§°Ü";

			for (j = 0; j < 11; j++)
				free_points(num[j]);

			return -1;
		}

		now->next = next;
		now = next;
	}

	for (i = 1; i < k - 2; i++)
	{
		now->X = i;
		now->Y = c_mid;

		next = new(nothrow) point;
		if (next == NULL)
		{
			system("cls");
			cout << "¶¯Ì¬ÄÚ´æÉêÇëÊ§°Ü";

			for (j = 0; j < 11; j++)
				free_points(num[j]);

			return -1;
		}

		now->next = next;
		now = next;
	}
	now->X = k - 2;
	now->Y = c_mid;

	//5
	now = num[5];

	for (i = 0; i < k; i++)
	{
		now->X = i;
		now->Y = 0;

		next = new(nothrow) point;
		if (next == NULL)
		{
			system("cls");
			cout << "¶¯Ì¬ÄÚ´æÉêÇëÊ§°Ü";

			for (j = 0; j < 11; j++)
				free_points(num[j]);

			return -1;
		}

		now->next = next;
		now = next;

		now->X = i;
		now->Y = c_mid;

		next = new(nothrow) point;
		if (next == NULL)
		{
			system("cls");
			cout << "¶¯Ì¬ÄÚ´æÉêÇëÊ§°Ü";

			for (j = 0; j < 11; j++)
				free_points(num[j]);

			return -1;
		}

		now->next = next;
		now = next;

		now->X = i;
		now->Y = c - 1;

		next = new(nothrow) point;
		if (next == NULL)
		{
			system("cls");
			cout << "¶¯Ì¬ÄÚ´æÉêÇëÊ§°Ü";

			for (j = 0; j < 11; j++)
				free_points(num[j]);

			return -1;
		}

		now->next = next;
		now = next;
	}

	for (i = 1; i < c_mid; i++)
	{
		now->X = 0;
		now->Y = i;

		next = new(nothrow) point;
		if (next == NULL)
		{
			system("cls");
			cout << "¶¯Ì¬ÄÚ´æÉêÇëÊ§°Ü";

			for (j = 0; j < 11; j++)
				free_points(num[j]);

			return -1;
		}

		now->next = next;
		now = next;
	}

	for (i = c_mid + 1; i < c - 1; i++)
	{
		now->X = k - 1;
		now->Y = i;

		next = new(nothrow) point;
		if (next == NULL)
		{
			system("cls");
			cout << "¶¯Ì¬ÄÚ´æÉêÇëÊ§°Ü";

			for (j = 0; j < 11; j++)
				free_points(num[j]);

			return -1;
		}

		now->next = next;
		now = next;
	}
	now->X = k - 1;
	now->Y = c - 1;

	//6
	now = num[6];

	for (i = 0; i < k; i++)
	{
		now->X = i;
		now->Y = 0;

		next = new(nothrow) point;
		if (next == NULL)
		{
			system("cls");
			cout << "¶¯Ì¬ÄÚ´æÉêÇëÊ§°Ü";

			for (j = 0; j < 11; j++)
				free_points(num[j]);

			return -1;
		}

		now->next = next;
		now = next;

		now->X = i;
		now->Y = c_mid;

		next = new(nothrow) point;
		if (next == NULL)
		{
			system("cls");
			cout << "¶¯Ì¬ÄÚ´æÉêÇëÊ§°Ü";

			for (j = 0; j < 11; j++)
				free_points(num[j]);

			return -1;
		}

		now->next = next;
		now = next;

		now->X = i;
		now->Y = c - 1;

		next = new(nothrow) point;
		if (next == NULL)
		{
			system("cls");
			cout << "¶¯Ì¬ÄÚ´æÉêÇëÊ§°Ü";

			for (j = 0; j < 11; j++)
				free_points(num[j]);

			return -1;
		}

		now->next = next;
		now = next;
	}

	for (i = 1; i < c; i++)
	{
		now->X = 0;
		now->Y = i;

		next = new(nothrow) point;
		if (next == NULL)
		{
			system("cls");
			cout << "¶¯Ì¬ÄÚ´æÉêÇëÊ§°Ü";

			for (j = 0; j < 11; j++)
				free_points(num[j]);

			return -1;
		}

		now->next = next;
		now = next;
	}

	for (i = c_mid + 1; i < c - 1; i++)
	{
		now->X = k - 1;
		now->Y = i;

		next = new(nothrow) point;
		if (next == NULL)
		{
			system("cls");
			cout << "¶¯Ì¬ÄÚ´æÉêÇëÊ§°Ü";

			for (j = 0; j < 11; j++)
				free_points(num[j]);

			return -1;
		}

		now->next = next;
		now = next;
	}
	now->X = k - 1;
	now->Y = c - 1;

	//7
	now = num[7];

	for (i = 0; i < k; i++)
	{
		now->X = i;
		now->Y = 0;

		next = new(nothrow) point;
		if (next == NULL)
		{
			system("cls");
			cout << "¶¯Ì¬ÄÚ´æÉêÇëÊ§°Ü";

			for (j = 0; j < 11; j++)
				free_points(num[j]);

			return -1;
		}

		now->next = next;
		now = next;
	}

	for (i = 1; i < c - 1; i++)
	{
		now->X = k - 1;
		now->Y = i;

		next = new(nothrow) point;
		if (next == NULL)
		{
			system("cls");
			cout << "¶¯Ì¬ÄÚ´æÉêÇëÊ§°Ü";

			for (j = 0; j < 11; j++)
				free_points(num[j]);

			return -1;
		}

		now->next = next;
		now = next;
	}
	now->X = k - 1;
	now->Y = c - 1;

	//8
	now = num[8];

	for (i = 0; i < k; i++)
	{
		now->X = i;
		now->Y = 0;

		next = new(nothrow) point;
		if (next == NULL)
		{
			system("cls");
			cout << "¶¯Ì¬ÄÚ´æÉêÇëÊ§°Ü";

			for (j = 0; j < 11; j++)
				free_points(num[j]);

			return -1;
		}

		now->next = next;
		now = next;

		now->X = i;
		now->Y = c_mid;

		next = new(nothrow) point;
		if (next == NULL)
		{
			system("cls");
			cout << "¶¯Ì¬ÄÚ´æÉêÇëÊ§°Ü";

			for (j = 0; j < 11; j++)
				free_points(num[j]);

			return -1;
		}

		now->next = next;
		now = next;

		now->X = i;
		now->Y = c - 1;

		next = new(nothrow) point;
		if (next == NULL)
		{
			system("cls");
			cout << "¶¯Ì¬ÄÚ´æÉêÇëÊ§°Ü";

			for (j = 0; j < 11; j++)
				free_points(num[j]);

			return -1;
		}

		now->next = next;
		now = next;
	}

	for (i = 1; i < c; i++)
	{
		now->X = 0;
		now->Y = i;

		next = new(nothrow) point;
		if (next == NULL)
		{
			system("cls");
			cout << "¶¯Ì¬ÄÚ´æÉêÇëÊ§°Ü";

			for (j = 0; j < 11; j++)
				free_points(num[j]);

			return -1;
		}

		now->next = next;
		now = next;
	}

	for (i = 0; i < c - 1; i++)
	{
		now->X = k - 1;
		now->Y = i;

		next = new(nothrow) point;
		if (next == NULL)
		{
			system("cls");
			cout << "¶¯Ì¬ÄÚ´æÉêÇëÊ§°Ü";

			for (j = 0; j < 11; j++)
				free_points(num[j]);

			return -1;
		}

		now->next = next;
		now = next;
	}
	now->X = k - 1;
	now->Y = c - 1;

	//9
	now = num[9];

	for (i = 0; i < k; i++)
	{
		now->X = i;
		now->Y = 0;

		next = new(nothrow) point;
		if (next == NULL)
		{
			system("cls");
			cout << "¶¯Ì¬ÄÚ´æÉêÇëÊ§°Ü";

			for (j = 0; j < 11; j++)
				free_points(num[j]);

			return -1;
		}

		now->next = next;
		now = next;

		now->X = i;
		now->Y = c_mid;

		next = new(nothrow) point;
		if (next == NULL)
		{
			system("cls");
			cout << "¶¯Ì¬ÄÚ´æÉêÇëÊ§°Ü";

			for (j = 0; j < 11; j++)
				free_points(num[j]);

			return -1;
		}

		now->next = next;
		now = next;

		now->X = i;
		now->Y = c - 1;

		next = new(nothrow) point;
		if (next == NULL)
		{
			system("cls");
			cout << "¶¯Ì¬ÄÚ´æÉêÇëÊ§°Ü";

			for (j = 0; j < 11; j++)
				free_points(num[j]);

			return -1;
		}

		now->next = next;
		now = next;
	}

	for (i = 1; i <= c_mid; i++)
	{
		now->X = 0;
		now->Y = i;

		next = new(nothrow) point;
		if (next == NULL)
		{
			system("cls");
			cout << "¶¯Ì¬ÄÚ´æÉêÇëÊ§°Ü";

			for (j = 0; j < 11; j++)
				free_points(num[j]);

			return -1;
		}

		now->next = next;
		now = next;
	}

	for (i = 0; i < c - 1; i++)
	{
		now->X = k - 1;
		now->Y = i;

		next = new(nothrow) point;
		if (next == NULL)
		{
			system("cls");
			cout << "¶¯Ì¬ÄÚ´æÉêÇëÊ§°Ü";

			for (j = 0; j < 11; j++)
				free_points(num[j]);

			return -1;
		}

		now->next = next;
		now = next;
	}
	now->X = k - 1;
	now->Y = c - 1;

	//:
	now = num[10];

	for (t = 0; t <= 1; t++)
	{
		for (i =c_mid-3 ; i <=c_mid-1; i++)
		{
			now->X = t;
			now->Y = i;

			next = new(nothrow) point;
			if (next == NULL)
			{
				system("cls");
				cout << "¶¯Ì¬ÄÚ´æÉêÇëÊ§°Ü";

				for (j = 0; j < 11; j++)
					free_points(num[j]);

				return -1;
			}

			now->next = next;
			now = next;

			now->X = t;
			now->Y = i+4;

			next = new(nothrow) point;
			if (next == NULL)
			{
				system("cls");
				cout << "¶¯Ì¬ÄÚ´æÉêÇëÊ§°Ü";

				for (j = 0; j < 11; j++)
					free_points(num[j]);

				return -1;
			}

			now->next = next;
			now = next;
		}
	}
	now->X = 1;
	now->Y = c_mid - 3;

	return 1;
}

int  combime_nums(now_time *tm, point *num[11], point *&all_num, const int k, const int X, const int Y)//ÔÚ X,Y ´¦Éú³É¼ÇÂ¼Êä³öµãµÄÁ´±í
{
	point *saver[8];
	int value,flag;

	value = (tm->second) % 10;
	flag = copy_points_link(num[value], saver[0]);
	if (flag == -1)
		return -1;

	//all_num = head;
	//return 1;

	points_link_add_X_Y(saver[0], k+1, 0);
	//getchar(); getchar(); getchar(); getchar(); getchar(); getchar(); getchar();

	value = (tm->second) / 10;
	flag = copy_points_link(num[value], saver[1]);
	if (flag == -1)
	{
		free_points(saver[0]);
		return -1;
	}
	points_link_add_X_Y(saver[0], 4, 0);
	combine_two_point_links(saver[0], saver[1]);
	points_link_add_X_Y(saver[0],10, 0);


	flag = copy_points_link(num[10], saver[2]);
	if (flag == -1)
	{
		free_points(saver[0]);
		return -1;
	}
	points_link_add_X_Y(saver[0], 4, 0);
	combine_two_point_links(saver[0], saver[2]);
	points_link_add_X_Y(saver[0], k+1, 0);

	points_link_add_X_Y(saver[0], 4, 0);


	value = (tm->minute) % 10;
	flag = copy_points_link(num[value], saver[3]);
	if (flag == -1)
	{
		free_points(saver[0]);
		return -1;
	}
	points_link_add_X_Y(saver[0], 4, 0);
	combine_two_point_links(saver[0], saver[3]);
	points_link_add_X_Y(saver[0], k + 1, 0);

	value = (tm->minute) / 10;
	flag = copy_points_link(num[value], saver[4]);
	if (flag == -1)
	{
		free_points(saver[0]);
		return -1;
	}
	points_link_add_X_Y(saver[0], 4, 0);
	combine_two_point_links(saver[0], saver[4]);
	points_link_add_X_Y(saver[0], 10, 0);


	flag = copy_points_link(num[10],saver[5]);
	if (flag == -1)
	{
		free_points(saver[0]);
		return -1;
	}
	combine_two_point_links(saver[0], saver[5]);
	points_link_add_X_Y(saver[0], k+1, 0);

	points_link_add_X_Y(saver[0], 4, 0);

	value = (tm->hour) % 10;
	flag = copy_points_link(num[value], saver[6]);
	if (flag == -1)
	{
		free_points(saver[0]);
		return -1;
	}
	points_link_add_X_Y(saver[0], 4, 0);
	combine_two_point_links(saver[0], saver[6]);
	points_link_add_X_Y(saver[0], k + 1, 0);

	value = (tm->hour) / 10;
	flag = copy_points_link(num[value], saver[7]);
	if (flag == -1)
	{
		free_points(saver[0]);
		return -1;
	}
	points_link_add_X_Y(saver[0], 4, 0);
	combine_two_point_links(saver[0], saver[7]);
	points_link_add_X_Y(saver[0], k + 1, 0);

	points_link_add_X_Y(saver[0],X,Y);

	all_num = saver[0];
	return 1;
}