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

void compareAndSwap(int* first, int* second);

void mergeSort(int* numbers, int size);

void printMergeIndicies(int size);

void printArray(int *numbers, int length);

DWORD WINAPI workerFunction(LPVOID lpParam);

BOOL setConsoleFontSize(int size);

struct MergeData
{
	int* first;
	int* second;
};

int main()
{
	setConsoleFontSize(32);

	int size;
	cout << "Please, enter length of the array" << endl;
	cin >> size;
	srand(time(0));

	int* numbers = new int[size];
	for (int i = 0; i < size; i++)
	{
		numbers[i] = rand() % 100 + 1;
	}

	cout << "Generated array: ";
	printArray(numbers, size);

	cout << "Compared indicies step by step:" << endl;
	printMergeIndicies(size);

	mergeSort(numbers, size);

	cout << "Sorted array: ";
	printArray(numbers, size);

	delete[] numbers;

	return 0;
}

void mergeSort(int* numbers, int size)
{
	HANDLE* hThreadArray = new HANDLE[size / 2];
	MergeData* dataArray = new MergeData[size / 2];

	for (int phase = 1; phase < size; phase *= 2)
	{
		for (int comparatorSize = phase; comparatorSize > 0; comparatorSize /= 2)
		{
			int index = 0;
			for (int startIndexInBlock = comparatorSize % phase; 
				startIndexInBlock + comparatorSize < size; 
				startIndexInBlock += comparatorSize * 2)
			{
				for (int comparatorInBlockIndex = 0; 
					comparatorInBlockIndex < comparatorSize && (startIndexInBlock + comparatorInBlockIndex + comparatorSize) < size; 
					comparatorInBlockIndex++)
				{
					int firstIndexBlock = (startIndexInBlock + comparatorInBlockIndex) / (phase * 2);
					int secondIndexBlock = (startIndexInBlock + comparatorInBlockIndex + comparatorSize) / (phase * 2);
					//compare only items from the same block
					if (firstIndexBlock == secondIndexBlock)
					{
						dataArray[index].first = numbers + startIndexInBlock + comparatorInBlockIndex;
						dataArray[index].second = dataArray[index].first + comparatorSize;
						hThreadArray[index] = CreateThread(0, 0, workerFunction, dataArray + index, 0, 0);
						index++;
					}
				}
			}

			WaitForMultipleObjects(index, hThreadArray, TRUE, INFINITE);
			for (int i = 0; i < index; i++)
			{
				CloseHandle(hThreadArray[i]);
			}
		}
	}

	delete[] hThreadArray;
	delete[] dataArray;
}

void compareAndSwap(int* first, int* second)
{
	if (first[0] > second[0])
	{
		int temp = first[0];
		first[0] = second[0];
		second[0] = temp;
	}
}

DWORD WINAPI workerFunction(LPVOID lpParam)
{
	MergeData* data = (MergeData*)lpParam;
	compareAndSwap(data->first, data->second);
	return 0;
}

void printMergeIndicies(int size)
{
	for (int phase = 1; phase < size; phase *= 2)
	{
		for (int comparatorSize = phase; comparatorSize > 0; comparatorSize /= 2)
		{
			int index = 0;
			for (int startIndexInBlock = comparatorSize % phase;
				startIndexInBlock + comparatorSize < size;
				startIndexInBlock += comparatorSize * 2)
			{
				for (int comparatorInBlockIndex = 0;
					comparatorInBlockIndex < comparatorSize && (startIndexInBlock + comparatorInBlockIndex + comparatorSize) < size;
					comparatorInBlockIndex++)
				{
					int firstIndexBlock = (startIndexInBlock + comparatorInBlockIndex) / (phase * 2);
					int secondIndexBlock = (startIndexInBlock + comparatorInBlockIndex + comparatorSize) / (phase * 2);
					//compare only items from the same block
					if (firstIndexBlock == secondIndexBlock)
					{
						cout << "[" << startIndexInBlock + comparatorInBlockIndex << "-" 
							<< startIndexInBlock + comparatorInBlockIndex + comparatorSize << "]";
					}
				}
			}
			cout << endl;
		}
	}
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