#pragma once
#include "ExecutionFailedException.h"

#include <windows.h>
#include <tchar.h>
#include <strsafe.h>
#include "atlstr.h"

#define STRLEN(x) (sizeof(x)/sizeof(TCHAR) - 1)

using namespace std;

class Runnable
{
protected:
	void printThreadFinished(int index)
	{
		HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
		if (hStdout == INVALID_HANDLE_VALUE)
		{
			throw ExecutionFailedException();
		}

		char preparedMessage[] = "Thread with index=%d finished\n";
		char messageChar[30];
		sprintf(messageChar, preparedMessage, index);

		TCHAR message[30];
		_tcscpy(message, CA2W(messageChar));

		DWORD dwCount = 0;

		WriteConsole(hStdout, &message, STRLEN(message), &dwCount, NULL);
	}

public:
	virtual int run() throw(ExecutionFailedException) = 0;
};

class ThreadPoolExecutor
{
private:
	int threadsCount;
	int newThreadIndex;
	HANDLE *hThreadArray;

public:
	ThreadPoolExecutor(int threadsCount);

	void scheduleTask(Runnable *runnable);

	void waitForAll();

	~ThreadPoolExecutor();
};

