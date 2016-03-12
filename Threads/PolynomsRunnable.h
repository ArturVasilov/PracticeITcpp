#pragma once
#include "Polynoms.h"
#include "ThreadPoolExecutor.h"

class PolynomsRunnable : Runnable
{
private:
	Polynoms *polynoms;
	int index;

public:

	PolynomsRunnable(Polynoms *polynoms, int index);

	int run() throw(ExecutionFailedException);
};

