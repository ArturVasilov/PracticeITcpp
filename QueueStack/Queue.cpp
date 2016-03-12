#include "stdafx.h"
#include "Queue.h"

const int VERY_BAD_NUMBER = -666;

int Queue::size()
{
	return list->getSize();
}

bool Queue::isEmpty()
{
	return list->isEmpty();
}

Queue::Queue()
{
	list = new LinkedList();
}

Queue::Queue(int data)
{
	list = new LinkedList(data);
}
	
void Queue::add(int data)
{
	list->addBack(data);
}

int Queue::pop()
{
	if (isEmpty())
		return VERY_BAD_NUMBER;
	return list->popFront();
}

int Queue::peek()
{
	if (isEmpty())
		return VERY_BAD_NUMBER;
	return list->peekFront();
}
	
void Queue::clear()
{
	list->clear();
}

Queue::~Queue(void)
{
	list->clear();
	delete list;
}
