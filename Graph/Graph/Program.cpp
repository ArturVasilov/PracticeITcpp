// Graph.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

#include <iostream>

#include "Graph.h"

using namespace std;


int _tmain(int argc, _TCHAR* argv[])
{
	Graph g;
	g.readEdges("edges.txt");

	cout<<"reading edges: "<<endl;

	cout<<g.matrixToString()<<endl;
	cout<<g.edgesToString()<<endl;

	cout<<"add vertex 1, 2, remove vertex 2: "<<endl;

	g.addVertex(1);
	g.addVertex(2);
	g.deleteVertex(2);

	cout<<g.matrixToString()<<endl;
	cout<<g.edgesToString()<<endl;

	cout<<"working with edges test: "<<endl;

	g.addEdge(new Edge(0, 1, 4));
	g.changeEdge(0, 1, 15);
	g.deleteEdge(2, 3);

	cout<<g.matrixToString()<<endl;
	cout<<g.edgesToString()<<endl;

	cout<<"Graph connected: "<<g.isConnected()<<endl;

	system("pause");

	return 0;
}

