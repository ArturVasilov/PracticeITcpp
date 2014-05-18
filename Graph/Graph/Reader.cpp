#include "stdafx.h"
#include "Reader.h"


Reader::Reader()
{
}

int** Reader::readMatrix()
{
	ifstream in(fileName);

	in >> n;

	int** matrix = new int*[n];
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
	return matrix;
}

EdgesLinkedList Reader::readEdges()
{
	ifstream in(fileName);
	in >> m;

	EdgesLinkedList edges;

	int nCalc = 0;

	for (int i = 0; i < m; i++)
	{
		int f, s, w;
		in >> f >> s >> w;
		Edge edge(f, s, w);
		edges.add(edge);
		if (f > nCalc)
			nCalc = f;
		if (s > nCalc)
			nCalc = s;
	}
	this->n = nCalc + 1;
	return edges;
}

void Reader::setFileName(string newFileName)
{
	this->fileName = newFileName;
}

int Reader::getEdgesCount() 
{
	return m;
}

int Reader::getVertexesCount()
{
	return n;
}

Reader::~Reader()
{
}
