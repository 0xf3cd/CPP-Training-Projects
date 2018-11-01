/*1550431 ����� �ƿ�����*/
#include "90-b5-adv.h"
#include <iomanip>

void free_temp_saver(temp_saver* head)
{
	temp_saver *now = head, *next;

	while (now != NULL)
	{
		next = now->next;
		delete now;
		now = next;
	}
}

void free_element(element* head)
{
	element *now = head, *next;

	while (now != NULL)
	{
		next = now->next;
		delete now;
		now = next;
	}
}

bigint::bigint()
{
}

bigint::~bigint()
{
	if (head != NULL)
	{
		free_element(head);
	}
}

bigint::bigint(ll length)
{
	if (length == 0)
	{
		//�ඨ�����Ѿ����˳�ֵ
		return;
	}

	ll i, n_counter = length - 1;
	element *now, *next;
	elements_amounts = length;

	head = new(nothrow) element;
	if (head == NULL)
	{
		cout << "��̬�ڴ��������\n";
		exit(ERROR);
	}

	now = head;
	for (i = 1; i <= length; i++)
	{
		next = new(nothrow) element;
		if (next == NULL)
		{
			cout << "��̬�ڴ��������\n";
			free_element(head);
			exit(ERROR);
		}

		next->n = n_counter--;
		now->next = next;
		next->prior = now;
		now = next;
	}

	last = now;
}

bigint::bigint(const bigint& bi)
{
	ll i;
	element *e_head, *e_now, *e_next, *p_to_bi = bi.head->next;

	sign = bi.sign;
	elements_amounts = bi.elements_amounts;
	is_infinite = bi.is_infinite;

	if (bi.head == NULL)
	{
		return;
	}

	e_head = new(nothrow) element;
	if (e_head == NULL)
	{
		cout << "��̬�ڴ��������\n";
		exit(ERROR);
	}
	e_now = e_head;
	head = e_head;

	for (i = 1; i <= elements_amounts; i++)
	{
		e_next = new(nothrow) element;
		if (e_next == NULL)
		{
			cout << "��̬�ڴ��������\n";
			free_element(e_head);
			exit(ERROR);
		}

		e_next->value = p_to_bi->value;
		e_now->next = e_next;
		e_next->prior = e_now;
		e_now = e_next;
		p_to_bi = p_to_bi->next;
	}

	last = e_now;
}

bigint::bigint(int x)
{
	 if(x<0)
	{
		x = -x;
		sign = -1;
	}

	elements_amounts = 1;
	head = new(nothrow) element;
	element*next = new(nothrow) element;
	if(head==NULL||next==NULL)
	{
		cout << "�ڴ�����ʧ��\n";
		if(head)
		{
			delete head;
		}
		exit(ERROR);
	}

	head->next = next;
	next->prior = head;
	last = next;
	next->n = 0;
	next->value = x;
}

void bigint::all_n_increase(ll inc) const
{
	element*p = head->next;

	while (p != NULL)
	{
		p->n += inc;
		p = p->next;
	}
}

bigint bigint::operator+ (const bigint& bi)//����������ֵ�Ӽ��ֿ�����
{
	if (sign*bi.sign == 1)//ͬ��
	{
		const bigint& bi_longer = (elements_amounts > bi.elements_amounts) ? (*this) : bi,
			&bi_shorter = (&bi_longer == &bi) ? (*this) : bi;
		const ll n_max = bi_longer.elements_amounts, n_min = bi_shorter.elements_amounts;
		ll i, result_of_divide;
		bigint temp(n_max);
		element* r1 = bi_longer.last, *r2 = bi_shorter.last, *rt = temp.last;//�ֱ�ָ��3��bigint��β���

		for (i = 1; i <= n_min; i++)
		{
			rt->value = r1->value + r2->value;

			r1 = r1->prior;
			r2 = r2->prior;
			rt = rt->prior;
		}

		for (i = n_min + 1; i <= n_max; i++)
		{
			rt->value = r1->value;

			r1 = r1->prior;
			rt = rt->prior;
		}

		//���ǽ�λ
		rt = temp.last;
		for (i = 2; i <= n_max; i++)
		{
			result_of_divide = rt->value / base;
			if (result_of_divide != 0)//��Ҫ��λ
			{
				rt->prior->value += result_of_divide;
				rt->value = rt->value%base;
			}

			rt = rt->prior;
		}//��ѭ��ʱ��rtָ�����λ

		//��������λ��λ����
		result_of_divide = rt->value / base;
		if (result_of_divide != 0)//��Ҫ��λ
		{
			element *add = new(nothrow) element;
			if (add == NULL)
			{
				cout << "��̬�ڴ��������\n";
				free_element(temp.head);
				exit(ERROR);
			}

			add->next = rt;
			rt->prior = add;
			head->next = add;
			add->prior = head;
			add->value = result_of_divide;
			rt->value = rt->value%base;
		}//end of��λ

		if (sign == 1)
		{
			return temp;
		}
		else
		{
			return -temp;
		}
	}
	else//���
	{
		//a(��)+b(��) <=> a(��) - (-b)(��)
		//a(��) + b(��) <=> a(��) - (-b)(��)
		//return *this - (-bigint(bi));
		int mark = abs_compare(*this, bi);//mark==1��������Ҫ+-�ŷ�ת��������Ҫ
		if (mark == 0)//*this == bi
		{
			return bigint(ll(0));//0
		}

		const bigint& bi_larger = (mark == 1) ? *this : bi, &bi_smaller = (mark == -1) ? *this : bi;
		ll n_max = bi_larger.elements_amounts, n_min = bi_smaller.elements_amounts, i, counts = 0;
		bigint temp(n_max);
		element* r1 = bi_larger.last, *r2 = bi_smaller.last, *rt = temp.last, *to_delete, *checker;

		//������ֻ��Ҫ���� bi_larger - bi_smaller, ���һ��Ϊ��, ����ķ�����+����-�����ⲿ�ּ���Ŀ��Ƿ�Χ��
		for (i = 1; i <= n_min; i++)
		{
			rt->value = r1->value - r2->value;

			r1 = r1->prior;
			r2 = r2->prior;
			rt = rt->prior;
		}

		for (i = n_min + 1; i <= n_max; i++)
		{
			rt->value = r1->value;

			r1 = r1->prior;
			rt = rt->prior;
		}

		//���ǽ�λ����
		rt = temp.last;
		for (i = 1; i <= n_max; i++)
		{
			if (rt->value < 0)
			{
				rt->value += base;
				rt->prior->value -= 1;
			}

			rt = rt->prior;
		}

		//�������λ����Ϊ0
		checker = temp.head->next;
		for (i = 1; i <= n_max; i++)
		{
			if (checker->value != 0)
			{
				break;
			}

			counts++;
			to_delete = checker;
			checker = checker->next;
			delete to_delete;
		}
		temp.elements_amounts -= counts;
		temp.head->next = checker;
		checker->prior = head;

		//���������
		if (sign*mark == 1)//mark==-1 -> ��Ҫ��ת��sign==-1 -> ��Ҫ��ת
		{
			return temp;
		}
		else
		{
			return -temp;
		}
	}
}

