#include "stdafx.h"
#include "List.h"

List::List(void)	
{
	count = 0;
	firstElement = NULL;
	lastElement = NULL;
}
List::List(int data)
{
	append(data);
}

int List::size()
{
	return count;
}
bool List::isEmpty()
{
	return size() == 0;
}

void List::append(int data)
{
	if (isEmpty())
	{
		firstElement = new Refer(data);
		lastElement = new Refer(data);
	}

	else if (size() == 1)
	{
		lastElement = new Refer(data);
		firstElement->setNext(lastElement);
		lastElement->setPrevious(firstElement);
	}

	else
	{
		Refer* insertElement = new Refer(data);
		insertElement->setPrevious(lastElement);
		lastElement->setNext(insertElement);
		lastElement = insertElement;
	}

	count++;
}
void List::prepend(int data)
{
	if (isEmpty())
		append(data);

	else if (size() == 1)
	{
		count++;
		firstElement = new Refer(data);
		firstElement->setNext(lastElement);
		lastElement->setPrevious(firstElement);
	}

	else
	{
		count++;
		Refer* insertElement = new Refer(data);
		insertElement->setNext(firstElement);
		firstElement->setPrevious(insertElement);
		firstElement = insertElement;
	}
}
void List::insert(int data, int index)
{
	if (index < 0 || index > size())
		return;

	if (index == 0)
		prepend(data);

	else if (index == size())
		append(data);

	else 
	{
		Refer* insertElement = new Refer(data);
		Refer* currentElement = getElement(index);

		currentElement->getPrevious()->setNext(insertElement);
		insertElement->setPrevious(currentElement->getPrevious());
		currentElement->setPrevious(insertElement);
		insertElement->setNext(currentElement);

		count++;
	}
}

void List::removeBack()
{
	if (isEmpty())
		return;
	if (lastElement->getPrevious() != NULL)
		lastElement->getPrevious()->setNext(NULL);
	lastElement = lastElement->getPrevious();
	count--;
}
void List::removeFront()
{
	if (isEmpty())
		return;
	if (firstElement->getNext() != NULL)
		firstElement->getNext()->setPrevious(NULL);
	firstElement = firstElement->getNext();
	count--;
}
void List::remove(int index)
{
	if (index < 0 || index >= size())
		return;
	
	if (index == 0)
		removeFront();

	else if (index == size() - 1)
		removeBack();

	else
	{
		Refer* deleteRefer = getElement(index);

		deleteRefer->getPrevious()->setNext(deleteRefer->getNext());
		deleteRefer->getNext()->setPrevious(deleteRefer->getPrevious());

		count--;
	}
}

void List::clear()
{
	while (!isEmpty())
		removeFront();
}

int List::first()
{
	if (isEmpty())
		return -1;
	return firstElement->getData();
}
int List::last()
{
	if (isEmpty())
		return -1;
	return lastElement->getData();
}
int List::get(int index)
{
	return getElement(index)->getData();
}
int List::getIndexByValue(int data)
{
	int currentIndex = 0;
	Refer* currentElement = firstElement;
	while (currentElement != NULL)
	{
		if (currentElement->getData() == data)
			return currentIndex;
		currentIndex++;
		currentElement = currentElement->getNext();
	}
	return -1;
}

bool List::contains(int data)
{
	Refer* currentElement = firstElement;
	while (currentElement != NULL)
	{
		if (currentElement->getData() == data)
			return true;
		currentElement = currentElement->getNext();
	}
	return false;
}

int* List::toArray()
{
	int* res = new int[size()];
	Refer* currentElement = firstElement;
	for (int i = 0; i < size(); i++)
	{
		res[i] = currentElement->getData();
		currentElement = currentElement->getNext();
	}
	return res;
}

Iterator* List::getIterator()
{
	return new Iterator(firstElement);
}

Iterator* List::getBackIterator()
{
	return new Iterator(lastElement);
}

Refer* List::getElement(int index)
{
	if (index < 0 || index >= size())
		return NULL;

	if (index < size() - index)
	{
		Refer* currentElement = firstElement;
		int currentIndex = 0;
		while (currentIndex < index)
		{
			currentElement = currentElement->getNext();
			currentIndex++;
		}
		return currentElement;	
	}

	Refer* currentElement = lastElement;
	int currentIndex = size() - 1;
	while (currentIndex > index)
	{
		currentElement = currentElement->getPrevious();
		currentIndex--;
	}
	return currentElement;
}

List::~List(void)
{
	clear();
	delete(lastElement);
	delete(firstElement);
}