/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "ClassLongNum.h"

#define naive_len 10 


LongNum::LongNum() {}

LongNum::LongNum(const int& other)
{
	if (other == 0)
	{
		long_num.push_back(0);
	}
	else
	{
		int x = other;
		while (x > 0)
		{
			long_num.push_back(x % 10);
			x /= 10;
		}
	}
}

LongNum::LongNum(string s)
{
	while (s.length() != 0)
	{
		long_num.push_back(s[s.length() - 1] - '0');
		s.erase(s.length() - 1, s.length());
	}

}

LongNum::LongNum(vector <int> newLong)
{
	long_num = newLong;
}


LongNum::LongNum(const LongNum& other)
{
	operator = (other);
}

vector<int>  LongNum::getLongNumber()
{ 
	return long_num; 
}

void LongNum::write() const
{
	for (auto i = long_num.end() ; i != long_num.begin(); )
		cout << *(--i);
}

bool LongNum::operator < (const LongNum& other)const
{
    
	if (long_num[long_num.size() - 1] < 0 && other == LongNum("0")) return true;
	int alen = long_num.size(), blen = other.long_num.size();
	if (alen != blen) return alen < blen;
	for (int i = alen - 1; i >= 0; --i) {
		if (long_num[i] != other.long_num[i]) {
			return long_num[i] < other.long_num[i];
		}
	}
	return false;
}

bool LongNum::operator == (const LongNum& other)const
{
	if (long_num.size() != other.long_num.size()) return false;
	for (int i = 0; i < max(long_num.size(), other.long_num.size()); ++i) {
		if (!(long_num[i] == other.long_num[i])) return false;
	}
	return true;
}

bool LongNum::operator <= (const LongNum& other)const
{
	return operator==(other) || operator<(other);
}


LongNum& LongNum::operator = (const LongNum &other)
{
	long_num = other.long_num;
	return *this;
}
bool LongNum::operator > (const LongNum& other)const
{
    return !(*this <=(other));
}

LongNum LongNum::operator - () const {
	LongNum nw, old;
	old = *this;
	nw = old;
	nw.long_num[nw.long_num.size() - 1] = -long_num[nw.long_num.size() - 1];
	return nw;
}


LongNum LongNum::operator + (const LongNum& other)
{
        LongNum h1 = *this;
	LongNum h2 = other;
	if (long_num[long_num.size() - 1] < 0) {
		if (other.long_num[other.long_num.size() - 1] < 0) {
			h1.long_num[h1.long_num.size() - 1] *= -1;
			h2.long_num[h2.long_num.size() - 1] *= -1;
			h1 = h1 + h2;
			h1.long_num[h1.long_num.size() - 1] *= -1;
			return h1;
		}
		h1.long_num[h1.long_num.size() - 1] *= -1;
		return h2 - h1;
	}
	if (h2.long_num[h2.long_num.size() - 1] < 0) {
		h2.long_num[h2.long_num.size() - 1] *= -1;
		return h1 - h2;
	}

	int n = max((*this).long_num.size(), other.long_num.size());
	string s;
	int k = 0;
	for (int i = 0; i <= n+1; ++i)
		s += '0';
	LongNum *res = new LongNum(s);
	if (h1.long_num.size() < h2.long_num.size()) 
		while (h1.long_num.size() != h2.long_num.size())
			h1.long_num.push_back(0);
	if (h1.long_num.size() > h2.long_num.size())
		while (h2.long_num.size() != h1.long_num.size())
			h2.long_num.push_back(0);

		for (int i = 0; i < n; i++) {
			int t = h1.long_num[i] + h2.long_num[i] + k;
			(*res).long_num[i] = t % 10;
			k = t / 10;
		}
		(*res).long_num[n] += k;
		int i = n + 1;
		while ((*res).long_num[i] == 0 && i != 0) {
			(*res).long_num.pop_back();
			i--;
		}

	return (*res);
}
    
LongNum LongNum::operator-(const LongNum & other)

