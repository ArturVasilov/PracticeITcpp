#include "stdafx.h"
#include "OperandsStack.h"

const int VERY_BAD_NUMBER = -666;

OperandsStack::OperandsStack(int count)
{
	pointer = 0;
	if (count >= 0)
	{
		this->count = count;
		operands = new double[count];
		for (int i = 0; i < count; i++)
			operands[i] = 0;
	}
}

int OperandsStack::getCount()
{
	return pointer;
}

void OperandsStack::pushOperand(double operand, int index)
{
	if (index >= 0 && index <= pointer) 
	{
		for (int i = count - 1; i > index; i--)
			operands[i] = operands[i - 1];
		operands[index] = operand;
		pointer++;
	}
}

double OperandsStack::getOperand(int index)
{
	if (index >= 0 && index < pointer)
		return operands[index];
	return VERY_BAD_NUMBER;
}

double OperandsStack::popOperand(int index)
{
	if (index >= 0 && index < pointer) 
	{
		pointer--;
		double result = operands[index];
		for (int i = index; i < count - 1; i++)
			operands[i] = operands[i + 1];
		return result;
	}
	return VERY_BAD_NUMBER;
}

void OperandsStack::pushBack(double operand)
{
	pushOperand(operand, pointer);
}

OperandsStack::~OperandsStack(void)
{
	delete operands;
}
