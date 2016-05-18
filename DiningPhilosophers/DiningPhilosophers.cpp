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

int n;
int repeat;

HANDLE semaphore;
HANDLE* hMutexArray;

int main()
{
	setConsoleFontSize(32);
	cout << "Please, enter philosophers count:" << endl;
	cin >> n;

	cout << "Please, enter repeat count:" << endl;
	cin >> repeat;

	srand(time(0));

	hMutexArray = new HANDLE[n];
	for (int i = 0; i < n; i++)
	{
		hMutexArray[i] = CreateMutex(NULL, FALSE, NULL);
	}

	semaphore = CreateSemaphore(NULL, n - 1, n - 1, NULL);        

	HANDLE *hThreadArray = new HANDLE[n];
	for (int i = 0; i < n; i++)
	{
		hThreadArray[i] = CreateThread(NULL,
			0,
			PhilosopherFunction,
			(LPVOID)i,
			0,
			0);
	}

	WaitForMultipleObjects(n, hThreadArray, TRUE, INFINITE);

	for (int i = 0; i < n; i++)
	{
		CloseHandle(hThreadArray[i]);
	}
	delete[] hThreadArray;

	for (int i = 0; i < n; i++)
	{
		CloseHandle(hMutexArray[i]);
	}
	delete[] hMutexArray;

	CloseHandle(semaphore);

    return 0;
}

DWORD WINAPI PhilosopherFunction(LPVOID lpParam)
{
	int index = (int) lpParam;
	int leftIndex = index;
	int rightIndex = index == n - 1 ? 0 : n - 1;

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
