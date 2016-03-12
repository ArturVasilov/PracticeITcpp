#include "stdafx.h"
#include "GraphConnection.h"


void GraphConnection::getAnswer()
{
	if (n < 2)
		isConnected = true;
    flag(0);
        for (int i = 0; i < n; i++)
		{
           if (!flags[i])
			   isConnected = false;
		}
	isConnected = true;
}

void GraphConnection::flag(int index)
{
	flags[index] = true;
    for (int i = 0; i < n; i++)
    {
        if (matrix[index][i] < 999999 &&
               !flags[i])
               flag(i);
    }
}

GraphConnection::GraphConnection(int n, int** matrix)
{
	this->n = n;
	this->matrix = new int*[n];
	for (int i = 0; i < n; i++)
		this->matrix[i] = new int[n];

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			this->matrix[i][j] = matrix[i][j];
			this->matrix[j][i] = matrix[j][i];
		}
	}

	flags = new bool[n];
	for (int i = 0; i < n; i++)
		flags[i] = false;

	getAnswer();
}

bool GraphConnection::graphConnected()
{
	return isConnected;
}

GraphConnection::~GraphConnection(void)
{
	for (int i = 0; i < n; i++)
		delete(matrix[i]);
	delete(matrix);
	delete(flags);
}
