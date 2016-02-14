#pragma once
#include "Arrays.h"

typedef struct ArrayTask {
	Arrays *arrays;
	int index;

	ArrayTask(Arrays *arrays, int index)
	{
		this->arrays = arrays;
		this->index = index;
	}

	ArrayTask()
	{
	}
} ArrayTask, *PArrayTask;

class ThreadPoolExecutor
{
private:
	int threadsCount;
	DWORD *dwThreadIdArray;
	HANDLE *hThreadArray;

public:
	ThreadPoolExecutor(int threadsCount);

	void scheduleTask(PArrayTask task);

	void waitForAll();

	~ThreadPoolExecutor();
};

