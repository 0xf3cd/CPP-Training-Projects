/*1550431 ����� �ƿ�����*/
#include <iostream>
#include "90-b5-adv.h"
using namespace std;

bigint fun(bigint x)
{
	x += x;
	return x--;
}

int main()
{
	bigint a, b,c,d;

	cout << "������a��b" << endl;
	cin >> a >> b;
	
	cout << "=���ز���" << endl;
	c = a;
	d = b;
	cout << c << endl;

	cout << "++ --" << endl;
	cout << a++ << endl;
	cout << b-- << endl;
	cout << ++c << endl;
	cout << --d << endl;

	cout << "+ - * / %  += -= *= /= %=" << endl;
	cout << a + b << endl;
	cout << a - b << endl;
	cout << a*b << endl;
	cout << d*c << endl;
	cout << a / b << endl;
	cout << a%b << endl;
	c += a;
	cout << c << endl;
	c -= b;
	cout << c << endl;
	c *= a;
	cout << c << endl;
	c /= a;
	cout << c << endl;
	c %= a;
	cout << c << endl;

	cout << "others" << endl;
	c = -a;
	cout << c << endl;
	c = +b;
	cout << c << endl;
	cout << (b == c) << endl;
	cout << (a != c) << endl;
	cout << (a > b) << endl;
	cout << (a >= b) << endl;
	cout << (a < b) << endl;
	cout << (a <= b) << endl;

	cout << fun(a) << endl;

	return SUCCESS;
}