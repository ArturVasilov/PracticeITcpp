#include "stdafx.h"
#include <algorithm>
#include "time.h"
#include <queue>

#include <iostream>

#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <strsafe.h>

#define BUF_SIZE 255
#define ERROR -1
#define BARBERS_WAITING_TIME_BEFORE_GO_HOME 10000

using namespace System;
using namespace std;

//Standard queue where push and pop operations are syncronized (atomic)
class SyncronizedIntQueue
{
private:
	queue<int> numbers;
	HANDLE mutex;

public:
	SyncronizedIntQueue()
	{
		mutex = CreateMutex(NULL, FALSE, NULL);
	}

	int get()
	{
		DWORD dwResult = WaitForSingleObject(mutex, INFINITE);
		int result = ERROR;
		if (!numbers.empty())
		{
			result = numbers.front();
			numbers.pop();
		}
		ReleaseMutex(mutex);
		return result;
	}

	void put(int number)
	{
		WaitForSingleObject(mutex, INFINITE);
		numbers.push(number);
		ReleaseMutex(mutex);
	}

	~SyncronizedIntQueue()
	{
		//http://stackoverflow.com/questions/2204608/does-c-call-destructors-for-global-and-class-static-variables
		//in short, it will be called after main function finishes
		CloseHandle(mutex);
	}
};

BOOL setConsoleFontSize(int size);

DWORD WINAPI BarberFunction(LPVOID lpParam);

DWORD WINAPI ClientFunction(LPVOID lpParam);

int repeat;

SyncronizedIntQueue waitingQueue; //table in waiting room (for clients in seats)
SyncronizedIntQueue workingQueue; //table in barbes room

HANDLE barbersSemaphore; //semaphore for free barbers 
HANDLE readyClientsSemaphore; //semaphore for clients which are waiting for barber

//pair of semaphore for each barber place (for messaging)
HANDLE* clientsSeatsSemaphores; 
HANDLE* barbersSeatsSemaphores;

int main()
{
	setlocale(LC_ALL, "Russian");
	setConsoleFontSize(32);

	int clients;
	cout << "Please, enter clients count:" << endl;
	cin >> clients;

	cout << "Please, enter repeat count:" << endl;
	cin >> repeat;

	int barbers;
	cout << "Please, enter barbers count:" << endl;
	cin >> barbers;

	int seats;
	cout << "Please, enter seats count:" << endl;
	cin >> seats;

	int capacity = barbers + seats;

	for (int i = 0; i < capacity; i++)
	{
		waitingQueue.put(i);
	}

	barbersSemaphore = CreateSemaphore(NULL, barbers, barbers, NULL); 
	readyClientsSemaphore = CreateSemaphore(NULL, 0, barbers, NULL); 

	clientsSeatsSemaphores = new HANDLE[capacity]; //since there are capacity of numbers
	barbersSeatsSemaphores = new HANDLE[capacity];
	for (int i = 0; i < capacity; i++)
	{
		clientsSeatsSemaphores[i] = CreateSemaphore(NULL, 0, 1, NULL);
		barbersSeatsSemaphores[i] = CreateSemaphore(NULL, 1, 1, NULL);
	}

	HANDLE *clientsThreads = new HANDLE[clients];
	for (int i = 0; i < clients; i++)
	{
		clientsThreads[i] = CreateThread(NULL,
			0,
			ClientFunction,
			(LPVOID)i,
			0,
			0);
	}

	HANDLE *barbersThreads = new HANDLE[barbers];
	for (int i = 0; i < barbers; i++)
	{
		barbersThreads[i] = CreateThread(NULL,
			0,
			BarberFunction,
			(LPVOID)i,
			0,
			0);
	}

	WaitForMultipleObjects(clients, clientsThreads, TRUE, INFINITE);
	WaitForMultipleObjects(barbers, barbersThreads, TRUE, INFINITE);

	for (int i = 0; i < clients; i++)
	{
		CloseHandle(clientsThreads[i]);
	}
	for (int i = 0; i < barbers; i++)
	{
		CloseHandle(barbersThreads[i]);
	}
	for (int i = 0; i < capacity; i++)
	{
		CloseHandle(clientsSeatsSemaphores[i]);
		CloseHandle(barbersSeatsSemaphores[i]);
	}
	delete[] clientsThreads;
	delete[] barbersThreads;
	delete[] clientsSeatsSemaphores;
	delete[] barbersSeatsSemaphores;

	return 0;
}

