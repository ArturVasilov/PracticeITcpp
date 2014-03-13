#pragma once
#include "LinkedList.h"

class Queue
{
private:
	LinkedList* list;

public:
	int size();
	bool isEmpty();

	Queue();
	Queue(int data);
		
	void add(int data);

	int pop();
	int peek();
	
	void clear();

	~Queue(void);
};

