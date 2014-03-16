#include "stdafx.h"
#include "OperatorsStack.h"

const char VERY_BAD_SYMBOL = '\0';

OperatorsStack::OperatorsStack(int count)
{
	if (count >= 0)
	{
		pointer = 0;
		this->count = count;
		operators = new char[count];
		for (int i = 0; i < count; i++)
			operators[i] = '\0';
	}
}

int OperatorsStack::getCount()
{
	return pointer;
}

void OperatorsStack::pushOperator(char myOperator, int index)
{
	if (index >= 0 && index <= pointer)
	{
		for (int i = count - 1; i > index; i--)
			operators[i] = operators[i - 1];
		operators[index] = myOperator;
		pointer++;
	}
}

char OperatorsStack::getOperator(int index) 
{
	if (index >= 0 && index < pointer)
		return operators[index];
	return VERY_BAD_SYMBOL;
}

char OperatorsStack::popOperator(int index)
{
	if (index >= 0 && index < pointer)
	{
		pointer--;
		char result = operators[index];
		for (int i = index; i < count - 1; i++)
			operators[i] = operators[i + 1];
		return result;
	}
	return VERY_BAD_SYMBOL;
}

void OperatorsStack::pushBack(char myOperator)
{
	pushOperator(myOperator, pointer);
}

OperatorsStack::~OperatorsStack(void)
{
	delete operators;
}
