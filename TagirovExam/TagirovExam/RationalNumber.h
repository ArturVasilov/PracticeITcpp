#pragma once

/**
Rational number is a fraction with two integers
*/

class RationalNumber
{
private:
	int a;
	int b;
	double number;

public:
	RationalNumber(void);
	RationalNumber(int a);
	RationalNumber(int a, int b);

	double getResult();
	void add(RationalNumber r);

	~RationalNumber(void);
};

