#include "stdafx.h"
#include "Arrays.h"
#include <iostream>

using namespace std;

Arrays::Arrays(int *firstArray, int firstSize, int *secondArray, int secondSize)
{
	this->firstSize = firstSize;
	this->secondSize = secondSize;

	first = new int[firstSize];
	second = new int[secondSize];
	for (int i = 0; i < firstSize; i++)
	{
		first[i] = firstArray[i];
	}

	for (int i = 0; i < secondSize; i++)
	{
		second[i] = secondArray[i];
	}
}

void Arrays::prepareResultArray()
{
	int length = firstSize + secondSize - 1; //(n + 1) + (m + 1) - 1 = n + m + 1
	result = new int[length];

	for (int i = 0; i < length; i++)
	{
		result[i] = 0;
	}
}

void Arrays::printResultArray()
{
	for (int i = firstSize + secondSize - 1; i >= 0; i--)
	{
		if (result[i] > 0)
		{
			cout << result[i];
			if (i == 1)
			{
				cout << "x + ";
			} 
			else if (i > 0)
			{
				cout << "x^" << i << " + ";
			}
		}
	}
	cout << endl;
}

void Arrays::calculate(int resultIndex)
{
	int result = 0;
	for (int i = max(0, resultIndex - secondSize + 1), to = min(resultIndex, firstSize - 1); i <= to; i++)
	{
		result += first[i] * second[resultIndex - i];
	}

	this->result[resultIndex] = result;
}

Arrays::~Arrays()
{
	delete[] first;
	delete[] second;
	if (result) 
	{
		delete[] result;
	}
}

int arraySize(int values[])
{
	return (sizeof(values) / sizeof(*values));
}