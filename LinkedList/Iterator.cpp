#include "stdafx.h"
#include "Iterator.h"


Iterator::Iterator(Refer* current)
{
	this->current = current;
}

bool Iterator::hasCurrent()
{
	return (current != NULL);
}
int Iterator::next()
{
	current = current->getNext();
	return current->getPrevious()->getData();
}

int Iterator::previous()
{
	current = current->getPrevious();
	return current->getNext()->getData();
}

Iterator::~Iterator(void)
{
	delete(current);
}
