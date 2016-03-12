#include "stdafx.h"
#include "Refer.h"

int Refer::getData()
{
	return data;	
}
void Refer::setData(int data)
{
	this->data = data;
}

Refer* Refer::getNext()
{
	return next;
}
void Refer::setNext(Refer* next)
{
	this->next = next;
}

Refer* Refer::getPrevious()
{
	return previous;
}
void Refer::setPrevious(Refer* previous)
{
	this->previous = previous;
}

Refer::Refer(int data)
{
	setData(data);
	setNext(NULL);
	setPrevious(NULL);
}
Refer::Refer(int data, Refer* next, Refer* previous)
{
	setData(data);
	setNext(next);
	setPrevious(previous);
}

Refer::~Refer(void)
{
	delete(next);
	delete(previous);
}
