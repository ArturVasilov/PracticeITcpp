#pragma once
#include <exception>

using namespace std;

class ExecutionFailedException : public exception
{
public:
	ExecutionFailedException();
};

