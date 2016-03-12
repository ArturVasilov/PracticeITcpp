#include "stdafx.h"
#include "LinkedList.h"
#include <iostream>

using namespace std;

const int VERY_BAD_NUMBER = -666;

int LinkedList::getSize()
{
	return size;
}

bool LinkedList::isEmpty()
{
	return getSize() == 0;
}

LinkedList::LinkedList()
{
	size = 0;
	firstElement = NULL;
	lastElement = NULL;
}

LinkedList::LinkedList(int data)
{
	firstElement = new Refer(data, NULL);
	lastElement = new Refer(data, NULL);
	size = 1;
}

void LinkedList::addBack(int data)
{
	if (isEmpty())
	{
		firstElement = new Refer(data, NULL);
		lastElement = new Refer(data, NULL);	
	}

	else if (getSize() == 1)
	{
		lastElement = new Refer(data, NULL);
		firstElement->setNext(lastElement);
	}

	else 
	{
		lastElement->setNext(new Refer(data, NULL));
		lastElement->setNext(lastElement->getNext());
	}

	size++;
}

void LinkedList::addFront(int data)
{
	if (isEmpty())
		addBack(data);

	else if (getSize() == 1)
	{
		firstElement = new Refer(data, NULL);
		firstElement->setNext(lastElement);
	}

	else 
	{
		Refer* insert = new Refer(data, NULL);
		insert->setNext(firstElement);
		firstElement = insert;
	}

	size++;
}

int LinkedList::popFront()
{
	if (isEmpty())
		return VERY_BAD_NUMBER;
	int data = firstElement->getData();
	if (getSize() == 1)
	{
		firstElement = firstElement->getNext();
		lastElement = NULL;
	}
	else
		firstElement = firstElement->getNext();
	size--;
	return data;
}

int LinkedList::peekFront()
{
	if (isEmpty())
		return VERY_BAD_NUMBER;
	return firstElement->getData();
}

void LinkedList::clear()
{
	size = 0;
	if (firstElement != NULL)
		firstElement->setNext(NULL);
	firstElement = NULL;
	lastElement = NULL;
}

LinkedList::~LinkedList(void)
{
	clear();
}
