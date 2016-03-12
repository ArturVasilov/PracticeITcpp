#include "stdafx.h"
#include "Polynom.h"


Polynom::Polynom(void)
{
	n = 0;
}

Polynom::Polynom(int* a, int n)
{
	this->n = n;
	for (int i = 0; i < n; i++)
		p.addLast(a[i]);
}

Polynom Polynom::operator +(Polynom p1)
{
	int min, max;
	if (n < p1.n)
	{
		min = n;
		max = p1.n;
	}
	else
	{
		min = p1.n;
		max = n;
	}
	int* arr = new int[max];
	for (int i = 0; i < min; i++)
		arr[i]= p.get(i) + p1[i];
	if (p1.n == max)
		for (int i = min + 1; i < max; i++)
			arr[i] = p1[i];
	else
		for (int i = min + 1; i < max; i++)
			arr[i] = p.get(i);
	Polynom pol(arr, max);
	return pol;
}

int Polynom::operator [](int i)
{
	return p.get(i);
}

Polynom Polynom::xPlusA(int a)
{
	Polynom pol;

	return pol;
}

int Polynom::valueAt(int a)
{
	int result = 0;
	for (int i = 0; i < n; i++)
		result += p.get(i) * pow(a, i);
	return result;
}

int Polynom::pow(int a, int n)
{
	int x = a;
	for (int i = 1; i < n; i++)
		x *= a;
	return x;
}

int factorial(int n)
{
	int res = 1;
	for (int i = 2; i < n; i++)
		res *= i;
	return res;
}

int binom(int n, int k)
{
	return factorial(n) / factorial(k) / factorial(n - k);
}

int* calc(int n)
{
	int* res = new int[n + 1];
	for (int i = 0; i <= n; i++)
		res[i] = binom(n, i);
	return res;
}

Polynom Polynom::powXPlusA(int a, int n)
{
	int* x = new int[n + 1];
	//(x + a) ^ n = { a1, a2, ..., a3 }
	int* k = calc(n);
	for (int i = 0; i <= n; i++)
		x[i] = k[i] * pow(a, n - i);
	//delete(k);
	Polynom p(x, n + 1);
	//delete(x);
	return p;
}

string Polynom::toString()
{
	if (n == 0)
		return "";
	string s = to_string(p.get(0)) + " ";
	if (n == 1)
		return s;
	int a = p.get(1);
	s += a == 0 ? "" : a > 0 ? "+ " + to_string(a) + "x " : "- " + to_string(-a) + "x ";
	for (int i = 2; i < n; i++)
	{
		int a = p.get(i);
		s += a == 0 ? "" : a > 0 ? "+ " + to_string(a) : "- " + to_string(-a);
		s += a == 0 ? "" : "x^" +  to_string(i) + " ";
	}
	return s;
}

Polynom::~Polynom(void)
{
}
