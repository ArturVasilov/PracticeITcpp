#pragma once
#include "Merge.h"
#include "ThreadPoolExecutor.h"

class MergeRunnable : Runnable
{
private:
	Merge *merge;
	int arrayIndex;
	int index;

public:
	MergeRunnable(Merge *merge, int arrayIndex, int index);

	int run() throw(ExecutionFailedException);
};

