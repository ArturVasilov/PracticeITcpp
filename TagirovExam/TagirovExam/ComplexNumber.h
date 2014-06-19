#pragma once

#include <string>

using namespace std;

class ComplexNumber
{
private:
	int a;
	int b;

public:
	ComplexNumber(void);

	ComplexNumber(int a);
	ComplexNumber(int a, int b);

	string toString();

	~ComplexNumber(void);
};

