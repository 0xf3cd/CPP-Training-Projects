/*1550431 ����� �ƿ�����*/
#include<iostream>
using namespace std;

typedef long long ll;//for the sake of convenience
const ll base = 100000000;//99999999��8λ��Ϊһ����λ�ڿɱ��������
const ll unit_length = 8;
const int x_length = 100;
#define ERROR -1
#define SUCCESS 1

struct temp_saver
{
	char x[x_length];
	temp_saver *next = NULL;
};
void free_temp_saver(temp_saver*head);//�ͷ���ʱ����ռ�

struct element
{
	//��ֵΪ value*base^n
	//base=10^9
	ll value=0;
	ll n;
	/*����˫��������������ʱ��λ�ͽ�λ*/
	element *next = NULL;
	element *prior = NULL;
};
void free_element(element *head);//�ͷ�bigint�����ݴ���ռ�

class bigint
{
private:
	mutable ll elements_amounts=0;//element�ĸ���
	//ll number_amounts=0;//���ֵ�λ��
	mutable int sign = 1;//+ => 1 ,- => -1
	bool is_infinite = false;
	element* head=NULL;
	mutable element* last = NULL;//���ݴ���ṹ��β��㣬�������
public:
	bigint();
	~bigint();
	bigint(ll length);//����һ��bigint��������element������elements-amounts����Ա
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
	friend int abs_compare(const bigint& bi1,const bigint& bi2);//���Ǿ���ֵ��bi1==bi2 -> 0; bi1>bi2 -> 1;bi1<bi2 -> -1
};