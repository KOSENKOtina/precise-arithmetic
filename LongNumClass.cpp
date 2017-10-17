#include "LongNumClass.h"
#include <iostream>
#include <string>
#include <vector>
#include <cassert> 
#include <math.h> 
#include <algorithm> 

#define naive_len 10
using namespace std;
using std::string;

LongNum::LongNum() {}

LongNum::LongNum(const int& other)
{
	if (other == 0)
	{
		longNumber.push_back(0);
	}
	else
	{
		int x = other;
		while (x > 0)
		{
			longNumber.push_back(x % 10);
			x /= 10;
		}
	}
}

LongNum::LongNum(string s)
{
	while (s.length() != 0)
	{
		longNumber.push_back(s[s.length() - 1] - '0');
		s.erase(s.length() - 1, s.length());
	}

}

LongNum::LongNum(vector <int> newLong)
{
	longNumber = newLong;
}


LongNum::LongNum(const LongNum& other)
{
	operator = (other);
}

/*LongNum::LongNum(const LongNum &&other)
{
	operator = (other);
}*/

vector<int>  LongNum::getLongNumber()
{ 
	return longNumber; 
}

vector<int>  const& LongNum::getLongNumber() const 
{ 
	return longNumber; 
}

const LongNum operator + (const LongNum& longNumber, const LongNum& longNumber1)
{
	if (longNumber.getLongNumber()[longNumber.getLongNumber().size() - 1] < 0 && longNumber1.getLongNumber()[longNumber1.getLongNumber().size() - 1] > 0) return longNumber1 - (-longNumber);
	if (longNumber1.getLongNumber()[longNumber1.getLongNumber().size() - 1] < 0 && longNumber.getLongNumber()[longNumber.getLongNumber().size() - 1] > 0) return longNumber - (-longNumber1);
	if (longNumber.getLongNumber()[longNumber.getLongNumber().size() - 1] < 0 && longNumber1.getLongNumber()[longNumber1.getLongNumber().size() - 1] < 0) return -(longNumber1 + longNumber);
	int length = 0, need = 0;
	vector <int> res;
	longNumber.getLongNumber().size() > longNumber1.getLongNumber().size() ?
		length = longNumber.getLongNumber().size() + 1 : length = longNumber1.getLongNumber().size() + 1;

	for (int i = 0; i < length; i++)
	{
		int tmp = 0;
		bool a = (i >= longNumber.getLongNumber().size());
		bool b = (i >= longNumber1.getLongNumber().size());
		if (  a  && (!b))    tmp = longNumber1.getLongNumber()[i] + need;
		if ((!a) &&   b )    tmp = longNumber.getLongNumber()[i] + need;
		if (  a  &&   b )    tmp = need;
		if ((!a) && (!b))    tmp = longNumber1.getLongNumber()[i] + longNumber.getLongNumber()[i] + need;
		res.push_back(tmp % 10);
		need = 0;
		need += tmp / 10;
	}
	while (res.size() > 1 && res.back() == 0)
		res.pop_back();
	LongNum c(res);
	return c;
}

const LongNum operator * (const LongNum& longNumber, const LongNum& other) {
	int len = max(longNumber.getLongNumber().size(), other.getLongNumber().size());
	int next = 0;
	vector<int> res(len * 2);
	LongNum help = longNumber, help1 = other;

	if (longNumber.getLongNumber()[longNumber.getLongNumber().size() - 1] < 0) help = -longNumber;
	if (other.getLongNumber()[other.getLongNumber().size() - 1] < 0) help1 = -other;

	vector<int> a = help.getLongNumber();
	vector<int> b = help1.getLongNumber();

	if (a.size() < b.size())
	{
		swap(a, b);
	};

	for (int i = 0; i < b.size(); ++i) {
		for (int j = 0; j < a.size(); ++j) {
			int tmp = 0;
			tmp += res[i + j] + b[i] * a[j];
			res[i + j] = tmp % 10;
			res[i + j + 1] += tmp / 10;
		}
	}
	while (res.size() > 1 && res.back() == 0)
		res.pop_back();
	LongNum c(res);
	if ((longNumber.getLongNumber()[longNumber.getLongNumber().size() - 1] < 0) || (other.getLongNumber()[other.getLongNumber().size() - 1] < 0)) return -c;
	else return c;
}


