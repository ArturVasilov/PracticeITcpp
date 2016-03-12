#pragma once

#include <string>
#include "Refer.h"

using namespace std;

class LinkedList
{
private:

	Refer* firstElement;
	Refer* lastElement;

	int size;

public:

	int getSize();
	bool isEmpty();

	LinkedList();
	LinkedList(int data);

	void addBack(int data);
	void addFront(int data);

	int popFront();
	int peekFront();

	void clear();

	~LinkedList(void);
};