bigint bigint::operator- (const bigint& bi)//����������ֵ�Ӽ��ֿ����� //����ʱֻ���� �� - ��
{
	if (sign*bi.sign == 1)//ͬ�� �� - �� or �� - ��
	{
		//�� - �� -> -(�� - ��)
		//���Ե��� �� - �� ����
		int mark = abs_compare(*this, bi);//mark==1��������Ҫ+-�ŷ�ת��������Ҫ
		if (mark == 0)//*this == bi
		{
			return bigint(ll(0));//0
		}

		const bigint& bi_larger = (mark == 1) ? *this : bi, &bi_smaller = (mark == -1) ? *this : bi;
		ll n_max = bi_larger.elements_amounts, n_min = bi_smaller.elements_amounts, i, counts = 0;
		bigint temp(n_max);
		element* r1 = bi_larger.last, *r2 = bi_smaller.last, *rt = temp.last, *to_delete, *checker;

		//������ֻ��Ҫ���� bi_larger - bi_smaller, ���һ��Ϊ��, ����ķ�����+����-�����ⲿ�ּ���Ŀ��Ƿ�Χ��
		for (i = 1; i <= n_min; i++)
		{
			rt->value = r1->value - r2->value;

			r1 = r1->prior;
			r2 = r2->prior;
			rt = rt->prior;
		}

		for (i = n_min + 1; i <= n_max; i++)
		{
			rt->value = r1->value;

			r1 = r1->prior;
			rt = rt->prior;
		}

		//���ǽ�λ����
		rt = temp.last;
		for (i = 1; i <= n_max; i++)
		{
			if (rt->value < 0)
			{
				rt->value += base;
				rt->prior->value -= 1;
			}

			rt = rt->prior;
		}

		//�������λ����Ϊ0
		checker = temp.head->next;
		for (i = 1; i <= n_max; i++)
		{
			if (checker->value != 0)
			{
				break;
			}

			counts++;
			to_delete = checker;
			checker = checker->next;
			delete to_delete;
		}
		temp.elements_amounts -= counts;
		temp.head->next = checker;
		checker->prior = head;

		//���������
		if (sign*mark == 1)//mark==-1 -> ��Ҫ��ת��sign==-1 -> ��Ҫ��ת
		{
			return temp;
		}
		else
		{
			return -temp;
		}
	}
	else//���
	{
		//a(��)-b(��) <=> a(��)+(-b)(��)
		//a(��)-b(��) <=> a(��)+(-b)(��)
		//return (*this) + (-bigint(bi));
		const bigint& bi_longer = (elements_amounts > bi.elements_amounts) ? (*this) : bi,
			&bi_shorter = (&bi_longer == &bi) ? (*this) : bi;
		const ll n_max = bi_longer.elements_amounts, n_min = bi_shorter.elements_amounts;
		ll i, result_of_divide;
		bigint temp(n_max);
		element* r1 = bi_longer.last, *r2 = bi_shorter.last, *rt = temp.last;//�ֱ�ָ��3��bigint��β���

		for (i = 1; i <= n_min; i++)
		{
			rt->value = r1->value + r2->value;

			r1 = r1->prior;
			r2 = r2->prior;
			rt = rt->prior;
		}

		for (i = n_min + 1; i <= n_max; i++)
		{
			rt->value = r1->value;

			r1 = r1->prior;
			rt = rt->prior;
		}

		//���ǽ�λ
		rt = temp.last;
		for (i = 2; i <= n_max; i++)
		{
			result_of_divide = rt->value / base;
			if (result_of_divide != 0)//��Ҫ��λ
			{
				rt->prior->value += result_of_divide;
				rt->value = rt->value%base;
			}

			rt = rt->prior;
		}//��ѭ��ʱ��rtָ�����λ

		 //��������λ��λ����
		result_of_divide = rt->value / base;
		if (result_of_divide != 0)//��Ҫ��λ
		{
			element *add = new(nothrow) element;
			if (add == NULL)
			{
				cout << "��̬�ڴ��������\n";
				free_element(temp.head);
				exit(ERROR);
			}

			add->next = rt;
			rt->prior = add;
			head->next = add;
			add->prior = head;
			add->value = result_of_divide;
			rt->value = rt->value%base;
		}//end of��λ

		if (sign == 1)
		{
			return temp;
		}
		else
		{
			return -temp;
		}
	}
}

bigint bigint::operator* (const bigint& bi)
{
	bigint temp(elements_amounts + bi.elements_amounts - 1);
	ll  n_most_t = temp.elements_amounts - 1, n_most_1 = elements_amounts - 1, n_most_2 = bi.elements_amounts - 1, i, j, k, result_of_divide;
	element *p1, *p2, *pt;

	//base^k = base^i * base^j
	//������ģ�����ʽ�˷�
	p1 = last;
	for (i = 0; i <= n_most_1; i++)
	{
		pt = temp.last;
		for (k = 0; k < i; k++)
		{
			pt = pt->prior;
		}

		p2 = bi.last;
		for (j = 0; j <= n_most_2; j++)
		{
			pt->value = p1->value*p2->value;
			p2 = p2->prior;
			pt = pt->prior;
		}

		p1 = p1->prior;
	}

	//���ǽ�λ
	pt = temp.last;
	for (i = 1; i <= n_most_t; i++)
	{
		result_of_divide = pt->value / base;
		if (result_of_divide != 0)//��Ҫ��λ
		{
			pt->prior->value += result_of_divide;
			pt->value = pt->value%base;
		}

		pt = pt->prior;
	}//��ѭ��ʱ��ptָ�����λ

	 //��������λ��λ����
	result_of_divide = pt->value / base;
	if (result_of_divide != 0)//��Ҫ��λ
	{
		element *add = new(nothrow) element;
		if (add == NULL)
		{
			cout << "��̬�ڴ��������\n";
			free_element(temp.head);
			exit(ERROR);
		}

		add->next = pt;
		pt->prior = add;
		temp.head->next = add;
		add->prior = temp.head;
		add->value = result_of_divide;
		pt->value = pt->value%base;
	}//end of��λ

	element*checker, *to_delete;
	ll n_max=temp.elements_amounts-1,counts_=0;
	 //�������λ����Ϊ0
	checker = temp.head->next;
	for (i = 1; i <= n_max; i++)
	{
		if (checker->value != 0)
		{
			break;
		}

		counts_++;
		to_delete = checker;
		checker = checker->next;
		delete to_delete;
	}
	temp.elements_amounts -= counts_;
	temp.head->next = checker;
	checker->prior = head;

	temp.sign = sign*bi.sign;

	return temp;
}

