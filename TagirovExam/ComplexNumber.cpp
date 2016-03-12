#include "stdafx.h"
#include "ComplexNumber.h"


ComplexNumber::ComplexNumber(void)
{
	a = 0;
	b = 0;
}

ComplexNumber::ComplexNumber(int a)
{
	this->a = a;
	b = 0;
}

ComplexNumber::ComplexNumber(int a, int b)
{
	this->a = a;
	this->b = b;
}

int module(int a)
{
	return a < 0 ? -a : a;
}

string ComplexNumber::toString()
{
	string s = to_string(a);
	if (b == 0)
		return s;
	s += b < 0 ? " - i" : " + i";
	return s + to_string(module(b));
}

ComplexNumber::~ComplexNumber(void)
{
}
