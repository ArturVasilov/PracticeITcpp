#pragma once
#include "DoubleArrays.h"

class Polynoms : DoubleArrays
{
private:
	int *result;

public:
	Polynoms(int firstSize, int secondSize);

	void generateDistinct();

	void printArrays();

	void clearResultArray();

	void multiply();

	void printResultArray();

	void calculate(int resultIndex);

	~Polynoms();
};

