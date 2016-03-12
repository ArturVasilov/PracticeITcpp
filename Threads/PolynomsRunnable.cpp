#include "stdafx.h"
#include "PolynomsRunnable.h"

PolynomsRunnable::PolynomsRunnable(Polynoms *polynoms, int index) 
{
	this->polynoms = polynoms;
	this->index = index;
}

int PolynomsRunnable::run() throw(ExecutionFailedException)
{
	polynoms->calculate(index);
	printThreadFinished(index);
	return 0;
}
