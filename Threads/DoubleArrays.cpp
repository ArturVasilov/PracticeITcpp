#include "stdafx.h"
#include "DoubleArrays.h"

#include <iostream>

using namespace std;

DoubleArrays::DoubleArrays(int firstSize, int secondSize)
{
	this->firstSize = firstSize;
	this->secondSize = secondSize;
	first = new int[firstSize];
	second = new int[secondSize];
}

DoubleArrays::~DoubleArrays()
{
	delete[] first;
	delete[] second;
}

void DoubleArrays::printArray(int *numbers, int length)
{
	cout << "[";
	for (int i = 0; i < length - 1; i++)
	{
		cout << numbers[i] << ", ";
	}
	cout << numbers[length - 1] << "]" << endl;
}
