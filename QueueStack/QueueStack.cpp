// QueueStack.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>

#include "Queue.h"
#include "Stack.h"

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	Queue queue(5); 
	queue.add(2);
	queue.add(4);
	queue.add(5);

	cout<<"Queue top: "<<queue.pop();
	cout<<" size now: "<<queue.size()<<endl;

	Stack stack(3);
	stack.add(2);
	stack.add(1332);
	stack.add(4);

	cout<<"Stack top: "<<stack.pop();
	cout<<" size now: "<<stack.size()<<endl;

	system("pause");
}