const LongNum operator - (const LongNum& longNumber, const LongNum& longNumber1)
{
	int l0 = longNumber.getLongNumber().size();
	int l1 = longNumber1.getLongNumber().size();
	if (longNumber == LongNum("0")) return -longNumber1;
	if (longNumber1 == LongNum("0")) return longNumber;
	if (longNumber1.getLongNumber()[l1 - 1] < 0 && longNumber.getLongNumber()[l0 - 1] > 0) return longNumber + (-longNumber1);
	if (longNumber1.getLongNumber()[l1 - 1] > 0 && longNumber.getLongNumber()[l0 - 1] < 0) return -((-longNumber) + longNumber1);
	if (longNumber1.getLongNumber()[l1 - 1] < 0 && longNumber.getLongNumber()[l0 - 1] < 0) return longNumber + (-longNumber1);
	int length = 0, minNext = 0;
	vector <int> res;
	longNumber.getLongNumber().size() > longNumber1.getLongNumber().size() ?
		length = longNumber.getLongNumber().size() : length = longNumber1.getLongNumber().size();

	for (int i = 0; i < length; i++)
	{
		int a = 0, b = 0;
		bool c = (i >= longNumber.getLongNumber().size());
		bool d = (i >= longNumber1.getLongNumber().size());
		if (c) { a = 0; }
		else { a = longNumber.getLongNumber()[i]; };
		if (d) { b = 0; }
		else { b = longNumber1.getLongNumber()[i]; };

		int tmp = 0;
		if ((!c) && (!d))
		{
			tmp += a - b - minNext;
			minNext = 0;
			if (tmp < 0 && i != length - 1) {
				tmp += 10;
				minNext += 1;
			};
		};

		if ((!c) && d)
		{
			tmp += a - minNext;
			minNext = 0;
		};
		res.push_back(tmp);
	}
	while (res.size() > 1 && res.back() == 0)
		res.pop_back();
	LongNum c(res);
	return c;
}


const LongNum operator / (const LongNum& longnumber, const LongNum& other)
{
	if (other == LongNum("0"))
		throw;
	LongNum help = longnumber, help1 = other;

	if (longnumber.getLongNumber()[longnumber.getLongNumber().size() - 1] < 0) help = -longnumber;
	if (other.getLongNumber()[other.getLongNumber().size() - 1] < 0) help1 = -other;

	LongNum a = help;
	LongNum b = help1;

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
	if (longnumber.getLongNumber()[longnumber.getLongNumber().size() - 1] < 0 || other.getLongNumber()[other.getLongNumber().size() - 1] < 0) return -res;
	else return res;
}

void LongNum::write() const
{
	for (auto iter = longNumber.end(); iter != longNumber.begin(); )
		cout << *(--iter);
}

LongNum LongNum::operator - () const {
	LongNum nw, old;
	old = *this;
	nw = old;
	nw.longNumber[nw.longNumber.size() - 1] = -longNumber[nw.longNumber.size() - 1];
	return nw;
}

bool LongNum::operator < (const LongNum& other)const
{
	if (this->getLongNumber()[this->getLongNumber().size() - 1] < 0 && other == LongNum("0")) return true;
	int alen = longNumber.size(), blen = other.longNumber.size();
	if (alen != blen) return alen < blen;
	for (int i = alen - 1; i >= 0; --i) {
		if (longNumber[i] != other.longNumber[i]) {
			return longNumber[i] < other.longNumber[i];
		}
	}
	return false;
}

bool LongNum::operator == (const LongNum& other)const
{
	if (longNumber.size() != other.getLongNumber().size()) return false;
	for (int i = 0; i < max(longNumber.size(), other.longNumber.size()); ++i) {
		if (!(longNumber[i] == other.longNumber[i])) return false;
	}
	return true;
}

bool LongNum::operator <= (const LongNum& other)const
{
	return operator==(other) || operator<(other);
}


LongNum& LongNum::operator = (const LongNum &other)
{
	longNumber = other.longNumber;
	return *this;
}



/*--------------------------------------------Algorythms---------------------------------------------------*/

LongNum LongNum::karatsuba(const LongNum& other) const
{
	int len = max(longNumber.size(), other.longNumber.size());
	if (len <= naive_len) //Cheks if it`s necessary to use Karatsuba multiplication
	{
		return longNumber*other; 
	};
	vector<int> res(2 * len);
	vector<int> x = longNumber; 
	vector<int> y = other.longNumber;

	if (longNumber.size() < other.longNumber.size()) //Adding 0 to make numbers the same size
	{
		do
		{
			x.push_back(0);
		} while (x.size() != other.longNumber.size());
		x.resize(other.longNumber.size());
	};
	if (other.longNumber.size() < longNumber.size())
	{
		do
		{
			y.push_back(0);
		} while (y.size() != longNumber.size());
		y.resize(longNumber.size());
	};

	int k = (len / 2) + (len % 2);
	vector <int> a1 = { x.begin() + k,x.end() }; //First k numbers from x
	vector <int> b1 = { x.begin(), x.begin() + k }; //Second k numbers from x
	vector <int> c1 = { y.begin() + k, y.end() };
	vector <int> d1 = { y.begin(), y.begin() + k };

	LongNum a(a1), b(b1), c(c1), d(d1);
	LongNum kr(res);
	LongNum z0, z1, z2, z3;
	z0 = a.karatsuba(c);
	z1 = (a + b).karatsuba(c + d);
	z2 = b.karatsuba(d);
	z3 = z1 - z2 - z0;
	z0.longNumber.insert(z0.longNumber.begin(), 2 * k, 0); // Add zeroes 
	z3.longNumber.insert(z3.longNumber.begin(), k, 0);
	kr = (z0)+(z3)+(z2);
	return kr;
}
