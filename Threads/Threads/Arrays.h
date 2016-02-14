#include <windows.h>

#pragma once
class Arrays
{
private:
	int firstSize;
	int secondSize;

	int *first;
	int *second;
	int *result;

public:
	Arrays(int *firstArray, int firstSize, int *secondArray, int secondSize);

	void prepareResultArray();

	void printResultArray();

	void calculate(int resultIndex);

	~Arrays();
};

