#pragma once

#include "LinkedList.h"

#include <string>

using namespace std;

class Polynom
{
private:
	LinkedList p;

	int n;

public:
	Polynom(void);

	Polynom(int* a, int n);

	Polynom operator +(Polynom p1);
	int operator [](int i);

	Polynom xPlusA(int a);

	int valueAt(int a);

	int pow(int a, int n);

	Polynom powXPlusA(int a, int n);

	string toString();

	~Polynom(void);
};

