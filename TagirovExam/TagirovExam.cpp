// TagirovExam.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <stack>
#include <iomanip>
#include <vector>
#include <time.h>
#include <fstream>

#include "RationalNumber.h"
#include "ComplexNumber.h"

#include "BeTree.h"

using namespace std;

int factorial1(int n)
{
	int res = 1;
	for (int i = 2; i <= n; i++)
		res *= i;
	return res;
}

int binom1(int n, int k)
{
	return factorial1(n) / factorial1(k) / factorial1(n - k);
}

int* calc1(int n)
{
	int* res = new int[n + 1];
	for (int i = 0; i <= n; i++)
		res[i] = binom1(n, i);
	return res;
}

int* powXPlusA1(int a, int n)
{
	int* x = new int[n + 1];
	//(x + a) ^ n = { a1, a2, ..., a3 }
	int* k = calc1(n);
	for (int i = 0; i <= n; i++)
		x[i] = k[i] * pow(a, n - i);
	delete(k);
	return x;
}

long ackerman(long m, long n)
{
	/*
	if (m < 0 || n < 0) return 0;
	if (m == 0)
		return n + 1;
	else if (n == 0)
		return ackerman(m - 1, 1);
	return ackerman(m - 1, ackerman(m, n - 1));//*/
	//*
	stack<int> s;
	s.push(m);
	while (!s.empty())
	{
		m = s.top();
		s.pop();
		if (n == 0 || m == 0)
			n += m + 1;
		else
		{
			s.push(--m);
			s.push(++m);
			n--;
		}
	}
	return n;//*/
}

void readArrays(int* &a, int* &b)
{
	int n;
	int m;
	ifstream in("input.txt");
	in>>n;
	in>>m;
	a = new int[n];
	for (int i = 0; i < n; i++)
		in>>a[i];
	b = new int[m];
	for (int j = 0; j < m; j++)
		in>>b[j];
	in.close();
}

void readMatrix(int** &a)
{
	int n;
	int m;
	ifstream in("input.txt");
	in>>n;
	in>>m;
	a = new int*[n];
	for (int i = 0; i < n; i++)
	{
		a[i] = new int[m];
		for (int j = 0; j < m; j++)
			in>>a[i][j];
	}
	in.close();
}

void printMatrix(int** &a, int n, int m)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
			cout<<setw(5)<<a[i][j];
		cout<<endl;
	}
}

void printArray(int* &a, int n)
{
	for (int i = 0; i < n; i++)
	{
		cout<<a[i]<<" ";
	}
	cout<<endl;
}

vector<pair<int, int>> findInMatrix(int** a, int n, int m)
{
	int* maxInRows = new int[n];
	for (int i = 0; i < n; i++)
	{
		int max = -10000;
		for (int j = 0; j < m; j++)
		{
			if (a[i][j] > max)
			{
				max = a[i][j];
			}
		}
		maxInRows[i] = max;
	}

	int* minInCols = new int[m];
	for (int i = 0; i < m; i++)
	{
		int min = 10000;
		for (int j = 0; j < n; j++)
		{
			if (a[j][i] < min)
			{
				min = a[j][i];
			}
		}
		minInCols[i] = min;
	}

	int minRow = 10000;
	for (int i = 0; i < n; i++)
		if (minRow > maxInRows[i])
			minRow = maxInRows[i];
	
	int maxCol = -10000;
	for (int i = 0; i < m; i++)
		if (maxCol < minInCols[i])
			maxCol = minInCols[i];

	vector<pair<int, int>> points;
	if (maxCol < minRow)
		return points;
	for (int i = 0; i < n; i++)
	{
		pair<int, int> p;
		for (int j = 0; j < m; j++)
		{
			if (maxInRows[i] == minInCols[j] && maxInRows[i] == maxCol)
			{
				p.first = i;
				p.second = j;
				points.push_back(p);
			}
		}
	}
	return points;
}

int* multiplyArrays(int* a, int n, int* b, int m)
{
	int size = n + m;
	int* r = new int[size];
	for (int i = 0; i < size; i++)
		r[i] = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
			r[i + j] += a[i] * b[j];
	}
	for (int i = 0; i < size - 1; i++)
	{
		r[i + 1] += r[i] / 10;
		r[i] %= 10;
	}
	size -= r[size - 1] == 0 ? 1 : 0;
	int* res = new int[size];
	for (int i = 0; i < size; i++)
		res[i] = r[size - i - 1];
	delete(r);
	return res;
}

int max(int a, int b)
{
	return a < b ? b : a;
}

int kadane(int* &a, int n)
{
	if (n == 0)
		return 0;
	int sum = 0;
	int m = 0;
	for (int i = 0; i < n; i++)
	{
		sum += a[i];
		m = max(sum, m);
		sum = max(sum, 0);
	}
	return m;
}

int kadane(int** &a, int n, int m)
{
	int maxSum = 0;
	for (int i = 0; i < m; i++)
	{
		int* temp = new int[n];
		for (int j = 0; j < n; j++)
			temp[j] = 0;
		for (int j = i; j < m; j++)
		{
			for (int k = 0; k < n; k++)
                temp[k] += a[k][j];
			int sum = kadane(temp, m);
			maxSum = max(maxSum, sum);
		}
	}
	return maxSum;
}

int main()
{
	/*for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 5; j++)
			cout<<ackerman(i, j)<<" ";
		cout<<endl;
	}*/
	//cout<<ackerman(2, 2)<<endl;
	/*srand(time(0));
	int n = 10;
	int m = 12;
	int** a = new int*[n];
	for (int i = 0; i < n; i++)
	{
		a[i] = new int[m];
		for (int j = 0; j < m; j++)
			a[i][j] = rand() % 100 - 50;
	}
	printMatrix(a, n, m);
	vector<pair<int, int>> points = findInMatrix(a, n, m);
	while (!points.empty())
	{
		pair<int, int> point = points.back();
		points.pop_back();
		cout<<"(" + to_string(point.first) + "," + to_string(point.second) + ")"<<endl;
	}*/
	int** a;
	readMatrix(a);
	cout<<kadane(a, 4, 3)<<endl;
	system("pause");
	return 0;
}

