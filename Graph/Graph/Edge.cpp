#include "stdafx.h"
#include "Edge.h"


Edge::Edge(int first, int second, int weight)
{
	this->first = first;
	this->second = second;
	this->weight = weight;
}

Edge::Edge(void)
{
	setFirst(-1);
	setSecond(-1);
	setWeight(-1);
}

int Edge::getFirst()
{
	return first;
}

int Edge::getSecond()
{
	return second;
}

int Edge::getWeight()
{
	return weight;
}

void Edge::setFirst(int first)
{
	this->first = first;
}

void Edge::setSecond(int second)
{
	this->second = second;
}

void Edge::setWeight(int weight)
{
	this->weight = weight;
}

string Edge::toString()
{
	string s = "First vertex: " + to_string(getFirst());
	s += " ";
	s += "Second vertex: " + to_string(getSecond());
	s += " ";
	s += "Weight: " + to_string(getWeight()); 
	return s;
}

bool Edge::equals(Edge* edge)
{
	return getFirst() == edge->getFirst() &&
		getSecond() == edge->getSecond();
}


Edge::~Edge(void)
{
}
