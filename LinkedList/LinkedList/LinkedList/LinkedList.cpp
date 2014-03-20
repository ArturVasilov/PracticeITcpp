// LinkedList.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

#include "List.h"

#include <iostream>

using namespace std;

void print(List* list)
{
	Iterator* myIterator = list->getIterator();
	while (myIterator->hasCurrent())
		cout<<myIterator->next()<<" ";
	cout<<endl;
}


int _tmain(int argc, _TCHAR* argv[])
{
	List* list = new List(5);
	list->append(4);
	list->append(5);
	print(list);

	system("pause");

	return 0;
}