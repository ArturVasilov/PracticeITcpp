#pragma once

#include <string>

using namespace std;

class Edge
{
private:
	int first;
	int second;
	int weight;

public:
	Edge(int first, int second, int weight);

	Edge(void);

	int getFirst();

	int getSecond();

	int getWeight();

	void setFirst(int first);

	void setSecond(int second);

	void setWeight(int weight);

	string toString();

	bool equals(Edge* edge);

	~Edge(void);
};