{
	LongNum h1 = (*this);
	LongNum h2 = other;
        
	if (h2.long_num[h2.long_num.size() - 1] < 0) {
		if (h1.long_num[h1.long_num.size() - 1] > 0) {
			h2.long_num[h2.long_num.size() - 1] *= -1;
			return h1 + h2;
		}
		h2.long_num[h2.long_num.size() - 1] *= -1;
		h1.long_num[h1.long_num.size() - 1] *= -1;
		return h2 - h1;
	}
	if (h1.long_num[h1.long_num.size() - 1] < 0) {
		h1.long_num[h1.long_num.size() - 1] *= -1;
		h1 = h2 + h1;
		h1.long_num[h1.long_num.size() - 1] *= -1;
		return h1;
	}
	bool isPositive = true;
	if (other > (*this)) {
		h2 = (*this);
		h1 = other;
		isPositive = false;
	}

	int n = max((*this).long_num.size(), other.long_num.size());
	string s;
	int k = 0;
	for (int i = 0; i <= n+1; ++i)
		s += '0';
	LongNum *res = new LongNum(s);

	if (h1.long_num.size() < h2.long_num.size())
		while (h1.long_num.size() != h2.long_num.size())
			h1.long_num.push_back(0);
	if (h1.long_num.size() > h2.long_num.size())
		while (h2.long_num.size() != h1.long_num.size())
			h2.long_num.push_back(0);
	for (int i = 0; i < h2.long_num.size(); i++) {
		if (h1.long_num[i] < h2.long_num[i]) {
			h1.long_num[i + 1]--;
			h1.long_num[i] += 10;
		}
		(*res).long_num[i] = h1.long_num[i] - h2.long_num[i];
	}
	int i = n + 1;
	while ((*res).long_num[i] == 0 && i != 0) {
		(*res).long_num.pop_back();
		i--;
	}

	
	if (isPositive == false) (*res).long_num[(*res).long_num.size() - 1] *= -1;
	return (*res);
}


LongNum LongNum::operator*(const LongNum& other)

{
        LongNum h1 = *this;
	LongNum h2 = other;
	
	int m = (*this).long_num.size();
        int n = other.long_num.size();
        
	string s;
	int k = 0, i = 0, j = 0;

	if (long_num[long_num.size() - 1] < 0) {
		if (other.long_num[other.long_num.size() - 1] < 0) {
			h1.long_num[h1.long_num.size() - 1] *= -1;
			h2.long_num[h2.long_num.size() - 1] *= -1;
			return h1*h2;
		}
		h1.long_num[h1.long_num.size() - 1] *= -1;
		h1 = h1*h2;
		h1.long_num[h1.long_num.size() - 1] *= -1;
		return h1;
	}
	if (h2.long_num[h2.long_num.size() - 1] < 0) {
		h2.long_num[h2.long_num.size() - 1] *= -1;
		h1 = h1*h2;
		h1.long_num[h1.long_num.size() - 1] *= -1;
		return h1;
	}
	
	for (int i = 0; i <= m+n+1; ++i)
		s += '0';
	LongNum *result = new LongNum(s);
	
	for (j = 0; j < n; j++) {
		k = 0;
		if (other.long_num[j] == 0) {
			(*result).long_num[j + m] = 0;
			continue;
		}
		for (i = 0; i < m; i++) {
			int t = (*this).long_num[i] * other.long_num[j] + (*result).long_num[i + j] + k;
			(*result).long_num[i + j] = t % 10;
			k = t / 10;
		}
		(*result).long_num[j + m] = k;
	}
	i = m + n + 1;
	while ((*result).long_num[i] == 0 && i != 0) {
		(*result).long_num.pop_back();
		i--;
	}
	return (*result);
}

LongNum LongNum::operator/(const int & x) 
{
	if (x == 0) throw ("Division by zero!");
	int n = (*this).long_num.size();
	string s;
	int k = 0;
        int cur = 0;
        
	for (int i = 0; i <= n; ++i)
		s += '0';
	LongNum *result = new LongNum(s);

	for (int i = n - 1; i >= 0; i--)
	{
		cur = 10 * k + (*this).long_num[i];
		(*result).long_num[i] = cur / x;
		k = cur % x;
	}
	int i = n;
	while ((*result).long_num[i] == 0 && i != 0) {
		(*result).long_num.pop_back();
		i--;
	}
	return (*result);
}


