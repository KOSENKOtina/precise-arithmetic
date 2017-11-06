/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ClassLongNum.h
 * Author: valentina
 *
 * Created on October 21, 2017, 4:52 PM
 */

#ifndef CLASSLONGNUM_H
#define CLASSLONGNUM_H

#include <vector>
#include <iostream>
#include <string>
#include <cmath>


using std::string;
using namespace std;

class LongNum {
private:
	vector <int> long_num;
public:
	LongNum();
	LongNum(const int& other);
	LongNum(string s);
	LongNum(vector <int> newLong);
	LongNum(const LongNum & other);
	
	vector<int> getLongNumber();
	//vector<int> const& getLongNumber() const;
	
	void write() const;
        LongNum to_2_base();
        LongNum from_2_base();
        int to_int();
        LongNum binpow(const LongNum& other);

	bool operator < (const LongNum& other)const;
        bool operator >(const LongNum& other)const;
	bool operator == (const LongNum& other)const;
	bool operator <= (const LongNum& other)const;

	LongNum& operator = (const LongNum &other);
	LongNum  operator - () const;

	LongNum operator + (const LongNum& other);
        LongNum operator-(const LongNum & other);
        LongNum operator*(const LongNum& other);
        LongNum operator/(const int & x);
        LongNum operator / (const LongNum& other);
        LongNum operator % (const LongNum& other);
//        int operator % (const LongNum& other);
        
        LongNum karatsuba(const LongNum& other);
        
};



#endif /* CLASSLONGNUM_H */

