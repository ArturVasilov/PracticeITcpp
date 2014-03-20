#pragma once

#include "Iterator.h"
#include "Refer.h"

class List
{
private:
	int count;
	Refer* firstElement;
	Refer* lastElement;

	Refer* getElement(int index);

public:
	List(void);
	List(int data);

    int size();
    bool isEmpty();

	void append(int data);
    void prepend(int data);
	void insert(int data, int index);

    void removeBack();
    void removeFront();
    void remove(int index);

    void clear();

    int first();
    int last();
	int get(int index);
    int getIndexByValue(int data);

    bool contains(int data);

    int* toArray();

	Iterator* getIterator();
	Iterator* getBackIterator();

	~List(void);
};

