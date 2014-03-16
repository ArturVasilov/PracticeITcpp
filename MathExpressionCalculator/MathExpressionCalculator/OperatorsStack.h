#pragma once
class OperatorsStack
{
private:

	int count;
	int pointer;

	char* operators;

public:
	OperatorsStack(int count);

	int getCount();
	
	void pushOperator(char myOperator, int index);
	char getOperator(int index);
	char popOperator(int index);
	void pushBack(char myOperator);

	~OperatorsStack(void);
};