LongNum LongNum::operator / (const LongNum& other)
{
	if (other == LongNum("0")) throw  "Division by 0!";
	LongNum h1 = (*this), h2 = other;

	if (long_num[long_num.size() - 1] < 0) h1 = -(*this);
	if (other.long_num[long_num.size() - 1] < 0) h2 = -other;

	LongNum a = h1;
	LongNum b = h2;
	LongNum res("0");
	LongNum z("1");
	int k = 0;

	while (b <= a)
	{
		b = (b + b);
		z = (z + z);
		++k;
	}
	while (k)
	{
		b = (b / 2);
		z = (z / 2);
		--k;
		while (b <= a)
		{
			a = (a - b);
			res = (res + z);
		}
	}
	if (long_num[long_num.size() - 1] < 0 || other.long_num[other.long_num.size() - 1] < 0) return -res;
	else return res;
}


LongNum  LongNum::operator % (const LongNum& other){
    LongNum h1 = *this, h2 = other, res("0");
    res = h1/h2;
    res = h1 - res*h2;
    return res;
   
}

int LongNum::to_int(){
    int res = 0;
    for(long i = 0; i<(*this).long_num.size(); ++ i)
        res += (*this).long_num[i] * pow(10,i);
    return res;
}

LongNum LongNum::binpow(const LongNum &other)
{
    LongNum h1 = *this, h2 = other;
    
    if(h2 == LongNum("0"))
        return LongNum("1");
    if(h2%LongNum("2") == LongNum("1")){
        h1 = h1.binpow(h2 - LongNum("1")) * h1;
        return h1;
    }
    else{
        LongNum h3 = h1.binpow(h2 / 2);
        return h3*h3;
    }

}

LongNum LongNum::to_2_base()
{
    LongNum h1 = (*this), zero("0"), res, two("2");
    unsigned long i = 0;
    while(!(h1 == zero)){
        res.long_num.resize(i);
        res.long_num.push_back((h1%two).to_int());
        h1 = h1/two;
        ++i;
    } 
    return res;
}


LongNum LongNum::from_2_base(){
    LongNum h1 = *this, res("0"), two("2"), h2;
    for(long i = 0; i <  long_num.size();++i){
        h2 = LongNum(long_num[i]);
        res = res + h2*two.binpow(LongNum(i));
    }
    return res;
}


/*--------------------------------------------Algorythms---------------------------------------------------*/

LongNum LongNum::karatsuba(const LongNum& other) 
{
	int len = max(long_num.size(), other.long_num.size());
	if (len <= naive_len) //Checks if it`s necessary to use Karatsuba multiplication
	{
		return (*this)*(other); 
	};
	vector<int> res(2 * len);
	vector<int> x = long_num; 
	vector<int> y = other.long_num;

	if (long_num.size() < other.long_num.size()) //Adding 0 to make numbers the same size
	{
		do
		{
			x.push_back(0);
		} while (x.size() != other.long_num.size());
		x.resize(other.long_num.size());
	};
	if (other.long_num.size() < long_num.size())
	{
		do
		{
			y.push_back(0);
		} while (y.size() != long_num.size());
		y.resize(long_num.size());
	};

	int k = (len / 2) + (len % 2);
	vector <int> a1 = { x.begin() + k, x.end() }; //First k numbers from x
	vector <int> b1 = { x.begin(), x.begin() + k }; //Second k numbers from x
	vector <int> c1 = { y.begin() + k, y.end() };
	vector <int> d1 = { y.begin(), y.begin() + k };

	LongNum a, b, c, d;
        a = LongNum(a1);
        b = LongNum(b1);
        c = LongNum(c1);
        d = LongNum(d1);
	LongNum kr(res);
	LongNum z0, z1, z2, z3;
	z0 = (a).karatsuba(c);
	z1 = ((a) + (b)).karatsuba((c) + (d));
	z2 = (b).karatsuba((d));
	z3 = z1 - z2 - z0;
	z0.long_num.insert(z0.long_num.begin(), 2 * k, 0); // Add zeroes 
	z3.long_num.insert(z3.long_num.begin(), k, 0);
	kr = (z0)+(z3)+(z2);

	return kr;
}
