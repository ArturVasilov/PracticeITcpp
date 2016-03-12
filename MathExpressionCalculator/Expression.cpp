#include "stdafx.h"
#include "Expression.h"
#include "OperandsStack.h"
#include "OperatorsStack.h"

const char PLUS = '+';
const char MINUS = '-';
const char PRODUCTION = '*';
const char DIVISION = '/';

Expression::Expression(string expr)
{
	this->expr = expr;
}

double Expression::expressionResult()
{
	return exprResult(scobExpr(expr));
}

string Expression::scobExpr(string expr)
{
	string s = "";
	int n = expr.length();
	for (int i = 0; i < n; i++)
	{
		if (expr[i] == '(')
		{
			string someRes = "";
			i++;
			while (i < n && expr[i] != ')')
			{
				if (expr[i] == '(')
				{
					string recur = subString(expr, i + 1);
					someRes += scobExpr(recur);
					return s + someRes;
					break;
				}
				someRes += expr[i];
				i++;
			}
			s += doubleToString(exprResult(someRes));
		}
		else if (expr[i] == ')')
			return s;
		else s += expr[i];
	}
	return s;
}

double Expression::exprResult(string expr)
{
	OperandsStack operandsStack(expr.length());
	OperatorsStack operatorsStack(expr.length());

	double current_number = 0;
	double result = 0;

	int i = 0;
	//first symbol - number
	current_number = (int)expr[i] - (int)'0';
	i++;
	int n = expr.length();
	while (i < n)
	{
		if (isNumber(expr[i]))
		{
			current_number *= 10;
			current_number += (int)expr[i] - (int)'0';
			i++;
			continue;
		}

		else //sign
		{
			operandsStack.pushBack(current_number);
			current_number = 0;
			operatorsStack.pushBack(expr[i]);
			i++;
		}
	}
	operandsStack.pushBack(current_number);
	//production or divistion
	for (int j = 0; j < operandsStack.getCount(); j++)
	{
		if ((operatorsStack.getOperator(j) == PRODUCTION) 
			|| (operatorsStack.getOperator(j) == DIVISION))
		{
			double first = operandsStack.popOperand(j);
			double second = operandsStack.popOperand(j);
			char sign = operatorsStack.popOperator(j);
			operandsStack.pushOperand(doMathFromSymbols(sign, first, second), j);
			j--;
		}
	}

	for (int j = 0; j < operandsStack.getCount(); j++)
	{
		if (operatorsStack.getOperator(j) == MINUS) 
		{
			double first = operandsStack.popOperand(j);
			double second = operandsStack.popOperand(j);
			char sign = operatorsStack.popOperator(j);
			operandsStack.pushOperand(doMathFromSymbols(sign, first, second), j);
			j--;
		}
	}

	while (operandsStack.getCount() > 0)
	{
		result = doMathFromSymbols(PLUS,
			operandsStack.popOperand(operandsStack.getCount() - 1), result);
	}
	return result;
}


bool Expression::stringHasScobs(string expr)
{
	int n = expr.length();
	for (int i = 0; i < n; i++)
		if (expr[i] == '(' || expr[i] == ')')
			return true;
	return false;
}

bool Expression::isNumber(char c)
{
	return (c >= '0') && (c <= '9');
}

bool Expression::isSign(char c)
{
	return (c == PLUS) || (c == MINUS) || (c == PRODUCTION) || (c == DIVISION);
}

double Expression::doMathFromSymbols(char chOperator, double first, double second)
{
	switch (chOperator)
	{
	case PLUS:
		return first + second;
	case MINUS:
		return first - second;
	case PRODUCTION:
		return first * second;
	case DIVISION:
		return first / second;
	default:
		break;
	}
	return -1;
}

string Expression::doubleToString(double number)
{
	string result = "";
	int num = (int)number;
	while (num > 0)
	{
		int a = num % 10;
		result += a + '0';
		num /= 10;
	}
	return result;
}

string Expression::subString(string s, int j)
{
	int n = s.length();
	string result = "";
	for (int i = j; i < n; i++)
		result += s[i];
	return result;
}