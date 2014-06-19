#pragma once

#include <string>

using namespace std;

class LinkedList
{
private:

	struct Node
	{
		int data;
		Node* next;

		Node(int data) 
		{
			this->data = data;
			next = NULL;
		}

		Node(int data, Node* next)
		{
			this->data = data;
			this->next = next;
		}

	};

	Node* first;
	Node* last;

	int count;

public:

	LinkedList(void);
	
	LinkedList(int x);

	void addFirst(int x);
	void addLast(int x);
	void insertAfter(int x, int index);
	void insertBefore(int x, int value);
	void insertBetweenSimilar(int x);

	int get(int i);

	void removeSimilar();

	string toString();

	~LinkedList(void);
};

