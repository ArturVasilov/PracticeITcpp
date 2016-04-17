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
	int firstSize;
	int secondSize;
};

struct ThreadMergeData
{
	int* firstNumbers;
	int firstSize;

	int* secondNumbers;
	int secondSize;
};

void bucketSort(int* numbers, int size);

DWORD WINAPI mergeSortThreadFunction(LPVOID lpParam);

DWORD WINAPI mergeThreadFunction(LPVOID lpParam);

void iteratedMergeSort(int* numbers, int size);

int processorsCount();

void printArray(int* numbers, int length);

BOOL setConsoleFontSize(int size);

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

	bucketSort(numbers, size);
	cout << "Sorted array: ";
	printArray(numbers, size);

	delete[] numbers;

	system("pause");
	return 0;
}

void bucketSort(int* numbers, int size)
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

	int index = 0;
	for (index = 0; index < blocks / 2; index++)
	{
		mergeSortDataArray[index].numbers = numbers + index * blockSize * 2;
		mergeSortDataArray[index].firstSize = blockSize;
		mergeSortDataArray[index].secondSize = (index == p - 1 && blocks % 2 == 0) ? lastBlockSize : blockSize;
		hThreadArray[index] = CreateThread(0, 0, mergeSortThreadFunction, mergeSortDataArray + index, 0, 0);
	}
	if (blocks % 2 == 1)
	{
		mergeSortDataArray[index].numbers = numbers + index * blockSize * 2;
		mergeSortDataArray[index].firstSize = lastBlockSize;
		mergeSortDataArray[index].secondSize = 0;
		hThreadArray[index] = CreateThread(0, 0, mergeSortThreadFunction, mergeSortDataArray + index, 0, 0);
		index++;
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
			for (int startIndexInBlock = comparatorSize % phase;
				startIndexInBlock + comparatorSize < blocks;
				startIndexInBlock += comparatorSize * 2)
			{
				for (int comparatorInBlockIndex = 0;
					comparatorInBlockIndex < comparatorSize && (startIndexInBlock + comparatorInBlockIndex + comparatorSize) < blocks;
					comparatorInBlockIndex++)
				{
					int firstIndexBlock = (startIndexInBlock + comparatorInBlockIndex) / (phase * 2);
					int secondIndexBlock = (startIndexInBlock + comparatorInBlockIndex + comparatorSize) / (phase * 2);
					//compare only items from the same block
					if (firstIndexBlock == secondIndexBlock)
					{
						mergeDataArray[index].firstNumbers = numbers + (startIndexInBlock + comparatorInBlockIndex) * blockSize;
						mergeDataArray[index].firstSize = blockSize;
						mergeDataArray[index].secondNumbers = mergeDataArray[index].firstNumbers + comparatorSize * blockSize;
						if (lastBlockSize != 0 && ((startIndexInBlock + comparatorInBlockIndex + comparatorSize + 1) * blockSize) > size)
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
			}

			WaitForMultipleObjects(index, hThreadArray, TRUE, INFINITE);
			for (int i = 0; i < index; i++)
			{
				CloseHandle(hThreadArray[i]);
			}
		}
	}

	delete[] hThreadArray;
}

DWORD WINAPI mergeSortThreadFunction(LPVOID lpParam)
{
	ThreadMergeSortData* data = (ThreadMergeSortData*)lpParam;
	iteratedMergeSort(data->numbers, data->firstSize);
	iteratedMergeSort(data->numbers + data->firstSize, data->secondSize);
	return 0;
}

DWORD WINAPI mergeThreadFunction(LPVOID lpParam)
{
	ThreadMergeData* data = (ThreadMergeData*)lpParam;
	int* firstNumbers = data->firstNumbers;
	int firstSize = data->firstSize;

	int* secondNumbers = data->secondNumbers;
	int secondSize = data->secondSize;

	int size = firstSize + secondSize;
	int* buffer = new int[size];

	for (int i = 0, j = 0, k = 0; k < size; k++)
	{
		if ((i >= firstSize && j < secondSize) || (j < secondSize && firstNumbers[i] > secondNumbers[j]))
		{
			buffer[k] = secondNumbers[j];
			j++;
		}
		else if ((i < firstSize && j >= secondSize) || (i < firstSize && firstNumbers[i] <= secondNumbers[j]))
		{
			buffer[k] = firstNumbers[i];
			i++;
		}
	}

	for (int i = 0; i < firstSize; i++)
	{
		firstNumbers[i] = buffer[i];
	}
	for (int i = 0; i < secondSize; i++)
	{
		secondNumbers[i] = buffer[firstSize + i];
	}

	return 0;
}

void iteratedMergeSort(int* numbers, int n)
{
	int* buffer = new int[n];

	for (int sortedSize = 1; sortedSize < n; sortedSize *= 2)
	{
		for (int start = 0; start < n; start += sortedSize * 2)
		{
			int middle = start + sortedSize - 1;
			int end = middle + sortedSize;
			end = end >= n ? (n - 1) : end;

			for (int i = start; i <= end; i++)
			{
				buffer[i] = numbers[i];
			}

			for (int i = start, j = middle + 1, k = start; k <= end; k++)
			{
				if ((i > middle && j <= end) || (j <= end && buffer[i] > buffer[j]))
				{
					numbers[k] = buffer[j];
					j++;
				}
				else if ((i <= middle && j > end) || (i <= middle && buffer[i] <= buffer[j]))
				{
					numbers[k] = buffer[i];
					i++;
				}
			}
		}
	}

	delete[] buffer;
}

int processorsCount()
{
	//8 for my machine
	SYSTEM_INFO sysinfo;
	GetSystemInfo(&sysinfo);
	return sysinfo.dwNumberOfProcessors;
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

BOOL setConsoleFontSize(int size) {
	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_FONT_INFOEX info{ sizeof(CONSOLE_FONT_INFOEX) };
	if (!GetCurrentConsoleFontEx(output, false, &info))
		return false;
	info.dwFontSize.Y = size;
	info.dwFontSize.X = (int)(size / 1.5);
	return SetCurrentConsoleFontEx(output, false, &info);
}                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          