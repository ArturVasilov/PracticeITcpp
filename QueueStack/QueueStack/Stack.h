#pragma once

#include "LinkedList.h"

class Stack
{
private:
	LinkedList* list;

public:
	int size();
	bool isEmpty();

	Stack();
	Stack(int data);
		
	void add(int data);

	int pop();
	int peek();
	
	void clear();

	~Stack(void);

};

