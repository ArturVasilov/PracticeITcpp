#include "stdafx.h"
#include "Refer.h"

int Refer::getData()
{

}
void Refer::setData(int data)
{

}

Refer* Refer::getNext()
{

}
void Refer::setNext(Refer* next)
{

}

Refer* Refer::getPrevious()
{

}
void Refer::setPrevious(Refer* previous)
{

}

Refer::Refer(void)
{

}
Refer::Refer(int data)
{

}
Refer::Refer(int data, Refer* next, Refer* previous)
{

}

Refer::~Refer(void)
{
	delete(next);
	delete(previous);
}
