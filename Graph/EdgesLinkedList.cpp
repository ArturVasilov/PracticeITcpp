#include "stdafx.h"
#include "EdgesLinkedList.h"


EdgesLinkedList::Node* EdgesLinkedList::getElement(int index)
{
	if (index < 0 || index >= size())
		throw new exception("Index out of bounds exception");

	if (index < size() - index)
	{
		Node* current = first;
		int currentIndex = 0;
		while (currentIndex < index)
		{
			current = current->getNext();
			currentIndex++;
		}
		return current;
	}

	else
	{
		Node* current = last;
		int currentIndex = size() - 1;
		while (currentIndex > index)
		{
			current = current->getPrevious();
			currentIndex--;
		}
		return current;
	}
}

EdgesLinkedList::EdgesLinkedList(void)
{
	count = 0;
	first = NULL;
	last = NULL;
}

int EdgesLinkedList::size()
{
	return count;
}

bool EdgesLinkedList::isEmpty()
{
	return size() == 0;
}

void EdgesLinkedList::add(Edge* edge)
{
	if (isEmpty())
	{
		first = new Node(edge);
		last = new Node(edge);
	}

	else if (size() == 1)
	{
		last = new Node(edge, NULL, first);
		first->setNext(last);
	}

	else
	{
		Node* ins = new Node(edge, NULL, last);
		last->setNext(ins);
		last = ins;
	}
	count++;
}

void EdgesLinkedList::removeBack()
{
	if (isEmpty())
		throw new exception("List is empty!");
	if (last->getPrevious() != NULL)
		last->getPrevious()->setNext(NULL);
	last = last->getPrevious();
	count--;
}

void EdgesLinkedList::removeFront()
{
	if (isEmpty())
		throw new exception("List is empty!");
	if (first->getNext() != NULL)
		first->getNext()->setPrevious(NULL);
	first = first->getNext();
	count--;
}

void EdgesLinkedList::remove(int index)
{
	if (index < 0 || index >= size())
		throw new exception("Index out of bounds exception");

	if (index == 0)
		removeFront();

	else if (index == size() - 1)
		removeBack();

	else 
	{
		Node* rem = getElement(index);

		rem->getPrevious()->setNext(rem->getNext());
		rem->getNext()->setPrevious(rem->getPrevious());

		count--;
	}
}

void EdgesLinkedList::change(int firstVertex, int secondVertex, int weight)
{
	Edge* edge = new Edge(firstVertex, secondVertex, weight);
	Node* cur = first;
	for ( ; !cur->getEdge()->equals(edge); cur = cur->getNext()) ;
	cur->getEdge()->setWeight(weight);
}

void EdgesLinkedList::changeVertexesAfterRemoving(int index)
{
	Node* current = first;
    while (current != NULL)
    {
		if (current->getEdge()->getFirst() > index)
			current->getEdge()->setFirst(current->getEdge()->getFirst() - 1);
        if (current->getEdge()->getSecond() > index)
			current->getEdge()->setSecond(current->getEdge()->getSecond() - 1);
		current = current->getNext();
	}
}

void EdgesLinkedList::changeVertexesAfterAdding(int index)
{
	Node* current = first;
    while (current != NULL)
    {
		if (current->getEdge()->getFirst() > index)
			current->getEdge()->setFirst(current->getEdge()->getFirst() + 1);
        if (current->getEdge()->getSecond() > index)
			current->getEdge()->setSecond(current->getEdge()->getSecond() + 1);
		current = current->getNext();
	}
}

bool EdgesLinkedList::contains(Edge* edge)
{
	Node* cur = first;
	for ( ; cur != NULL && !cur->getEdge()->equals(edge); cur = cur->getNext()) ;
	return cur != NULL;
}

Edge* EdgesLinkedList::get(int index)
{
	return getElement(index)->getEdge();
}

string EdgesLinkedList::toString()
{
	Node* cur = first;
	string res = "";
	while (cur != NULL)
	{
		res += cur->getEdge()->toString();
		res += "\n";
		cur = cur -> getNext();
	}
	return res;
}

void EdgesLinkedList::clear()
{
	if (size() <= 1)
	{
		delete(first);
		delete(last);
	}
	else
	{
		Node* current = first->getNext();
		while (current->getNext() != NULL)
		{
			delete(current->getPrevious());
			current = current->getNext();
		}
		delete(current);
	}
	count = 0;
}

EdgesLinkedList::~EdgesLinkedList(void)
{
	clear();
}
