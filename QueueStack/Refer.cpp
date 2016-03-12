#include "stdafx.h"
#include "Refer.h"


Refer::Refer(int data, Refer* next)
{
	this->data = data;
	this->next = next;
}

int Refer::getData() 
{
	return data;
}


void Refer::setDet(int data)
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