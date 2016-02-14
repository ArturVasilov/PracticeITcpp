#include "stdafx.h"
#include "ThreadPoolExecutor.h"

#include <windows.h>
#include <tchar.h>
#include <strsafe.h>
#include "atlstr.h"

#define STRLEN(x) (sizeof(x)/sizeof(TCHAR) - 1)

using namespace System;

DWORD WINAPI calculationFunction(LPVOID lpParam);

ThreadPoolExecutor::ThreadPoolExecutor(int threadsCount)
{
	this->threadsCount = threadsCount;
	dwThreadIdArray = new DWORD[threadsCount];
	hThreadArray = new HANDLE[threadsCount];
}

void ThreadPoolExecutor::scheduleTask(PArrayTask task)
{
	hThreadArray[task->index] = CreateThread(
		NULL,                             // default security attributes
		0,                                // use default stack size
		calculationFunction,              // thread function name
		task,                             // argument to thread function
		0,                                // use default creation flags
		&dwThreadIdArray[task->index]);   // returns the thread identifier

	if (hThreadArray[task->index] == NULL)
	{
		ExitProcess(3);
	}
}

void ThreadPoolExecutor::waitForAll()
{
	WaitForMultipleObjects(threadsCount, hThreadArray, TRUE, INFINITE);
}

ThreadPoolExecutor::~ThreadPoolExecutor()
{
	for (int i = 0; i < threadsCount; i++)
	{
		CloseHandle(hThreadArray[i]);
	}

	delete[] dwThreadIdArray;
	delete[] hThreadArray;
}

DWORD WINAPI calculationFunction(LPVOID lpParam)
{
	PArrayTask task = (PArrayTask) lpParam;
	task->arrays->calculate(task->index);

	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hStdout == INVALID_HANDLE_VALUE)
	{
		return 1;
	}

	char preparedMessage[] = "Thread with index=%d finished\n";
	char messageChar[30];
	sprintf(messageChar, preparedMessage, task->index);

	TCHAR message[30];
	_tcscpy(message, CA2W(messageChar));

	DWORD dwCount = 0;
	//TCHAR message[] = L"Thread with index=%d finished\n";

	WriteConsole(hStdout, &message, STRLEN(message), &dwCount, NULL);
	delete(task);
	return 0;
}