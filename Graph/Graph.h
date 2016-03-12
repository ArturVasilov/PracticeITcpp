#pragma once

#include "EdgesLinkedList.h"

#include "GraphConnection.h"


class Graph
{
private:

	int** matrix;
	EdgesLinkedList edges;

	int n;
	int m;

	string shift(int x);

public:

	const static int INF = 999999; 

	Graph(void);

	void readMatrix(string fileName);
	void readEdges(string fileName);

	void transformMatrixToEdges();
    void transformEdgesToMatrix();
	
	void deleteVertex(int index);
	void addVertex(int index);
	void changeVertex(int index);

	void addEdge(Edge* edge);
	void deleteEdge(int firstVertex, int secondVertex);
	void changeEdge(int firstVertex, int secondVertex, int weight);

	bool isConnected();

	string matrixToString();
	string edgesToString();

	~Graph(void);
};

