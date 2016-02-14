// Threads.cpp: главный файл проекта.

#include "stdafx.h"

#include "ThreadPoolExecutor.h"
#include "Arrays.h"

#include <windows.h>
#include <tchar.h>
#include <strsafe.h>

int main(array<System::String ^> ^args)
{
	int first = 3; 
	int second = 4; 
	
	int *firstArray = new int[first];
	int *secondArray = new int[second];
	#pragma region fill first array
	firstArray[0] = 1;
	firstArray[1] = 2;
	firstArray[2] = 3; // 3x^2 + 2x + 1
	#pragma endregion

	#pragma region fill second array
	secondArray[0] = 4;
	secondArray[1] = 3;
	secondArray[2] = 2;
	secondArray[3] = 1; // x^3 + 2x^2 + 3x + 4
	#pragma endregion

	int resultSize = first + second - 1; // (n + 1) + (m + 1) - 1
	Arrays *arrays = new Arrays(firstArray, first, secondArray, second);
	arrays->prepareResultArray();

	ThreadPoolExecutor *executor = new ThreadPoolExecutor(resultSize);
	for (int index = 0; index < resultSize; index++)
	{
		ArrayTask *task = new ArrayTask(arrays, index);
		executor->scheduleTask(task);
	}

	executor->waitForAll();

	arrays->printResultArray();

	delete(executor);
	delete(arrays);

	system("pause");

	return 0;
}