#pragma once

#include "Refer.h"

class Iterator
{
private:
	Refer* current;
public:
	Iterator(Refer* current);

	bool hasCurrent();

	int next();

	int previous();

	~Iterator(void);
};

