#include "stdafx.h"
#include "RationalNumber.h"


RationalNumber::RationalNumber(void)
{
	this->a = 0;
	this->b = 0;
	number = 0;
}

RationalNumber::RationalNumber(int a)
{
	this->a = a;
	this->b = a;
	number = 1;
}

RationalNumber::RationalNumber(int a, int b)
{
	this->a = a;
	this->b = b;
	number = a / (double)b;
}

double RationalNumber::getResult() 
{
	return number;
}

int mod(int a)
{
	return a < 0 ? -a : a;
}

int gcd(int a, int b)
{
	if (a < 0 || b < 0)
		return -gcd(mod(a), mod(b));
	if (a < b) 
		return gcd(b, a);
	if (a % b == 0)
		return b;
	if (a == 1 || b == 1)
		return 1;
	return (b, a % b);
}

int lcm(int a, int b)
{
	// gcd * lcm = a * b
	//lcm = a * b / gcd
	return a / gcd(a, b) * b;
}

void RationalNumber::add(RationalNumber r)
{
	int x = lcm(r.b, b);
	if (x == 0)
		return;
	a = a * x / b + r.a * x / r.b;
	b = x;
	number = a / b;
}

RationalNumber::~RationalNumber(void)
{
}
