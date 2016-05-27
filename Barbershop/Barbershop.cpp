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
		WaitForSingleObject(mutex, INFINITE);
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

SyncronizedIntQueue waitingQueue; //table in waiting room
SyncronizedIntQueue workingQueue; //table in barbes room

HANDLE barbersSemaphore; //semaphore for free barbers 
HANDLE readyClientsSemaphore; //semaphore for clients which are waiting for barber

HANDLE* clientsSeatsSemaphores; //wait haircut finished for each seat
HANDLE haircutFinishedSemaphore; //semaphore to leave the seat

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
	for (int i = 0; i < capacity; i++)
	{
		clientsSeatsSemaphores[i] = CreateSemaphore(NULL, 0, 1, NULL);
	}
	haircutFinishedSemaphore = CreateSemaphore(NULL, 0, barbers, NULL);

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

	for (int i = 0; i < clients; i++)
	{
		CloseHandle(clientsThreads[i]);
	}
	for (int i = 0; i < capacity; i++)
	{
		CloseHandle(clientsSeatsSemaphores[i]);
	}
	CloseHandle(haircutFinishedSemaphore);

	delete[] clientsThreads;
	delete[] barbersThreads;
	delete[] clientsSeatsSemaphores;

	return 0;
}

DWORD WINAPI ClientFunction(LPVOID lpParam)
{
	int index = (int)lpParam;
	srand(100000 + index);

	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	TCHAR msgBuf[BUF_SIZE];
	size_t cchStringSize;
	DWORD dwChars;

	int i = 0;
	while (i < repeat)
	{
		int number = waitingQueue.get(); //waiting for number (step 1)
		if (number == ERROR) //queue is empty
		{
			StringCchPrintf(msgBuf, BUF_SIZE, TEXT("Свободных мест нет. Клиент %d уходит из парикмахерской.\n"), index);
			StringCchLength(msgBuf, BUF_SIZE, &cchStringSize);
			WriteConsole(hStdout, msgBuf, (DWORD)cchStringSize, &dwChars, NULL);

			int seconds = rand() % 5 + 1;
			Sleep(seconds * 1000);
		}
		else
		{
			//client now has his number and he can either go to barber's seat or to wait for barber
			StringCchPrintf(msgBuf, BUF_SIZE, TEXT("Клиент %d зашел в парикмахерскую и взял номерок %d.\n"), index, number);
			StringCchLength(msgBuf, BUF_SIZE, &cchStringSize);
			WriteConsole(hStdout, msgBuf, (DWORD)cchStringSize, &dwChars, NULL);

			WaitForSingleObject(barbersSemaphore, INFINITE); //waiting for the barber (step 2)
			workingQueue.put(number); //put number to the table in barbers room (step 3)

			StringCchPrintf(msgBuf, BUF_SIZE, TEXT("Клиент %d садится в кресло парикмахера.\n"), index, number);
			StringCchLength(msgBuf, BUF_SIZE, &cchStringSize);
			WriteConsole(hStdout, msgBuf, (DWORD)cchStringSize, &dwChars, NULL);

			//client is no more waiting for the barber
			ReleaseSemaphore(readyClientsSemaphore, 1, NULL);

			//wait until barber finishes his work (step 4)
			WaitForSingleObject(clientsSeatsSemaphores[number], INFINITE);

			StringCchPrintf(msgBuf, BUF_SIZE, TEXT("Клиент %d постригся и уходит из парикмахерской.\n"), index, number);
			StringCchLength(msgBuf, BUF_SIZE, &cchStringSize);
			WriteConsole(hStdout, msgBuf, (DWORD)cchStringSize, &dwChars, NULL);

			//finished, release seat and notify barber (step 5)
			ReleaseSemaphore(haircutFinishedSemaphore, 1, NULL); 

			int seconds = rand() % 5 + 1;
			Sleep(seconds * 1000);

			i++;
		}
	}
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
		//waiting for the client (step 1)
		WaitForSingleObject(readyClientsSemaphore, INFINITE);
		
		int number = workingQueue.get(); //take client number (step 2)

		StringCchPrintf(msgBuf, BUF_SIZE, TEXT("Парикмахер %d стрижет клиента с номерком %d.\n"), index, number);
		StringCchLength(msgBuf, BUF_SIZE, &cchStringSize);
		WriteConsole(hStdout, msgBuf, (DWORD)cchStringSize, &dwChars, NULL);

		int seconds = rand() % 3 + 1;
		Sleep(seconds * 1000);
		//haircut is finished, client should leave the seat (step 3)
		ReleaseSemaphore(clientsSeatsSemaphores[number], 1, NULL);

		//wait until client leaves its' seat to be ready for next client (step 4)
		WaitForSingleObject(haircutFinishedSemaphore, INFINITE); 

		waitingQueue.put(number); //put number back to the table in waiting room (step 5)

		StringCchPrintf(msgBuf, BUF_SIZE, TEXT("Парикмахер %d готов принять следующего клиента.\n"), index);
		StringCchLength(msgBuf, BUF_SIZE, &cchStringSize);
		WriteConsole(hStdout, msgBuf, (DWORD)cchStringSize, &dwChars, NULL);

		ReleaseSemaphore(barbersSemaphore, 1, NULL); //tell that the barber is free now
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
