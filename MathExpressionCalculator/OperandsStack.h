#include <string>

using namespace std;

class OperandsStack
{
private:
	int count;
	int pointer;

	double* operands;
public:
	OperandsStack(int count);

	int getCount();

	void pushOperand(double operand, int index);
	double getOperand(int index);
	double popOperand(int index);

	void pushBack(double operand);

	~OperandsStack(void);
};

