#include "stdafx.h"
#include "Graph.h"

#include <fstream>


string Graph::shift(int x)
{
	string s = to_string(INF);
	string s1 = to_string(x);
	while (s1.length() < s.length())
		s1 += " ";
	return s1;
}

Graph::Graph(void)
{
}

void Graph::readMatrix(string fileName)
{
	ifstream in(fileName);

	in >> n;

	matrix = new int*[n];
	for (int i = 0; i < n; i++)
		matrix[i] = new int[n];

	int mCalc = 0;

	for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
		{
			int x;
			in >> x;
			matrix[i][j] = (x == 0) ? INF : x;
			if (x > 0)
				mCalc++;
		}
	m = mCalc / 2;
	transformMatrixToEdges();
}

void Graph::readEdges(string fileName)
{
	ifstream in(fileName);
	in >> m;

	int nCalc = 0;

	for (int i = 0; i < m; i++)
	{
		int f, s, w;
		in >> f >> s >> w;
		edges.add(new Edge(f, s, w));
		if (f > nCalc)
			nCalc = f;
		if (s > nCalc)
			nCalc = s;
	}
	this -> n = nCalc + 1;
	transformEdgesToMatrix();
}

void Graph::transformMatrixToEdges()
{
	edges.clear();
	for (int i = 0; i < n; i++)
    {
         for (int j = i + 1; j < n; j++)
         {
              if (matrix[i][j] < INF)
              {
                  edges.add(new Edge(i, j, matrix[i][j]));
			  }
         }
	}
}

void Graph::transformEdgesToMatrix()
{
	matrix = new int*[n];
	for (int i = 0; i < n; i++)
	{
		matrix[i] = new int[n];
		for (int j = 0; j < n; j++)
			matrix[i][j] = INF;
	}
	for (int i = 0; i < m; i++)
    {
        Edge* edge = edges.get(i);
		matrix[edge->getFirst()][edge->getSecond()] = edge->getWeight();
		matrix[edge->getSecond()][edge->getFirst()] = edge->getWeight();
    }
}

void Graph::deleteVertex(int index)
{
	if (index >= n || index < 0)
		throw new exception("Vertex index is out of bounds exception");

	for (int i = 0; i < m; i++)
    {
         Edge* edge = edges.get(i);
		 if (edge->getFirst() == index || edge->getSecond() == index)
         {
              edges.remove(i);
              m--;
              i--;
			  break;
         }
    }
	edges.changeVertexesAfterRemoving(index);
	n--;
	transformEdgesToMatrix();
}

void Graph::addVertex(int index)
{
	if (index > n || index < 0)
		throw new exception("Vertex index is out of bounds exception");

	n++;

	int** newMatrix;

	newMatrix = new int*[n];
	for (int i = 0; i < n; i++)
	{
		newMatrix[i] = new int[n];
	}

	for (int i = 0; i < n; i++)
	{
		newMatrix[index][i] = INF;
		newMatrix[i][index] = INF;
	}

	for (int i = 0; i < index; i++)
		for (int j = 0; j < index; j++)
			newMatrix[i][j] = matrix[i][j];

	for (int i = index + 1; i < n; i++)
		for (int j = index + 1; j < n; j++)
			newMatrix[i][j] = matrix[i - 1][j - 1];

	for (int i = index + 1; i < n; i++)
        for (int j = 0; j < index; j++)
            newMatrix[i][j] = matrix[i - 1][j];
    for (int i = 0; i < index; i++)
        for (int j = index + 1; j < n; j++)
            newMatrix[i][j] = matrix[i][j - 1];

	for (int i = 0; i < n - 1; i++)
		delete(matrix[i]);
	delete(matrix);

	matrix = new int*[n];
	for (int i = 0; i < n; i++)
	{
		matrix[i] = new int[n];
	}

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			matrix[i][j] = newMatrix[i][j];

	for (int i = 0; i < n; i++)
		delete(newMatrix[i]);
	delete(newMatrix);

	transformMatrixToEdges();
}

void Graph::changeVertex(int index)
{
	if (index > n || index < 0)
		throw new exception("Vertex index is out of bounds exception");
    for (int i = 0; i < n; i++)
	{
        matrix[i][index] = INF;
		matrix[index][i] = INF;
    }
    transformMatrixToEdges();
}

void Graph::addEdge(Edge* edge)
{
	if (edge->getFirst() > n || edge->getSecond() > n)
        throw new exception("There are no such vertex in graph!");

	if (edges.contains(edge))
		edges.change(edge->getFirst(), edge->getSecond(), edge->getWeight());

	else 
	{
		m++;
		edges.add(edge);
	}
	transformEdgesToMatrix();
}

void Graph::deleteEdge(int firstVertex, int secondVertex)
{
	 if ((firstVertex >= n || firstVertex < 0) ||
         (secondVertex >= n || secondVertex < 0))
          throw new exception("Edge index is out of bounds exception");

	 for (int i = 0; i < m; i++)
     {
          Edge* edge = edges.get(i);
          if (edge->getFirst() == firstVertex && edge->getSecond() == secondVertex)
          {
               edges.remove(i);
               break;
          }
     }
     m--;
     transformEdgesToMatrix();
}

void Graph::changeEdge(int firstVertex, int secondVertex, int weight)
{
	if ((firstVertex >= n || firstVertex < 0) ||
        (secondVertex >= n || secondVertex < 0))
            throw new exception("Edge index is out of bounds exception");
    edges.change(firstVertex, secondVertex, weight);
    transformEdgesToMatrix();
}

bool Graph::isConnected()
{
	GraphConnection con(n, matrix);
	return con.graphConnected();
}

string Graph::matrixToString()
{
	string res = "";
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			res += shift(matrix[i][j]) + " ";
		res += "\n";
	}
	return res;		
}

string Graph::edgesToString()
{
	return edges.toString();
}

Graph::~Graph(void)
{

}
