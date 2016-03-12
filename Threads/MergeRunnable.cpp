#include "stdafx.h"
#include "MergeRunnable.h"

MergeRunnable::MergeRunnable(Merge *merge, int arrayIndex, int index)
{
	this->merge = merge;
	this->arrayIndex = arrayIndex;
	this->index = index;
}

int MergeRunnable::run() throw(ExecutionFailedException)
{
	merge->findPlace(arrayIndex, index);
	printThreadFinished(index);
	return 0;
}
