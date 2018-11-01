/*1550431 王甯琪 计科三班*/
#include<iostream>
using namespace std;

typedef long long ll;//for the sake of convenience
const ll base = 100000000;//99999999，8位，为一个单位内可表达的最大数
const ll unit_length = 8;
const int x_length = 100;
#define ERROR -1
#define SUCCESS 1

struct temp_saver
{
	char x[x_length];
	temp_saver *next = NULL;
};
void free_temp_saver(temp_saver*head);//释放临时储存空间

struct element
{
	//数值为 value*base^n
	//base=10^9
	ll value=0;
	ll n;
	/*建立双向链表，方便运算时借位和进位*/
	element *next = NULL;
	element *prior = NULL;
};
void free_element(element *head);//释放bigint的数据储存空间

class bigint
{
private:
	mutable ll elements_amounts=0;//element的个数
	//ll number_amounts=0;//数字的位数
	mutable int sign = 1;//+ => 1 ,- => -1
	bool is_infinite = false;
	element* head=NULL;
	mutable element* last = NULL;//数据储存结构的尾结点，方便计算
public:
	bigint();
	~bigint();
	bigint(ll length);//生成一个bigint变量，其element链表有elements-amounts个成员
	bigint(const bigint& b);
	bigint(int x);
	void all_n_increase(ll inc) const;
	bigint operator+(const bigint& bi);
	bigint operator-(const bigint& bi);
	bigint operator*(const bigint& bi);
	bigint operator/(const bigint& bi);
	bigint operator%(const bigint& bi);
	bigint operator+();
	bigint operator-();
	bigint& operator=(const bigint& bi);
	bigint operator+=(const bigint& bi);
	bigint operator-=(const bigint& bi);
	bigint operator*=(const bigint& bi);
	bigint operator/=(const bigint& bi);
	bigint operator%=(const bigint& bi);
	bigint& operator++();
	bigint operator++(int);
	bigint& operator--();
	bigint operator--(int);
	friend bool operator>(const bigint &bi1, const bigint &bi2);
	friend bool operator<(const bigint &bi1, const bigint &bi2);
	friend bool operator<=(const bigint &bi1, const bigint &bi2);
	friend bool operator>=(const bigint &bi1, const bigint &bi2);
	friend bool operator==(const bigint &bi1, const bigint &bi2);
	friend bool operator!=(const bigint &bi1, const bigint &bi2);
	friend istream& operator >> (istream &in, bigint& bi);
	friend ostream& operator << (ostream &in, const bigint& bi);
	friend int abs_compare(const bigint& bi1,const bigint& bi2);//考虑绝对值，bi1==bi2 -> 0; bi1>bi2 -> 1;bi1<bi2 -> -1
};