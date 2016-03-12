#pragma once

#include "Edge.h"

class EdgesLinkedList
{
private:

	struct Node
	{
		Edge* edge;
		Node* next;
		Node* previous;

		Edge* Node::getEdge()
		{
			return edge;
		}

		Node* Node::getNext()
		{
			return next;
		}

		Node* Node::getPrevious()
		{
			return previous;
		}

		void Node::setEdge(Edge* edge)
		{
			this->edge = edge;
		}

		void Node::setNext(Node* next)
		{
			this->next = next;
		}

		void Node::setPrevious(Node* previous)
		{
			this->previous = previous;
		}

		Node(Edge *edge)
		{
			setEdge(edge);
			setNext(NULL);
			setPrevious(NULL);
		}
	
		Node::Node(Edge *edge, Node* next, Node* previous)
		{
			setEdge(edge);
			setNext(next);
			setPrevious(previous);
		}
	};

	int count;

	Node* first;
	Node* last;

	Node* getElement(int index);

public:

	EdgesLinkedList(void);

	int size();
	bool isEmpty();

	void add(Edge* edge);

	void removeBack();
	void removeFront();
	void remove(int index);

	void changeVertexesAfterRemoving(int index);
	void changeVertexesAfterAdding(int index);

	void change(int firstVertex, int secondVertex, int weight);

	Edge* toArray();

	bool contains(Edge* edge);
	Edge* get(int index);

	void clear();

	string toString();

	~EdgesLinkedList(void);
};

