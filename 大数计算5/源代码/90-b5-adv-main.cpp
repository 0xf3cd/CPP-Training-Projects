/*1550431 王甯琪 计科三班*/
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

	cout << "请输入a和b" << endl;
	cin >> a >> b;
	
	cout << "=重载测试" << endl;
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