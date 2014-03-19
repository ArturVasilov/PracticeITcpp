#pragma once

#include "Refer.h"

class Iterator
{
private:
	Refer* current;
public:
	Iterator(Refer* current);

	bool hasNext();
	int next();

	bool hasPrevious();
	int previous();

	~Iterator(void);
};

