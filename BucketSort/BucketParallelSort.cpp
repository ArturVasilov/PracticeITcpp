// BucketParallelSort.cpp: главный файл проекта.

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

using namespace System;
using namespace std;

struct ThreadMergeSortData
{
	int* numbers;
	int* buffer;
	int firstSize;
	int secondSize;
};

struct ThreadMergeData
{
	int* firstNumbers;
	int* firstBuffer;
	int firstSize;

	int* secondNumbers;
	int* secondBuffer;
	int secondSize;
};

void blockSort(int* numbers, int size);

DWORD WINAPI mergeSortThreadFunction(LPVOID lpParam);

DWORD WINAPI mergeThreadFunction(LPVOID lpParam);

void iteratedMergeSort(int* numbers, int* buffer, int size);

int processorsCount();

void printArray(int* numbers, int length);

BOOL setConsoleFontSize(int size);

int main()
{
	//setConsoleFontSize(32);

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

	blockSort(numbers, size);
	cout << "Sorted array: ";
	printArray(numbers, size);

	delete[] numbers;

	return 0;
}

void blockSort(int* numbers, int size)
{
	int p = processorsCount();
	int blocks = p * 2;
	int r = size % blocks;
	int blockSize = size / blocks;
	int lastBlockSize = blockSize;
	if (r != 0)
	{
		int q = size / blocks;
		int s = size / (q + 1);
		int t = size % (q + 1);
		blocks = t == 0 ? s : (s + 1);
		blockSize = q + 1;
		lastBlockSize = t == 0 ? blockSize : t;
	}

	HANDLE* hThreadArray = new HANDLE[p];
	ThreadMergeSortData* mergeSortDataArray = new ThreadMergeSortData[p];

	int* buffer = new int[size];
	int index = 0;
	for (index = 0; index < blocks / 2 + blocks % 2; index++)
	{
		mergeSortDataArray[index].numbers = numbers + index * blockSize * 2;
		if (blocks % 2 == 1 && index == blocks / 2)
		{
			mergeSortDataArray[index].firstSize = lastBlockSize;
			mergeSortDataArray[index].secondSize = 0;
		} 
		else
		{
			mergeSortDataArray[index].firstSize = blockSize;
			mergeSortDataArray[index].secondSize = (index == blocks / 2 + blocks % 2 - 1) ? lastBlockSize : blockSize;
		}
		mergeSortDataArray[index].buffer = buffer + index * blockSize * 2;
		hThreadArray[index] = CreateThread(0, 0, mergeSortThreadFunction, mergeSortDataArray + index, 0, 0);
	}

	WaitForMultipleObjects(index, hThreadArray, TRUE, INFINITE);
	for (int i = 0; i < index; i++)
	{
		CloseHandle(hThreadArray[i]);
	}
	delete[] mergeSortDataArray;

	ThreadMergeData* mergeDataArray = new ThreadMergeData[p];
	for (int phase = 1; phase < blocks; phase *= 2)
	{
		for (int comparatorSize = phase; comparatorSize > 0; comparatorSize /= 2)
		{
			int index = 0;
			//sib ~ start index in each cascade
			for (int sib = comparatorSize % phase; sib + comparatorSize < blocks; sib += comparatorSize * 2)
			{
				if (sib / (phase * 2) != (sib + comparatorSize) / (phase * 2))
				{
					//comparators are in different cascades
					continue;
				}
				//cbi ~ index for compartor in cascade
				for (int cbi = 0; cbi < comparatorSize && (sib + cbi + comparatorSize) < blocks; cbi++)
				{
					mergeDataArray[index].firstNumbers = numbers + (sib + cbi) * blockSize;
					mergeDataArray[index].firstBuffer = buffer + (sib + cbi) * blockSize;
					mergeDataArray[index].firstSize = blockSize;
					mergeDataArray[index].secondNumbers = mergeDataArray[index].firstNumbers + comparatorSize * blockSize;
					mergeDataArray[index].secondBuffer = mergeDataArray[index].firstBuffer + comparatorSize * blockSize;
					if (lastBlockSize != 0 && ((sib + cbi + comparatorSize + 1) * blockSize) > size)
					{
						mergeDataArray[index].secondSize = lastBlockSize;
					}
					else
					{
						mergeDataArray[index].secondSize = blockSize;
					}
					hThreadArray[index] = CreateThread(0, 0, mergeThreadFunction, mergeDataArray + index, 0, 0);
					index++;
				}
			}

			WaitForMultipleObjects(index, hThreadArray, TRUE, INFINITE);
			for (int i = 0; i < index; i++)
			{
				CloseHandle(hThreadArray[i]);
			}

			/* 
			//This doesn't work, but looks pretty correct.
			//I don't think that it should. 
			//Since not all items are changing in each step - may be we're loosing something
			int* temp = numbers;
			numbers = buffer;
			buffer = temp;
			//*/
		}
	}

	delete[] buffer;
	delete[] mergeDataArray;
	delete[] hThreadArray;
}

