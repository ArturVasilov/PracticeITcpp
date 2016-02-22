#include "stdafx.h"
#include "Polynoms.h"
#include <iostream>
#include <algorithm>

using namespace std;

void printPolynom(int *numbers, int length);

Polynoms::Polynoms(int firstSize, int secondSize) : DoubleArrays(firstSize, secondSize)
{
	result = new int[firstSize + secondSize - 1];
	clearResultArray();
}

void Polynoms::generateDistinct()
{
	for (int i = 0; i < firstSize; i++)
	{
		first[i] = rand() % 10 + 1;
	}

	for (int i = 0; i < secondSize; i++)
	{
		second[i] = rand() % 10 + 1;
	}
}

void Polynoms::printArrays()
{
	cout << "first array = ";
	printArray(first, firstSize);

	cout << "second array = ";
	printArray(second, secondSize);

	cout << "first polynom = ";
	printPolynom(first, firstSize);

	cout << "second polynom = ";
	printPolynom(second, secondSize);
}

void Polynoms::clearResultArray()
{
	int length = firstSize + secondSize - 1;
	for (int i = 0; i < length; i++)
	{
		result[i] = 0;
	}
}

void Polynoms::multiply()
{
	for (int i = 0; i < firstSize; i++)
	{
		for (int j = 0; j < secondSize; j++)
		{
			result[i + j] += first[i] * second[j];
		}
	}
}

void Polynoms::printResultArray() 
{
	int length = firstSize + secondSize - 1;
	cout << "result array = ";
	printArray(result, length);

	cout << "result polynom = ";
	printPolynom(result, length);
}

void Polynoms::calculate(int resultIndex)
{
	int result = 0;
	for (int i = max(0, resultIndex - secondSize + 1), to = min(resultIndex, firstSize - 1); i <= to; i++)
	{
		result += first[i] * second[resultIndex - i];
	}

	this->result[resultIndex] = result;
}

Polynoms::~Polynoms()
{
	delete[] result;
}

void printArray(int *numbers, int length)
{
	cout << "[";
	for (int i = 0; i < length - 1; i++)
	{
		cout << numbers[i] << ", ";
	}
	cout << numbers[length - 1] << "]" << endl;
}

void printPolynom(int *numbers, int length)
{
	for (int i = length - 1; i >= 0; i--)
	{
		if (numbers[i] > 0)
		{
			cout << numbers[i];
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
