#include "stdafx.h"
#include "ThreadPoolExecutor.h"

using namespace System;

DWORD WINAPI workerFunction(LPVOID lpParam);

ThreadPoolExecutor::ThreadPoolExecutor(int threadsCount)
{
	this->threadsCount = threadsCount;
	this->newThreadIndex = 0;
	hThreadArray = new HANDLE[threadsCount];
}

void ThreadPoolExecutor::scheduleTask(Runnable *runnable)
{
	if (newThreadIndex >= threadsCount)
	{
		throw ExecutionFailedException();
	}

	hThreadArray[newThreadIndex] = CreateThread(
		NULL,                                  // default security attributes
		0,                                     // use default stack size
		workerFunction,                        // thread function name
		runnable,                              // argument to thread function
		0,                                     // use default creation flags
		0);                                    // returns the thread identifier

	if (hThreadArray[newThreadIndex] == NULL)
	{
		ExitProcess(3);
	}
	newThreadIndex++;
}

void ThreadPoolExecutor::waitForAll()
{
	WaitForMultipleObjects(threadsCount, hThreadArray, TRUE, INFINITE);
}

DWORD WINAPI workerFunction(LPVOID lpParam)
{
	Runnable *runnable = (Runnable*) lpParam;
	return runnable->run();
}

ThreadPoolExecutor::~ThreadPoolExecutor()
{
	for (int i = 0; i < threadsCount; i++)
	{
		CloseHandle(hThreadArray[i]);
	}

	delete[] hThreadArray;
}