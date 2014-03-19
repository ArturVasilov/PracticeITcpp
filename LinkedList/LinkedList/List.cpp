#include "stdafx.h"
#include "List.h"

List::List(void)	
{

}
List::List(int data)
{

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

}
void List::prepend(int data)
{

}
void List::insert(int data, int index)
{

}

void List::removeBack()
{

}
void List::removeFront()
{

}
void List::remove(int index)
{

}

void List::clear()
{

}

int List::first()
{

}
int List::last()
{

}
int List::get(int index)
{

}
int List::getIndexByValue(int data)
{

}

bool List::contains(int data)
{

}

int* List::toArray()
{

}

Iterator* List::getIterator()
{
	return new Iterator(firstElement);
}

Iterator* List::getBackIterator()
{
	return new Iterator(lastElement);
}


List::~List(void)
{
	clear();
	delete(lastElement);
	delete(firstElement);
}