DWORD WINAPI BarberFunction(LPVOID lpParam)
{
	int index = (int)lpParam;
	srand(index);

	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	TCHAR msgBuf[BUF_SIZE];
	size_t cchStringSize;
	DWORD dwChars;

	while (true)
	{
		DWORD result = WaitForSingleObject(readyClientsSemaphore, BARBERS_WAITING_TIME_BEFORE_GO_HOME);
		if (result != WAIT_OBJECT_0)
		{
			return 0; //unless that the program will never end and we simply can't release resources in main function
		}
		int number = workingQueue.get();
		WaitForSingleObject(barbersSeatsSemaphores[number], INFINITE); //lock this seat unless barber finishes his work

		int seconds = rand() % 3 + 1;
		Sleep(seconds * 1000);

		StringCchPrintf(msgBuf, BUF_SIZE, TEXT("Парикмахер %d стрижет клиента с номерком %d.\n"), index, number);
		StringCchLength(msgBuf, BUF_SIZE, &cchStringSize);
		WriteConsole(hStdout, msgBuf, (DWORD)cchStringSize, &dwChars, NULL);
		ReleaseSemaphore(clientsSeatsSemaphores[number], 1, NULL); //let client go

		waitingQueue.put(number); //put number back to the table in waiting room

		ReleaseSemaphore(barbersSemaphore, 1, NULL); //tell that the barber is free now

		StringCchPrintf(msgBuf, BUF_SIZE, TEXT("Парикмахер %d готов принять следующего клиента.\n"), index);
		StringCchLength(msgBuf, BUF_SIZE, &cchStringSize);
		WriteConsole(hStdout, msgBuf, (DWORD)cchStringSize, &dwChars, NULL);
	}

	return 0;
}

DWORD WINAPI ClientFunction(LPVOID lpParam)
{
	int index = (int)lpParam;
	srand(1000 + index);

	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	TCHAR msgBuf[BUF_SIZE];
	size_t cchStringSize;
	DWORD dwChars;

	for (int i = 0; i < repeat; i++)
	{
		int number = waitingQueue.get();
		while (number == ERROR) //empty queue
		{
			number = waitingQueue.get();
			StringCchPrintf(msgBuf, BUF_SIZE, TEXT("Свободных мест нет. Клиент %d уходит из парикмахерской.\n"), index);
			StringCchLength(msgBuf, BUF_SIZE, &cchStringSize);
			WriteConsole(hStdout, msgBuf, (DWORD)cchStringSize, &dwChars, NULL);

			int seconds = rand() % 5 + 1;
			Sleep(seconds * 1000);
		}

		//client now has his number and he can either go to barber's seat or to wait for barber
		StringCchPrintf(msgBuf, BUF_SIZE, TEXT("Клиент %d зашел в парикмахерскую и взял номерок %d.\n"), index, number);
		StringCchLength(msgBuf, BUF_SIZE, &cchStringSize);
		WriteConsole(hStdout, msgBuf, (DWORD)cchStringSize, &dwChars, NULL);

		WaitForSingleObject(barbersSemaphore, INFINITE); //waiting for the barber
		workingQueue.put(number); //put number to the table in barbers room

		ReleaseSemaphore(readyClientsSemaphore, 1, NULL); //client is no more waiting for the barber

		StringCchPrintf(msgBuf, BUF_SIZE, TEXT("Клиент %d садится в кресло парикмахера.\n"), index, number);
		StringCchLength(msgBuf, BUF_SIZE, &cchStringSize);
		WriteConsole(hStdout, msgBuf, (DWORD)cchStringSize, &dwChars, NULL);

		WaitForSingleObject(clientsSeatsSemaphores[number], INFINITE); //wait until barber finishes his work

		StringCchPrintf(msgBuf, BUF_SIZE, TEXT("Клиент %d постригся и уходит из парикмахерской.\n"), index, number);
		StringCchLength(msgBuf, BUF_SIZE, &cchStringSize);
		WriteConsole(hStdout, msgBuf, (DWORD)cchStringSize, &dwChars, NULL);

		ReleaseSemaphore(barbersSeatsSemaphores[number], 1, NULL); //finished, go home

		int seconds = rand() % 5 + 1;
		Sleep(seconds * 1000);
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
