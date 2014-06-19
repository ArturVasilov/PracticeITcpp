#include "stdafx.h"
#include "LinkedList.h"

#include <vector>

LinkedList::LinkedList(void)
{
	first = NULL;
	last = NULL;
	count = 0;
}

LinkedList::LinkedList(int x)
{
	count = 0;
	addFirst(x);
}

void LinkedList::addFirst(int x)
{
	Node* add = new Node(x);
	if (count == 0)
	{
		first = add;
		last = add;
	}
	else if (count == 1)
	{
		first = add;
		first->next = last;
	}
	else 
	{
		add->next = first;
		first = add;
	}
	count++;
}

void LinkedList::addLast(int x)
{
	Node* add = new Node(x);
	if (count == 0)
	{
		addFirst(x);
		return;
	}
	else if (count == 1)
	{
		last = add;
		first->next = last;
	}
	else
	{
		last->next = add;
		last = add;
	}
	count++;
}

void LinkedList::insertAfter(int x, int index)
{
	if (index < 0 || index > count)
		throw new exception("index is out of bounds exception!");
	int i = 0;
	Node* ins = new Node(x);
	Node* cur = first;
	while (i < index)
	{
		cur = cur->next;
		i++;
	}
	ins->next = cur->next;
	cur->next = ins;
	count++;
}

void LinkedList::insertBefore(int x, int value)
{
	Node* ins = new Node(x);
	Node* cur = first;
	if (count == 0)
		return;
	if (first->data == value)
	{
		addFirst(x);
		return;
	}
	//count >= 2
	for ( ; cur->next != NULL && cur->next->data != value ; cur = cur->next ) ;
	if (cur->next == NULL)
		return;
	cur->next = new Node(x, cur->next);
}

void LinkedList::insertBetweenSimilar(int x)
{
	if (count < 2)
		return;
	Node* cur = first->next;
	Node* back = first;
	while (cur != NULL)
	{
		if (cur->data == back->data)
		{
			back->next = new Node(x, cur);
		}
		back = cur;
		cur = cur->next;
	}
}

int LinkedList::get(int index)
{
	if (index < 0 || index > count)
		throw new exception("index is out of bounds exception");
	int i = 0;
	Node* cur = first;
	while (i < index)
	{
		cur = cur->next;
		i++;
	}
	return cur->data;
}

bool contains(vector<int> &vector, int value)
{
	for (int i = 0; i < vector.size(); i++)
		if (vector[i] == value)
			return true;
	return false;
}

void LinkedList::removeSimilar()
{
	vector<int> vector;
	if (count < 1)
		return;
	vector.push_back(first->data);
	Node* cur = first->next;
	Node* back = first;
	while (cur != NULL)
	{
		if (contains(vector, cur->data))
		{
			back->next = cur->next;
			back = cur;
			cur = back->next;
			continue;
		}
		else
		{
			vector.push_back(cur->data);
			back = cur;
			cur = cur->next;
		}
	}
}

string LinkedList::toString()
{
	string s = "";
	Node* cur = first;
	while (cur != NULL) 
	{
		s += to_string(cur->data) + " ";
		cur = cur->next;
	}
	return s;
}

LinkedList::~LinkedList(void)
{
	if (count == 1)
		delete(first);
	else
	{
		Node* cur = first->next;
		Node* back = first;
		while (cur != NULL)
		{
			delete(back);
			back = cur;
			cur = cur->next;
		}
		delete(back);
	}
}