bigint bigint::operator/ (const bigint& bi)
{
	if (bi.head == NULL)//bi==0
	{
		bigint temp(ll(0));
		temp.is_infinite = true;

		return temp;
	}

	int cmp_result = abs_compare(*this, bi);

	if (cmp_result == -1)//|*this|<|bi|
	{
		return bigint(ll(0));//return 0
	}
	else if (cmp_result == 0)//|*this|==|bi|
	{
		bigint temp(ll(1));
		temp.sign = sign*bi.sign;
		temp.head->next->value = 1;

		return temp;//return 1 or -1
	}
	else//|*this|>|bi|
	{
		//���ַ�����������hhh
		char* l;//l,s -> larger,smaller or longer,shorter
		ll l_length, s_length, i, temp_for_divide, highest_value, this_value, pos = 0,counts=0,res;
		element* p;
		bigint temp(ll(1));

		//*this����
		temp_for_divide = base / 10;//10000000
		highest_value = head->next->value;
		for (i = 8; i >= 1; i--)
		{
			if (highest_value / temp_for_divide != 0)
			{
				break;
			}

			temp_for_divide /= 10;
		}
		l_length = i;
		l_length += unit_length*(elements_amounts - 1);

		l = new(nothrow) char[unsigned(l_length + 1)];//'\0'
		if (l == NULL)
		{
			cout << "��̬�ڴ��������\n";
			exit(ERROR);
		}

		temp_for_divide = base / 10;//10000000
		highest_value = head->next->value;
		for (i = unit_length; i >= 1; i--)
		{
			if (highest_value / temp_for_divide != 0)
			{
				break;
			}

			temp_for_divide /= 10;
		}
		while (temp_for_divide != 0)
		{
			l[pos++] = char(highest_value / temp_for_divide + '0');
			highest_value %= temp_for_divide;
			temp_for_divide /= 10;
		}

		p = head->next->next;
		while (p != NULL)
		{
			this_value = p->value;
			temp_for_divide = base / 10;//10000000
			for (i = unit_length; i >= 1; i--)
			{
				l[pos++] = char(this_value / temp_for_divide + '0');
				this_value %= temp_for_divide;
				temp_for_divide /= 10;
			}

			p = p->next;
		}
		l[pos] = '\0';

		//bi����
		temp_for_divide = base / 10;//10000000
		highest_value = bi.head->next->value;
		for (i = 8; i >= 1; i--)
		{
			if (highest_value / temp_for_divide != 0)
			{
				break;
			}

			temp_for_divide /= 10;
		}
		s_length = i;
		s_length += unit_length*(bi.elements_amounts - 1);

		//cout << l << endl << s << endl;
		//l s correct

		pos = 0;
		bigint temp_bi(ll(1));
		temp_bi.head->next->value = 0;
		for(i=0;i<s_length;i++)
		{
			temp_bi *= bigint(10);
			temp_bi += bigint(l[pos++] - '0');
		}
		if (abs_compare(temp_bi, bi) == -1)//temp_bi<bi
		{
			temp_bi *= bigint(10);
			temp_bi += bigint(l[pos++] - '0');
		}

		i = 0;
		temp_saver* ts_head, *ts_now, *ts_next;
		ts_head = new(nothrow) temp_saver;
		if(ts_head==NULL)
		{
			cout << "��̬�ڴ��������\n";
			delete[]l;
			exit(ERROR);
		}
		ts_next = new(nothrow) temp_saver;
		if (ts_next == NULL)
		{
			cout << "��̬�ڴ��������\n";
			delete ts_head;
			delete[]l;
			exit(ERROR);
		}
		ts_now = ts_head;
		ts_now->next = ts_next;
		
		counts = 0;
		while(1)
		{
			res = 0;
			//cout << temp_bi << ' ';
			while(abs_compare(temp_bi, bi)==1)
			{
				res++;
				temp_bi -= bi;
			}
			if(abs_compare(temp_bi, bi) == 0)
			{
				res++;
				temp_bi = bigint(ll(1));
			}
			//cout << res << endl;
			

			if (i == x_length)//һ��temp_saver�����Դ���x_length���ַ�
			{
				i = 0;
				ts_next = new(nothrow) temp_saver;
				if (ts_next == NULL)
				{
					cout << "��̬�ڴ��������\n";
					free_temp_saver(ts_head);
					exit(ERROR);
				}

				//����ɹ�
				ts_now->next = ts_next;
				ts_now = ts_next;
			}

			*((ts_next->x) + i) = char(res + '0');
			i++;
			//cout << res << endl;

			if(pos>=l_length)
			{
				break;
			}

			counts++;
			//��������һ��
			temp_bi *= bigint(10);
			temp_bi += bigint(l[pos++] - '0');
		}//��ѭ��ʱ temp_bi Ϊ����

		//��temp_saver -> bigint
		ll numbers_of_elements, n_counter, first_element_length,temp_value,k,j;
		bigint result;
		numbers_of_elements = counts / unit_length;
		first_element_length = counts%unit_length;//��֤�����λ��element�⣬����ÿһ��element��������8����
		if (first_element_length == 0)
		{
			first_element_length = unit_length;
		}
		else
		{
			numbers_of_elements++;//���λ��element��Ҫһ�����
		}
		n_counter = numbers_of_elements - 1;

		//result.number_amounts = counts;
		result.elements_amounts = numbers_of_elements;//bigint�����ݵ�����

		element *e_head, *e_now, *e_next;

		e_head = new(nothrow) element;
		e_now = new(nothrow) element;
		if (e_head == NULL || e_now == NULL)
		{
			cout << "��̬�ڴ��������\n";
			free_temp_saver(ts_head);
			exit(ERROR);
		}
		e_head->next = e_now;
		e_now->prior = e_head;
		e_next = e_now;
		result.head = e_head;

		//�ȴ������λ��element
		ts_now = ts_head->next;
		i = 0;
		temp_value = 0;
		for (j = 1; j <= first_element_length; j++)
		{
			temp_value *= 10;
			temp_value += *(ts_now->x + i) - '0';
			i++;
		}
		e_next->value = temp_value;
		e_next->n = n_counter;
		n_counter--;

		//ʣ��elements,һ��(numbers_of_elements-1)��
		for (j = 1; j < numbers_of_elements; j++)
		{
			e_next = new(nothrow) element;
			if (e_next == NULL)
			{
				cout << "��̬�ڴ��������\n";
				free_temp_saver(ts_head);
				free_element(e_head);
				exit(ERROR);
			}

			//����ɹ�
			e_now->next = e_next;
			e_next->prior = e_now;
			e_now = e_next;

			temp_value = 0;
			for (k = 1; k <= unit_length; k++)
			{
				if (i == x_length)
				{
					ts_now = ts_now->next;
					i = 0;
				}

				temp_value *= 10;
				temp_value += *(ts_now->x + i) - '0';
				i++;
			}
			e_next->value = temp_value;
			e_next->n = n_counter;
			n_counter--;
		}//��ѭ��ʱ��e_nextָ��β�ڵ�

		result.last = e_next;
		result.sign = sign*bi.sign;

		element*checker, *to_delete;
		ll n_max = result.elements_amounts - 1, counts_ = 0;
		//�������λ����Ϊ0
		checker = result.head->next;
		for (i = 1; i <= n_max; i++)
		{
			if (checker->value != 0)
			{
				break;
			}

			counts_++;
			to_delete = checker;
			checker = checker->next;
			delete to_delete;
		}
		result.elements_amounts -= counts_;
		result.head->next = checker;
		checker->prior = head;

		free_temp_saver(ts_head);
		delete[]l;
		return result;
	}
}

