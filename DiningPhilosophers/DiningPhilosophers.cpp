#include "stdafx.h"
#include <algorithm>
#include "time.h"

#include <iostream>

#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <strsafe.h>

#define BUF_SIZE 255

using namespace System;
using namespace std;

BOOL setConsoleFontSize(int size);

DWORD WINAPI PhilosopherFunction(LPVOID lpParam);

struct PhilosopherData
{
	int index;
	int leftIndex;
	int rightIndex;
	int repeat;
};

HANDLE semaphore;
HANDLE* hMutexArray;

int main()
{
	setConsoleFontSize(32);
	cout << "Please, enter philosophers count:" << endl;
	int n;
	cin >> n;

	cout << "Please, enter repeat count:" << endl;
	int m;
	cin >> m;

	srand(time(0));

	hMutexArray = new HANDLE[n];
	for (int i = 0; i < n; i++)
	{
		hMutexArray[i] = CreateMutex(NULL, FALSE, NULL);
	}

	semaphore = CreateSemaphore(NULL, n - 1, n - 1, NULL);        

	HANDLE *hThreadArray = new HANDLE[n];
	PhilosopherData* dataArray = new PhilosopherData[n];
	for (int i = 0; i < n; i++)
	{
		dataArray[i].index = i;
		dataArray[i].leftIndex = i;
		dataArray[i].rightIndex = (i == n - 1) ? 0 : i + 1;
		dataArray[i].repeat = m;

		hThreadArray[i] = CreateThread(NULL,
			0,
			PhilosopherFunction,
			dataArray + i,
			0,
			0);
	}

	WaitForMultipleObjects(n, hThreadArray, TRUE, INFINITE);

	for (int i = 0; i < n; i++)
	{
		CloseHandle(hThreadArray[i]);
	}
	delete[] hThreadArray;
	delete[] dataArray;

	for (int i = 0; i < n; i++)
	{
		CloseHandle(hMutexArray[i]);
	}
	delete[] hMutexArray;

	CloseHandle(semaphore);
	
	system("pause");

    return 0;
}

DWORD WINAPI PhilosopherFunction(LPVOID lpParam)
{
	PhilosopherData* data = (PhilosopherData*)lpParam;
	int index = data->index;
	int leftIndex = data->leftIndex;
	int rightIndex = data->rightIndex;
	int repeat = data->repeat;

	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	TCHAR msgBuf[BUF_SIZE];
	size_t cchStringSize;
	DWORD dwChars;

	for (int i = 0; i < repeat; i++)
	{
		StringCchPrintf(msgBuf, BUF_SIZE, TEXT("Philosopher %d is thinking...\n"), index);
		StringCchLength(msgBuf, BUF_SIZE, &cchStringSize);
		WriteConsole(hStdout, msgBuf, (DWORD)cchStringSize, &dwChars, NULL);

		//thinking
		int seconds = rand() % 5 + 1;
		Sleep(seconds * 1000);

		//waiting for place at the table
		WaitForSingleObject(semaphore, INFINITE);

		//waiting for left stick
		WaitForSingleObject(hMutexArray[leftIndex], INFINITE);
		StringCchPrintf(msgBuf, BUF_SIZE, TEXT("Philosopher %d took left stick\n"), index);
		StringCchLength(msgBuf, BUF_SIZE, &cchStringSize);
		WriteConsole(hStdout, msgBuf, (DWORD)cchStringSize, &dwChars, NULL);

		//waiting for right stick
		WaitForSingleObject(hMutexArray[rightIndex], INFINITE);
		StringCchPrintf(msgBuf, BUF_SIZE, TEXT("Philosopher %d took right stick\n"), index);
		StringCchLength(msgBuf, BUF_SIZE, &cchStringSize);
		WriteConsole(hStdout, msgBuf, (DWORD)cchStringSize, &dwChars, NULL);

		StringCchPrintf(msgBuf, BUF_SIZE, TEXT("Philosopher %d is dining...\n"), index);
		StringCchLength(msgBuf, BUF_SIZE, &cchStringSize);
		WriteConsole(hStdout, msgBuf, (DWORD)cchStringSize, &dwChars, NULL);
		//eating
		seconds = rand() % 3 + 1;
		Sleep(seconds * 1000);

		//put sticks back
		ReleaseMutex(hMutexArray[leftIndex]);
		ReleaseMutex(hMutexArray[rightIndex]);

		//leave the table
		ReleaseSemaphore(semaphore, 1, NULL);
	}
	
	return 0;
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
