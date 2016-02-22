#pragma once
class DoubleArrays
{
protected:
	int firstSize;
	int secondSize;

	int *first;
	int *second;

	void printArray(int *numbers, int length);

public:
	DoubleArrays(int firstSize, int secondSize);

	~DoubleArrays();
};

