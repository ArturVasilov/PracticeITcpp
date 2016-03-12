#pragma once
#include "DoubleArrays.h"

class Merge : DoubleArrays
{
private:
	int *result;

public:
	Merge(int firstSize, int secondSize);

	void generateAllDistinctSorted();

	void printArrays();

	void clearResultArray();

	void merge();

	void printResultArray();

	void findPlace(int arrayIndex, int index);

	~Merge();

};

