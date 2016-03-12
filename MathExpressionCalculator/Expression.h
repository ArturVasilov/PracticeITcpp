#include <string>

using namespace std;

class Expression
{
private:
	string expr;

	string scobExpr(string expr);
	double exprResult(string expr);

	bool stringHasScobs(string expr);

	bool isSign(char c);
	bool isNumber(char c);

	double doMathFromSymbols(char chOperator, double first, double second);

	string doubleToString(double number);

	string subString(string s, int j);

public:

	Expression(string expr);

	double expressionResult();
};