bigint bigint::operator% (const bigint& bi)
{
	if (bi.head == NULL)//bi==0
	{
		bigint temp(ll(0));
		temp.is_infinite = true;

		return temp;
	}

	int cmp_result = abs_compare(*this, bi);

	if (cmp_result == -1)//|*this|<|bi|
	{
		return *this;//return 0
	}
	else if (cmp_result == 0)//|*this|==|bi|
	{
		bigint temp(ll(1));

		return temp;//return 1 or -1
	}
	else//|*this|>|bi|
	{
		//���ַ�����������hhh
		char* l;//l,s -> larger,smaller or longer,shorter
		ll l_length, s_length, i, temp_for_divide, highest_value, this_value, pos = 0, counts = 0, res;
		element* p;
		bigint temp(ll(1));

		//*this����
		temp_for_divide = base / 10;//10000000
		highest_value = head->next->value;
		for (i = 8; i >= 1; i--)
		{
			if (highest_value / temp_for_divide != 0)
			{
				break;
			}

			temp_for_divide /= 10;
		}
		l_length = i;
		l_length += unit_length*(elements_amounts - 1);

		l = new(nothrow) char[unsigned(l_length + 1)];//'\0'
		if (l == NULL)
		{
			cout << "��̬�ڴ��������\n";
			exit(ERROR);
		}

		temp_for_divide = base / 10;//10000000
		highest_value = head->next->value;
		for (i = unit_length; i >= 1; i--)
		{
			if (highest_value / temp_for_divide != 0)
			{
				break;
			}

			temp_for_divide /= 10;
		}
		while (temp_for_divide != 0)
		{
			l[pos++] = char(highest_value / temp_for_divide + '0');
			highest_value %= temp_for_divide;
			temp_for_divide /= 10;
		}

		p = head->next->next;
		while (p != NULL)
		{
			this_value = p->value;
			temp_for_divide = base / 10;//10000000
			for (i = unit_length; i >= 1; i--)
			{
				l[pos++] = char(this_value / temp_for_divide + '0');
				this_value %= temp_for_divide;
				temp_for_divide /= 10;
			}

			p = p->next;
		}
		l[pos] = '\0';

		//bi����
		temp_for_divide = base / 10;//10000000
		highest_value = bi.head->next->value;
		for (i = 8; i >= 1; i--)
		{
			if (highest_value / temp_for_divide != 0)
			{
				break;
			}

			temp_for_divide /= 10;
		}
		s_length = i;
		s_length += unit_length*(bi.elements_amounts - 1);

		//cout << l << endl << s << endl;
		//l s correct

		pos = 0;
		bigint temp_bi(ll(1));
		temp_bi.head->next->value = 0;
		for (i = 0; i<s_length; i++)
		{
			temp_bi *= bigint(10);
			temp_bi += bigint(l[pos++] - '0');
		}
		if (abs_compare(temp_bi, bi) == -1)//temp_bi<bi
		{
			temp_bi *= bigint(10);
			temp_bi += bigint(l[pos++] - '0');
		}

		i = 0;
		counts = 0;
		while (1)
		{
			res = 0;
			//cout << temp_bi << ' ';
			while (abs_compare(temp_bi, bi) == 1)
			{
				res++;
				temp_bi -= bi;
			}
			if (abs_compare(temp_bi, bi) == 0)
			{
				res++;
				temp_bi = bigint(ll(1));
			}
			//cout << res << endl;

			if (pos >= l_length)
			{
				break;
			}

			//��������һ��
			temp_bi *= bigint(10);
			temp_bi += bigint(l[pos++] - '0');
		}//��ѭ��ʱ temp_bi Ϊ����

		element*checker, *to_delete;
		ll n_max = temp_bi.elements_amounts - 1, counts_ = 0;
		//�������λ����Ϊ0
		checker = temp_bi.head->next;
		for (i = 1; i <= n_max; i++)
		{
			if (checker->value != 0)
			{
				break;
			}

			counts_++;
			to_delete = checker;
			checker = checker->next;
			delete to_delete;
		}
		temp_bi.elements_amounts -= counts_;
		temp_bi.head->next = checker;
		checker->prior = head;

		delete[]l;
		return temp_bi;
	}
}

bigint bigint::operator+ ()
{
	return *this;
}

bigint bigint::operator- ()
{
	bigint temp(*this);//���ø��ƹ��캯��
	temp.sign *= -1;

	return temp;
}

bigint& bigint::operator= (const bigint& bi)
{
	ll i;
	element *e_head, *e_now, *e_next, *p_to_bi = bi.head->next;

	sign = bi.sign;
	elements_amounts = bi.elements_amounts;
	is_infinite = bi.is_infinite;

	e_head = new(nothrow) element;
	if (e_head == NULL)
	{
		cout << "��̬�ڴ��������\n";
		exit(ERROR);
	}
	e_now = e_head;
	head = e_head;

	for (i = 1; i <= elements_amounts; i++)
	{
		e_next = new(nothrow) element;
		if (e_next == NULL)
		{
			cout << "��̬�ڴ��������\n";
			free_element(e_head);
			exit(ERROR);
		}

		e_next->n = p_to_bi->n;
		e_next->value = p_to_bi->value;
		e_now->next = e_next;
		e_next->prior = e_now;
		e_now = e_next;
		p_to_bi = p_to_bi->next;
	}

	last = e_now;
	return (*this);
}

