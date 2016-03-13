#include "stdafx.h"
#include <iostream>
#include <math.h>
#include <algorithm>
#include "time.h"

#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <strsafe.h>
#include "atlstr.h"

using namespace std;

using namespace System;

void printArray(int *numbers, int length);

DWORD WINAPI workerFunction(LPVOID lpParam);

BOOL setConsoleFontSize(int size);

struct ArraySum
{
	int* numbers;
	int firstIndex;
	int secondIndex;
};

int main()
{
	setConsoleFontSize(32);

	int n;
	cout << "Please, enter length of the array" << endl;
	cin >> n;
	srand(time(0));

	int* numbers = new int[n];
	for (int i = 0; i < n; i++)
	{
		numbers[i] = rand() % 100 + 1;
	}
	cout << "Generated array: ";
	printArray(numbers, n);

	int sum = 0;
	for (int i = 0; i < n; i++)
	{
		sum += numbers[i];
	}
	cout << "Sequentially calculated sum s=" << sum << endl;

	int end = n;
	while (end > 1)
	{
		int threadsCount = end / 2;
		HANDLE *hThreadArray = new HANDLE[threadsCount];
		for (int i = 0; i < threadsCount; i++)
		{
			ArraySum* sum = new ArraySum();
			sum->numbers = numbers;
			sum->firstIndex = i;
			sum->secondIndex = threadsCount + i + (end % 2);

			hThreadArray[i] = CreateThread(NULL, 
				0,
				workerFunction,
				sum,
				0,
				0);
		}

		WaitForMultipleObjects(threadsCount, hThreadArray, TRUE, INFINITE);
		for (int i = 0; i < threadsCount; i++)
		{
			CloseHandle(hThreadArray[i]);
		}
		delete[] hThreadArray;

		printArray(numbers, end);
		end = threadsCount + (end % 2);
	}

	cout << "Parallel calculated sum s=" << numbers[0] << endl;

	delete[] numbers;
	
	system("pause");
    return 0;
}

DWORD WINAPI workerFunction(LPVOID lpParam)
{
	ArraySum* sum = (ArraySum*)lpParam;
	sum->numbers[sum->firstIndex] += sum->numbers[sum->secondIndex];
	return 0;
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

BOOL setConsoleFontSize(int size) {
	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_FONT_INFOEX info{ sizeof(CONSOLE_FONT_INFOEX) };
	if (!GetCurrentConsoleFontEx(output, false, &info))
		return false;
	info.dwFontSize.Y = size;
	info.dwFontSize.X = (int)(size / 1.5);
	return SetCurrentConsoleFontEx(output, false, &info);
}