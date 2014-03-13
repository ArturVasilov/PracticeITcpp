#include "stdafx.h"
#include "Stack.h"

const int VERY_BAD_NUMBER = -666;

int Stack::size()
{
	return list->getSize();
}

bool Stack::isEmpty()
{
	return list->isEmpty();
}

Stack::Stack()
{
	list = new LinkedList();
}

Stack::Stack(int data)
{
	list = new LinkedList(data);
}

void Stack::add(int data)
{
	list->addFront(data);
}

int Stack::pop()
{
	if (isEmpty())
		return VERY_BAD_NUMBER;
	return list->popFront();
}

int Stack::peek()
{
	if (isEmpty())
		return VERY_BAD_NUMBER;
	return list->peekFront();
}

void Stack::clear()
{
	list->clear();
}

Stack::~Stack(void)
{
	clear();
	delete list;
}
