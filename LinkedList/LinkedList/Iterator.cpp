#include "stdafx.h"
#include "Iterator.h"


Iterator::Iterator(Refer* current)
{
}

bool Iterator::hasNext()
{

}
int Iterator::next()
{

}

bool Iterator::hasPrevious()
{

}
int Iterator::previous()
{

}

Iterator::~Iterator(void)
{
	delete(current);
}
