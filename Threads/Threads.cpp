#include "stdafx.h"

#include "PolynomsRunnable.h"
#include "MergeRunnable.h"

#include "time.h"

#include <iostream>

using namespace std;

void multiplyPolynoms(int first, int second);

void mergeArrays(int first, int second);

BOOL setConsoleFontSize(int size);

int main()
{
	srand(time(0));

	//setConsoleFontSize(32);

	int first;
	int second;
	
	cout << "Please, enter two numbers, that represents your arrays length" << endl;
	cin >> first;
	cin >> second;

	cout << "Thank you for your response. Please, select program you want to execute:" << endl;
	cout << "1 - create and multiply polynoms" << endl;
	cout << "2 - create and merge arrays" << endl;
	cout << "Any different number - exit" << endl;

	int program;
	cin >> program;

	if (program == 1)
	{
		multiplyPolynoms(first, second);
	} 
	else if (program == 2)
	{
		mergeArrays(first, second);
	}
	else
	{
		return 0;
	}

	system("pause");

	return 0;
}

void multiplyPolynoms(int first, int second)
{
	Polynoms *polynoms = new Polynoms(first, second);
	cout << "Generating arrays..." << endl;
	polynoms->generateDistinct();
	polynoms->printArrays();

	cout << "Calculating sequentially..." << endl;
	polynoms->multiply();
	polynoms->printResultArray();

	cout << "Calculating in parallel..." << endl;
	polynoms->clearResultArray();

	int size = first + second - 1;
	ThreadPoolExecutor *executor = new ThreadPoolExecutor(size);
	for (int i = 0; i < size; i++)
	{
		PolynomsRunnable *runnable = new PolynomsRunnable(polynoms, i);
		executor->scheduleTask((Runnable*) runnable);
	}

	executor->waitForAll();
	
	polynoms->printResultArray();

	delete(executor);
	delete(polynoms);
}

void mergeArrays(int first, int second)
{
	Merge *merge = new Merge(first, second);
	cout << "Generating arrays..." << endl;
	merge->generateAllDistinctSorted();
	merge->printArrays();

	cout << "Merging sequentially..." << endl;
	merge->merge();
	merge->printResultArray();

	cout << "Parallel binary merging..." << endl;
	merge->clearResultArray();
	
	ThreadPoolExecutor *executor = new ThreadPoolExecutor(first + second);
	for (int i = 0; i < first; i++)
	{
		MergeRunnable *runnable = new MergeRunnable(merge, 0, i);
		executor->scheduleTask((Runnable*)runnable);
	}
	for (int j = 0; j < second; j++)
	{
		MergeRunnable *runnable = new MergeRunnable(merge, 1, j);
		executor->scheduleTask((Runnable*)runnable);
	}

	executor->waitForAll();

	merge->printResultArray();

	delete(executor);
	delete(merge);
}

BOOL setConsoleFontSize(int size) {
	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_FONT_INFOEX info{ sizeof(CONSOLE_FONT_INFOEX) };
	if (!GetCurrentConsoleFontEx(output, false, &info))
		return false;
	info.dwFontSize.Y = size;
	info.dwFontSize.X = (int) (size / 1.5);
	return SetCurrentConsoleFontEx(output, false, &info);
}