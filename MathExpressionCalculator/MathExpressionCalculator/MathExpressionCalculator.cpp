// MathExpressionCalculator.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "Expression.h"
#include <iostream>
#include <cstring>

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	string s = "";
	for (int i = 0; i < 3; i++)
	{
		cin>>s;
		Expression expr(s);
		cout<<expr.expressionResult()<<endl;
	}
	system("pause");
	return 0;
}

