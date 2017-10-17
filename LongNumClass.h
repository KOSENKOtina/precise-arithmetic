
#ifndef LONGNUMCLASS_H
#define LONGNUMCLASS_H

#include <string>
#include <vector>
#include <complex>

using namespace std;

class LongNum
{
private:
	vector <int> longNumber;
public:
	LongNum();
	LongNum(const int& other);
	LongNum(string s);
	LongNum(vector <int> newLong);
	LongNum(const LongNum& other);
	//LongNum(const LongNum &&other);
	
	vector<int> getLongNumber();
	vector<int> const& getLongNumber() const;
	
	void write() const;

	bool operator < (const LongNum& other)const;
	bool operator == (const LongNum& other)const;
	bool operator <= (const LongNum& other)const;

	LongNum& operator = (const LongNum &other);
	LongNum  operator - () const;

	friend const LongNum operator / (const LongNum& longnumber, const LongNum& other);
	friend const LongNum operator * (const LongNum& longNumber, const LongNum& other);
	friend const LongNum operator + (const LongNum& longNumber, const LongNum& longNumber1);
	friend const LongNum operator - (const LongNum& longNumber, const LongNum& longNumber1);

	LongNum karatsuba(const LongNum& other) const;
};

#endif /* LONGNUMCLASS_H */