bigint bigint::operator+= (const bigint& bi)
{
	if (sign*bi.sign == 1)//ͬ��
	{
		const bigint& bi_longer = (elements_amounts > bi.elements_amounts) ? (*this) : bi,
			&bi_shorter = (&bi_longer == &bi) ? (*this) : bi;
		const ll n_max = bi_longer.elements_amounts, n_min = bi_shorter.elements_amounts;
		ll i, result_of_divide;
		//bigint temp(n_max);
		element* r1 = bi_longer.last, *r2 = bi_shorter.last, *rt = last, *new_one;//�ֱ�ָ��3��bigint��β���

		if (this == &bi_shorter)
		{
			for (i = n_min; i < n_max; i++)
			{
				new_one = new(nothrow) element;
				if (new_one == NULL)
				{
					cout << "��̬�ڴ��������\n";
					exit(ERROR);
				}

				new_one->n = i;
				head->next->prior = new_one;
				new_one->next = head->next;
				new_one->prior = head;
				head->next = new_one;
			}
		}

		for (i = 1; i <= n_min; i++)
		{
			rt->value = r1->value + r2->value;

			r1 = r1->prior;
			r2 = r2->prior;
			rt = rt->prior;
		}

		for (i = n_min + 1; i <= n_max; i++)
		{
			rt->value = r1->value;

			r1 = r1->prior;
			rt = rt->prior;
		}

		//���ǽ�λ
		rt = last;
		for (i = 2; i <= n_max; i++)
		{
			result_of_divide = rt->value / base;
			if (result_of_divide != 0)//��Ҫ��λ
			{
				rt->prior->value += result_of_divide;
				rt->value = rt->value%base;
			}

			rt = rt->prior;
		}//��ѭ��ʱ��rtָ�����λ

		 //��������λ��λ����
		result_of_divide = rt->value / base;
		if (result_of_divide != 0)//��Ҫ��λ
		{
			element *add = new(nothrow) element;
			if (add == NULL)
			{
				cout << "��̬�ڴ��������\n";
				exit(ERROR);
			}

			add->next = rt;
			rt->prior = add;
			head->next = add;
			add->prior = head;
			add->value = result_of_divide;
			rt->value = rt->value%base;
		}//end of��λ

		return (*this);
	}
	else//���
	{
		//a(��)+b(��) <=> a(��) - (-b)(��)
		//a(��) + b(��) <=> a(��) - (-b)(��)
		int mark = abs_compare(*this, bi);//mark==1��������Ҫ+-�ŷ�ת��������Ҫ
		if (mark == 0)//*this == bi
		{
			free_element(head);
			head = NULL;
			last = NULL;
			elements_amounts = 0;
			sign = 1;
			return *this;
		}

		const bigint& bi_larger = (mark == 1) ? *this : bi, &bi_smaller = (mark == -1) ? *this : bi;
		ll n_max = bi_larger.elements_amounts, n_min = bi_smaller.elements_amounts, i, counts = 0;
		//bigint temp(n_max);
		element* r1 = bi_larger.last, *r2 = bi_smaller.last, *rt = last, *to_delete, *checker, *new_one;

		if (this == &bi_smaller)
		{
			for (i = n_min; i < n_max; i++)
			{
				new_one = new(nothrow) element;
				if (new_one == NULL)
				{
					cout << "��̬�ڴ��������\n";
					exit(ERROR);
				}

				new_one->n = i;
				head->next->prior = new_one;
				new_one->next = head->next;
				new_one->prior = head;
				head->next = new_one;
			}
		}

		//������ֻ��Ҫ���� bi_larger - bi_smaller, ���һ��Ϊ��, ����ķ�����+����-�����ⲿ�ּ���Ŀ��Ƿ�Χ��
		for (i = 1; i <= n_min; i++)
		{
			rt->value = r1->value - r2->value;

			r1 = r1->prior;
			r2 = r2->prior;
			rt = rt->prior;
		}

		for (i = n_min + 1; i <= n_max; i++)
		{
			rt->value = r1->value;

			r1 = r1->prior;
			rt = rt->prior;
		}

		//���ǽ�λ����
		rt = last;
		for (i = 1; i <= n_max; i++)
		{
			if (rt->value < 0)
			{
				rt->value += base;
				rt->prior->value -= 1;
			}

			rt = rt->prior;
		}

		//�������λ����Ϊ0
		checker = head->next;
		for (i = 1; i <= n_max; i++)
		{
			if (checker->value != 0)
			{
				break;
			}

			counts++;
			to_delete = checker;
			checker = checker->next;
			delete to_delete;
		}
		elements_amounts -= counts;
		head->next = checker;
		checker->prior = head;

		//���������
		sign *= mark;

		return *this;
	}
}

bigint bigint::operator-= (const bigint& bi)
{
	if (sign*bi.sign == -1)//���
	{
		const bigint& bi_longer = (elements_amounts > bi.elements_amounts) ? (*this) : bi,
			&bi_shorter = (&bi_longer == &bi) ? (*this) : bi;
		const ll n_max = bi_longer.elements_amounts, n_min = bi_shorter.elements_amounts;
		ll i, result_of_divide;
		//bigint temp(n_max);
		element* r1 = bi_longer.last, *r2 = bi_shorter.last, *rt = last, *new_one;//�ֱ�ָ��3��bigint��β���

		if (this == &bi_shorter)
		{
			for (i = n_min; i < n_max; i++)
			{
				new_one = new(nothrow) element;
				if (new_one == NULL)
				{
					cout << "��̬�ڴ��������\n";
					exit(ERROR);
				}

				new_one->n = i;
				head->next->prior = new_one;
				new_one->next = head->next;
				new_one->prior = head;
				head->next = new_one;
			}
		}

		for (i = 1; i <= n_min; i++)
		{
			rt->value = r1->value + r2->value;

			r1 = r1->prior;
			r2 = r2->prior;
			rt = rt->prior;
		}

		for (i = n_min + 1; i <= n_max; i++)
		{
			rt->value = r1->value;

			r1 = r1->prior;
			rt = rt->prior;
		}

		//���ǽ�λ
		rt = last;
		for (i = 2; i <= n_max; i++)
		{
			result_of_divide = rt->value / base;
			if (result_of_divide != 0)//��Ҫ��λ
			{
				rt->prior->value += result_of_divide;
				rt->value = rt->value%base;
			}

			rt = rt->prior;
		}//��ѭ��ʱ��rtָ�����λ

		 //��������λ��λ����
		result_of_divide = rt->value / base;
		if (result_of_divide != 0)//��Ҫ��λ
		{
			element *add = new(nothrow) element;
			if (add == NULL)
			{
				cout << "��̬�ڴ��������\n";
				exit(ERROR);
			}

			add->next = rt;
			rt->prior = add;
			head->next = add;
			add->prior = head;
			add->value = result_of_divide;
			rt->value = rt->value%base;
		}//end of��λ

		return (*this);
	}
	else//ͬ��
	{
		int mark = abs_compare(*this, bi);//mark==1��������Ҫ+-�ŷ�ת��������Ҫ
		if (mark == 0)//*this == bi
		{
			free_element(head);
			head = NULL;
			last = NULL;
			elements_amounts = 0;
			sign = 1;
			return *this;
		}

		const bigint& bi_larger = (mark == 1) ? *this : bi, &bi_smaller = (mark == -1) ? *this : bi;
		ll n_max = bi_larger.elements_amounts, n_min = bi_smaller.elements_amounts, i, counts = 0;
		//bigint temp(n_max);
		element* r1 = bi_larger.last, *r2 = bi_smaller.last, *rt = last, *to_delete, *checker, *new_one;

		if (this == &bi_smaller)
		{
			for (i = n_min; i < n_max; i++)
			{
				new_one = new(nothrow) element;
				if (new_one == NULL)
				{
					cout << "��̬�ڴ��������\n";
					exit(ERROR);
				}

				new_one->n = i;
				head->next->prior = new_one;
				new_one->next = head->next;
				new_one->prior = head;
				head->next = new_one;
			}
		}

		//������ֻ��Ҫ���� bi_larger - bi_smaller, ���һ��Ϊ��, ����ķ�����+����-�����ⲿ�ּ���Ŀ��Ƿ�Χ��
		for (i = 1; i <= n_min; i++)
		{
			rt->value = r1->value - r2->value;

			r1 = r1->prior;
			r2 = r2->prior;
			rt = rt->prior;
		}

		for (i = n_min + 1; i <= n_max; i++)
		{
			rt->value = r1->value;

			r1 = r1->prior;
			rt = rt->prior;
		}

		//���ǽ�λ����
		rt = last;
		for (i = 1; i <= n_max; i++)
		{
			if (rt->value < 0)
			{
				rt->value += base;
				rt->prior->value -= 1;
			}

			rt = rt->prior;
		}

		//�������λ����Ϊ0
		checker = head->next;
		for (i = 1; i <= n_max; i++)
		{
			if (checker->value != 0)
			{
				break;
			}

			counts++;
			to_delete = checker;
			checker = checker->next;
			delete to_delete;
		}
		elements_amounts -= counts;
		head->next = checker;
		checker->prior = head;

		//���������
		sign *= mark;

		return *this;
	}
}

