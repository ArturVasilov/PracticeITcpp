#include "stdafx.h"
#include "Merge.h"
#include <iostream>
#include <algorithm>

using namespace std;

int findIndexInSortedArray(int *values, int value, int start, int end);

Merge::Merge(int firstSize, int secondSize) : DoubleArrays(firstSize, secondSize)
{
	result = new int[firstSize + secondSize];
	clearResultArray();
}

void Merge::generateAllDistinctSorted()
{
	int value = 0;
	int i = 0;
	int j = 0;
	while (i < firstSize && j < secondSize)
	{
		int arrayIndex = rand() % 2;
		value += rand() % 10 + 1;
		if (arrayIndex == 0)
		{
			first[i] = value;
			i++;
		}
		else
		{
			second[j] = value;
			j++;
		}
	}

	while (i < firstSize)
	{
		value += rand() % 10 + 1;
		first[i] = value;
		i++;
	}

	while (j < secondSize)
	{
		value += rand() % 10 + 1;
		second[j] = value;
		j++;
	}
}

void Merge::printArrays()
{
	cout << "first array = ";
	printArray(first, firstSize);

	cout << "second array = ";
	printArray(second, secondSize);
}

void Merge::clearResultArray()
{
	int length = firstSize + secondSize;
	for (int i = 0; i < length; i++)
	{
		result[i] = 0;
	}
}

void Merge::merge()
{
	clearResultArray();

	int i = 0;
	int j = 0;

	while (i < firstSize && j < secondSize)
	{
		if (first[i] < second[j])
		{
			result[i + j] = first[i];
			i++;
		}
		else
		{
			result[i + j] = second[j];
			j++;
		}
	}

	while (i < firstSize)
	{
		result[i + j] = first[i];
		i++;
	}

	while (j < secondSize)
	{
		result[i + j] = second[j];
		j++;
	}
}

void Merge::printResultArray()
{
	printArray(result, firstSize + secondSize);
}

void Merge::findPlace(int arrayIndex, int index)
{
	if (arrayIndex == 0)
	{
		int resultIndex = index + findIndexInSortedArray(second, first[index], 0, secondSize);
		result[resultIndex] = first[index];
	}
	else
	{
		int resultIndex = index + findIndexInSortedArray(first, second[index], 0, firstSize);
		result[resultIndex] = second[index];
	}
}

Merge::~Merge()
{
	delete[] result;
}

int findIndexInSortedArray(int *values, int value, int start, int end)
{
	if (start == end)
	{
		return start;
	}
	int middle = (start + end) / 2;
	if (values[middle] > value)
	{
		return findIndexInSortedArray(values, value, start, middle);
	}
	else
	{
		return findIndexInSortedArray(values, value, middle + 1, end);
	}
}