DWORD WINAPI mergeSortThreadFunction(LPVOID lpParam)
{
	ThreadMergeSortData* data = (ThreadMergeSortData*)lpParam;
	iteratedMergeSort(data->numbers, data->buffer, data->firstSize);
	iteratedMergeSort(data->numbers + data->firstSize, data->buffer + data->firstSize, data->secondSize);
	return 0;
}

DWORD WINAPI mergeThreadFunction(LPVOID lpParam)
{
	ThreadMergeData* data = (ThreadMergeData*)lpParam;
	int* firstNumbers = data->firstNumbers;
	int* firstBuffer = data->firstBuffer;
	int firstSize = data->firstSize;

	int* secondNumbers = data->secondNumbers;
	int* secondBuffer = data->secondBuffer;
	int secondSize = data->secondSize;


	//buffer for smallest values
	for (int i = 0, j = 0, k = 0; k < firstSize; k++)
	{
		if (j >= secondSize || firstNumbers[i] < secondNumbers[j])
		{
			firstBuffer[k] = firstNumbers[i];
			i++;
		}
		else
		{
			firstBuffer[k] = secondNumbers[j];
			j++;
		}
	}

	//buffer for largest values
	for (int i = firstSize - 1, j = secondSize - 1, k = secondSize - 1; k >= 0; k--)
	{
		if (i < 0 || secondNumbers[j] > firstNumbers[i])
		{
			secondBuffer[k] = secondNumbers[j];
			j--;
		}
		else
		{
			secondBuffer[k] = firstNumbers[i];
			i--;
		}
	}

	for (int i = 0; i < firstSize; i++)
	{
		firstNumbers[i] = firstBuffer[i];
	}
	for (int i = 0; i < secondSize; i++)
	{
		secondNumbers[i] = secondBuffer[i];
	}

	return 0;
}

void iteratedMergeSort(int* numbers, int* buffer, int n)
{
	int* first = numbers;
	int* second = buffer;

	for (int sortedSize = 1; sortedSize < n; sortedSize *= 2)
	{
		for (int start = 0; start < n; start += sortedSize * 2)
		{
			int middle = start + sortedSize - 1;
			int end = middle + sortedSize;
			end = end >= n ? (n - 1) : end;

			for (int i = start, j = middle + 1, k = start; k <= end; k++)
			{
				if ((i > middle && j <= end) || (j <= end && first[i] > first[j]))
				{
					second[k] = first[j];
					j++;
				}
				else if ((i <= middle && j > end) || (i <= middle && first[i] <= first[j]))
				{
					second[k] = first[i];
					i++;
				}
			}
		}

		int* temp = first;
		first = second;
		second = temp;
	}

	if (numbers != first)
	{
		for (int i = 0; i < n; i++)
		{
			numbers[i] = first[i];
		}
	}

}

void printArray(int* numbers, int length)
{
	cout << "[";
	for (int i = 0; i < length - 1; i++)
	{
		cout << numbers[i] << ", ";
	}
	cout << numbers[length - 1] << "]" << endl;
}

int processorsCount()
{
	//8 for my machine
	SYSTEM_INFO sysinfo;
	GetSystemInfo(&sysinfo);
	return sysinfo.dwNumberOfProcessors;
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