bigint bigint::operator*= (const bigint& bi)
{
	bigint temp(elements_amounts + bi.elements_amounts - 1);
	ll  n_most_t = temp.elements_amounts - 1, n_most_1 = elements_amounts - 1, n_most_2 = bi.elements_amounts - 1, i, j, k, result_of_divide;
	element *p1, *p2, *pt;

	//base^k = base^i * base^j
	//������ģ�����ʽ�˷�
	p1 = last;
	for (i = 0; i <= n_most_1; i++)
	{
		pt = temp.last;
		for (k = 0; k < i; k++)
		{
			pt = pt->prior;
		}

		p2 = bi.last;
		for (j = 0; j <= n_most_2; j++)
		{
			pt->value = p1->value*p2->value;
			p2 = p2->prior;
			pt = pt->prior;
		}

		p1 = p1->prior;
	}

	//���ǽ�λ
	pt = temp.last;
	for (i = 1; i <= n_most_t; i++)
	{
		result_of_divide = pt->value / base;
		if (result_of_divide != 0)//��Ҫ��λ
		{
			pt->prior->value += result_of_divide;
			pt->value = pt->value%base;
		}

		pt = pt->prior;
	}//��ѭ��ʱ��ptָ�����λ

	 //��������λ��λ����
	result_of_divide = pt->value / base;
	if (result_of_divide != 0)//��Ҫ��λ
	{
		element *add = new(nothrow) element;
		if (add == NULL)
		{
			cout << "��̬�ڴ��������\n";
			free_element(temp.head);
			exit(ERROR);
		}

		add->next = pt;
		pt->prior = add;
		temp.head->next = add;
		add->prior = temp.head;
		add->value = result_of_divide;
		pt->value = pt->value%base;
	}//end of��λ

	temp.sign = sign*bi.sign;

	element*checker, *to_delete;
	ll n_max = temp.elements_amounts - 1, counts_ = 0;
	//�������λ����Ϊ0
	checker = temp.head->next;
	for (i = 1; i <= n_max; i++)
	{
		if (checker->value != 0)
		{
			break;
		}

		counts_++;
		to_delete = checker;
		checker = checker->next;
		delete to_delete;
	}
	temp.elements_amounts -= counts_;
	temp.head->next = checker;
	checker->prior = head;

	free_element(head);
	*this = temp;

	return temp;
}

bigint bigint::operator/= (const bigint& bi)
{
	bigint temp = *this / bi;

	element*checker, *to_delete;
	ll n_max = temp.elements_amounts - 1, counts_ = 0,i;
	//�������λ����Ϊ0
	checker = temp.head->next;
	for (i = 1; i <= n_max; i++)
	{
		if (checker->value != 0)
		{
			break;
		}

		counts_++;
		to_delete = checker;
		checker = checker->next;
		delete to_delete;
	}
	temp.elements_amounts -= counts_;
	temp.head->next = checker;
	checker->prior = head;

	free_element(head);
	*this = temp;

	return temp;
}

bigint bigint::operator%= (const bigint& bi)
{
	bigint temp = *this % bi;

	element*checker, *to_delete;
	ll n_max = temp.elements_amounts - 1, counts_ = 0,i;
	//�������λ����Ϊ0
	checker = temp.head->next;
	for (i = 1; i <= n_max; i++)
	{
		if (checker->value != 0)
		{
			break;
		}

		counts_++;
		to_delete = checker;
		checker = checker->next;
		delete to_delete;
	}
	temp.elements_amounts -= counts_;
	temp.head->next = checker;
	checker->prior = head;

	free_element(head);
	*this = temp;

	return temp;
}

bigint& bigint::operator++ ()
{
	element *p = last, *checker, *to_delete;
	ll result_of_divide, i, counts = 0;

	if (sign == 1)//+
	{
		last->value += 1;

		while (p != head)//��λ
		{
			result_of_divide = p->value / base;
			if (result_of_divide == 0)
			{
				break;
			}

			p->value -= base;
			p->prior->value++;
			p = p->prior;
		}
	}
	else//-
	{
		last->value -= 1;

		while (p != head)//��λ
		{
			if (p->value >= 0)
			{
				break;
			}

			p->value += base;
			p->prior->value--;
			p = p->prior;
		}

		checker = head->next;
		for (i = 1; i <= elements_amounts; i++)//��֤���λ��Ϊ0
		{
			if (checker->value != 0)
			{
				break;
			}

			counts++;
			to_delete = checker;
			checker = checker->next;
			delete to_delete;
		}
		elements_amounts -= counts;
		head->next = checker;
		checker->prior = head;
	}

	return *this;
}

bigint bigint::operator++ (int)
{
	bigint temp(*this);
	element *p = last, *checker, *to_delete;
	ll result_of_divide, i, counts = 0;

	if (sign == 1)//+
	{
		last->value += 1;

		while (p != head)//��λ
		{
			result_of_divide = p->value / base;
			if (result_of_divide == 0)
			{
				break;
			}

			p->value -= base;
			p->prior->value++;
			p = p->prior;
		}
	}
	else//-
	{
		last->value -= 1;

		while (p != head)//��λ
		{
			if (p->value >= 0)
			{
				break;
			}

			p->value += base;
			p->prior->value--;
			p = p->prior;
		}

		checker = head->next;
		for (i = 1; i <= elements_amounts; i++)//��֤���λ��Ϊ0
		{
			if (checker->value != 0)
			{
				break;
			}

			counts++;
			to_delete = checker;
			checker = checker->next;
			delete to_delete;
		}
		elements_amounts -= counts;
		head->next = checker;
		checker->prior = head;
	}

	return temp;
}

bigint& bigint::operator-- ()
{
	element *p = last, *checker, *to_delete;
	ll result_of_divide, i, counts = 0;

	if (sign == -1)//-
	{
		last->value += 1;

		while (p != head)//��λ
		{
			result_of_divide = p->value / base;
			if (result_of_divide == 0)
			{
				break;
			}

			p->value -= base;
			p->prior->value++;
			p = p->prior;
		}
	}
	else//+
	{
		last->value -= 1;

		while (p != head)//��λ
		{
			if (p->value >= 0)
			{
				break;
			}

			p->value += base;
			p->prior->value--;
			p = p->prior;
		}

		checker = head->next;
		for (i = 1; i <= elements_amounts; i++)//��֤���λ��Ϊ0
		{
			if (checker->value != 0)
			{
				break;
			}

			counts++;
			to_delete = checker;
			checker = checker->next;
			delete to_delete;
		}
		elements_amounts -= counts;
		head->next = checker;
		checker->prior = head;
	}

	return *this;
}

bigint bigint::operator-- (int)
{
	bigint temp(*this);
	element *p = last, *checker, *to_delete;
	ll result_of_divide, i, counts = 0;

	if (sign == -1)//-
	{
		last->value += 1;

		while (p != head)//��λ
		{
			result_of_divide = p->value / base;
			if (result_of_divide == 0)
			{
				break;
			}

			p->value -= base;
			p->prior->value++;
			p = p->prior;
		}
	}
	else//+
	{
		last->value -= 1;

		while (p != head)//��λ
		{
			if (p->value >= 0)
			{
				break;
			}

			p->value += base;
			p->prior->value--;
			p = p->prior;
		}

		checker = head->next;
		for (i = 1; i <= elements_amounts; i++)//��֤���λ��Ϊ0
		{
			if (checker->value != 0)
			{
				break;
			}

			counts++;
			to_delete = checker;
			checker = checker->next;
			delete to_delete;
		}
		elements_amounts -= counts;
		head->next = checker;
		checker->prior = head;
	}

	return temp;
}

bool operator> (const bigint& bi1, const bigint& bi2)
{
	if (bi1.head == NULL)//bi1==0
	{
		if (bi2.sign == -1 && bi2.head != NULL)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	if (bi2.head == NULL)//bi2==0
	{
		if (bi1.sign == 1 && bi1.head != NULL)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	if (bi1.sign == 1 && bi2.sign == -1)
	{
		return true;
	}

	if (bi1.sign == -1 && bi2.sign == 1)
	{
		return false;
	}

	//������bi1 bi2ͬ�ŵ����
	if (bi1.elements_amounts > bi2.elements_amounts)
	{
		if (bi1.sign == 1)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else	if (bi1.elements_amounts < bi2.elements_amounts)
	{
		if (bi1.sign == 1)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	else//bi1.elements_amounts==bi2.elements_amounts
	{
		ll i, amounts = bi1.elements_amounts;
		element *p1 = bi1.head->next, *p2 = bi2.head->next;

		for (i = 1; i <= amounts; i++)
		{
			if (p1->value > p2->value)
			{
				if (bi1.sign == 1)
				{
					return true;
				}
				else
				{
					return false;
				}
			}
			else if (p1->value < p2->value)
			{
				if (bi1.sign == 1)
				{
					return false;
				}
				else
				{
					return true;
				}
			}

			//p1->value==p2->value
			p1 = p1->next;
			p2 = p2->next;
		}
	}

	//��ѭ������Ȼ�޽��˵�����
	return false;
}

bool operator< (const bigint& bi1, const bigint& bi2)
{
	//<=> bi2>bi1
	if (bi2.head == NULL)//bi2==0
	{
		if (bi1.sign == -1 && bi1.head != NULL)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	if (bi1.head == NULL)//bi1==0
	{
		if (bi2.sign == 1 && bi2.head != NULL)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	if (bi2.sign == 1 && bi1.sign == -1)
	{
		return true;
	}

	if (bi2.sign == -1 && bi1.sign == 1)
	{
		return false;
	}

	//������bi2 bi1ͬ�ŵ����
	if (bi2.elements_amounts > bi1.elements_amounts)
	{
		if (bi2.sign == 1)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else	if (bi2.elements_amounts < bi1.elements_amounts)
	{
		if (bi2.sign == 1)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	else//bi2.elements_amounts==bi1.elements_amounts
	{
		ll i, amounts = bi2.elements_amounts;
		element *p1 = bi2.head->next, *p2 = bi1.head->next;

		for (i = 1; i <= amounts; i++)
		{
			if (p1->value > p2->value)
			{
				if (bi2.sign == 1)
				{
					return true;
				}
				else
				{
					return false;
				}
			}
			else if (p1->value < p2->value)
			{
				if (bi2.sign == 1)
				{
					return false;
				}
				else
				{
					return true;
				}
			}

			//p1->value==p2->value
			p1 = p1->next;
			p2 = p2->next;
		}
	}

	//��ѭ������Ȼ�޽��˵�����
	return false;
}

bool operator<= (const bigint& bi1, const bigint& bi2)
{
	//<=> bi2>=bi1
	if (bi2.head == NULL)//bi2==0
	{
		if (bi1.sign == -1 || bi1.head == NULL)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	if (bi1.head == NULL)//bi1==0
	{
		if (bi2.sign == 1 || bi2.head == NULL)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	if (bi2.sign == 1 && bi1.sign == -1)
	{
		return true;
	}

	if (bi2.sign == -1 && bi1.sign == 1)
	{
		return false;
	}

	//������bi2 bi1ͬ�ŵ����
	if (bi2.elements_amounts > bi1.elements_amounts)
	{
		if (bi2.sign == 1)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else	if (bi2.elements_amounts < bi1.elements_amounts)
	{
		if (bi2.sign == 1)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	else//bi2.elements_amounts==bi1.elements_amounts
	{
		ll i, amounts = bi2.elements_amounts;
		element *p1 = bi2.head->next, *p2 = bi1.head->next;

		for (i = 1; i <= amounts; i++)
		{
			if (p1->value > p2->value)
			{
				if (bi2.sign == 1)
				{
					return true;
				}
				else
				{
					return false;
				}
			}
			else if (p1->value < p2->value)
			{
				if (bi2.sign == 1)
				{
					return false;
				}
				else
				{
					return true;
				}
			}

			//p1->value==p2->value
			p1 = p1->next;
			p2 = p2->next;
		}
	}

	//��ѭ������Ȼ�޽��˵�����
	return true;
}

bool operator>= (const bigint& bi1, const bigint& bi2)
{
	if (bi1.head == NULL)//bi1==0
	{
		if (bi2.sign == -1 || bi2.head == NULL)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	if (bi2.head == NULL)//bi2==0
	{
		if (bi1.sign == 1 || bi1.head == NULL)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	if (bi1.sign == 1 && bi2.sign == -1)
	{
		return true;
	}

	if (bi1.sign == -1 && bi2.sign == 1)
	{
		return false;
	}

	//������bi1 bi2ͬ�ŵ����
	if (bi1.elements_amounts > bi2.elements_amounts)
	{
		if (bi1.sign == 1)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else	if (bi1.elements_amounts < bi2.elements_amounts)
	{
		if (bi1.sign == 1)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	else//bi1.elements_amounts==bi2.elements_amounts
	{
		ll i, amounts = bi1.elements_amounts;
		element *p1 = bi1.head->next, *p2 = bi2.head->next;

		for (i = 1; i <= amounts; i++)
		{
			if (p1->value > p2->value)
			{
				if (bi1.sign == 1)
				{
					return true;
				}
				else
				{
					return false;
				}
			}
			else if (p1->value < p2->value)
			{
				if (bi1.sign == 1)
				{
					return false;
				}
				else
				{
					return true;
				}
			}

			//p1->value==p2->value
			p1 = p1->next;
			p2 = p2->next;
		}
	}

	//��ѭ������Ȼ�޽��˵�����
	return true;
}

bool operator== (const bigint& bi1, const bigint& bi2)
{
	if (bi1.head == NULL)//bi1==0
	{
		if (bi2.head == NULL)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	if (bi2.head == NULL)//bi2==0
	{
		if (bi1.head == NULL)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	//���ų�bi1==bi2==0�����
	if (bi1.sign*bi2.sign != 1)
	{
		return false;
	}//bi1 bi2������ͬ

	if (bi1.elements_amounts != bi2.elements_amounts)
	{
		return false;
	}//elements����ͬ

	ll i, amounts = bi1.elements_amounts;
	element *p1 = bi1.head->next, *p2 = bi2.head->next;
	for (i = 1; i <= amounts; i++)
	{
		if (p1->value != p2->value)
		{
			return false;
		}

		p1 = p1->next;
		p2 = p2->next;
	}

	return true;
}

bool operator!= (const bigint& bi1, const bigint& bi2)
{
	if (bi2 == bi1)
	{
		return false;
	}

	return true;
}

istream& operator >> (istream& in, bigint& bi)
{
	temp_saver *ts_head, *ts_now, *ts_next;
	ll counts = 0, numbers_of_elements, first_element_length, temp_value, n_counter, i = 0, j, k;
	char saver;

	ts_head = new(nothrow) temp_saver;
	ts_next = new(nothrow) temp_saver;
	if (ts_head == NULL || ts_next == NULL)
	{
		cout << "��̬�ڴ��������\n";
		exit(ERROR);
	}
	ts_head->next = ts_next;
	ts_now = ts_next;

	if (in.peek() == '-')//Ϊ����
	{
		bi.sign = -1;
		in.get();//��ȡ���ţ�֮��Ĵ洢����������
	}
	else if (in.peek() == '0')
	{
		return in;
	}

	while (1)//���뻺�������ݣ�����temp_saver����
	{
		saver = in.get();

		if (saver<'0' || saver>'9')
		{
			break;
		}
		else
		{
			counts++;//����

			if (i == x_length)//һ��temp_saver�����Դ���x_length���ַ�
			{
				i = 0;
				ts_next = new(nothrow) temp_saver;
				if (ts_next == NULL)
				{
					cout << "��̬�ڴ��������\n";
					free_temp_saver(ts_head);
					exit(ERROR);
				}

				//����ɹ�
				ts_now->next = ts_next;
				ts_now = ts_next;
			}

			*((ts_next->x) + i) = saver;
			i++;
		}
	}

	//��ѭ��ʱ��counts�����������ַ���
	//ts_next: ��temp_saver���ݴ���elememt������

	//unit_length(=8) ��һ��element��������������λ�� 
	//that is to say, ����ṹ�� base(=10^9) Ϊ��������, ÿ��element����00000000-99999999
	numbers_of_elements = counts / unit_length;
	first_element_length = counts%unit_length;//��֤�����λ��element�⣬����ÿһ��element��������8����
	if (first_element_length == 0)
	{
		first_element_length = unit_length;
	}
	else
	{
		numbers_of_elements++;//���λ��element��Ҫһ�����
	}
	n_counter = numbers_of_elements - 1;

	//bi.number_amounts = counts;
	bi.elements_amounts = numbers_of_elements;//bigint�����ݵ�����

	element *e_head, *e_now, *e_next;

	e_head = new(nothrow) element;
	e_now = new(nothrow) element;
	if (e_head == NULL || e_now == NULL)
	{
		cout << "��̬�ڴ��������\n";
		free_temp_saver(ts_head);
		exit(ERROR);
	}
	e_head->next = e_now;
	e_now->prior = e_head;
	e_next = e_now;
	bi.head = e_head;

	//�ȴ������λ��element
	ts_now = ts_head->next;
	i = 0;
	temp_value = 0;
	for (j = 1; j <= first_element_length; j++)
	{
		temp_value *= 10;
		temp_value += *(ts_now->x + i) - '0';
		i++;
	}
	e_next->value = temp_value;
	e_next->n = n_counter;
	n_counter--;

	//ʣ��elements,һ��(numbers_of_elements-1)��
	for (j = 1; j < numbers_of_elements; j++)
	{
		e_next = new(nothrow) element;
		if (e_next == NULL)
		{
			cout << "��̬�ڴ��������\n";
			free_temp_saver(ts_head);
			free_element(e_head);
			exit(ERROR);
		}

		//����ɹ�
		e_now->next = e_next;
		e_next->prior = e_now;
		e_now = e_next;

		temp_value = 0;
		for (k = 1; k <= unit_length; k++)
		{
			if (i == x_length)
			{
				ts_now = ts_now->next;
				i = 0;
			}

			temp_value *= 10;
			temp_value += *(ts_now->x + i) - '0';
			i++;
		}
		e_next->value = temp_value;
		e_next->n = n_counter;
		n_counter--;
	}//��ѭ��ʱ��e_nextָ��β�ڵ�

	bi.last = e_next;
	free_temp_saver(ts_head);
	return in;
}

ostream& operator<< (ostream& out, const bigint& bi)
{
	if (bi.head == NULL)
	{
		out << setw(1) << 0;
		return out;
	}
	else if (bi.is_infinite)
	{
		out <<setw(4)<< "#INF";
		return out;
	}
	else if(bi.elements_amounts==1&&bi.head->next->value==0)
	{
		out <<setw(1)<< 0;
		return out;
	}
	element *now = (bi.head->next);//ָ��bigint�ĸ������ݴ���ĳ�Ա����Ԫ���

	if (bi.sign == -1)
	{
		out << setw(1)<<'-';
	}

	if (now != NULL)
	{
		cout << left << now->value;
		now = now->next;
	}

	while (now != NULL)
	{
		out << setw(unit_length) << setfill('0') << now->value;
		now = now->next;
	}

	return out;
}

int abs_compare(const bigint& bi1, const bigint& bi2)// bi1==bi2 -> 0; bi1>bi2 -> 1;bi1<bi2 -> -1
{
	if (bi1.head == NULL)//bi1==0
	{
		if (bi2.head != NULL)
		{
			return -1;
		}
		if (bi2.head == NULL)
		{
			return 0;
		}
	}

	if (bi2.head == NULL)//bi2==0
	{
		if (bi1.head != NULL)
		{
			return 1;
		}
		else if (bi1.head == NULL)
		{
			return 0;
		}
	}

	if (bi1.elements_amounts > bi2.elements_amounts)
	{
		return 1;
	}
	else	if (bi1.elements_amounts < bi2.elements_amounts)
	{
		return -1;
	}
	else//bi1.elements_amounts==bi2.elements_amounts
	{
		ll i, amounts = bi1.elements_amounts;
		element *p1 = bi1.head->next, *p2 = bi2.head->next;

		for (i = 1; i <= amounts; i++)
		{
			if (p1->value > p2->value)
			{
				return 1;
			}
			else if (p1->value < p2->value)
			{
				return -1;
			}

			//p1->value==p2->value
			p1 = p1->next;
			p2 = p2->next;
		}
	}

	//��ѭ������Ȼ�޽��˵�����
	return 0;
}