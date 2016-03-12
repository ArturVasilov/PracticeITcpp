#pragma once

class Refer
{
private:
	int data;
	Refer* next;
	Refer* previous;
public:

	int getData();
	void setData(int data);

	Refer* getNext();
	void setNext(Refer* next);

	Refer* getPrevious();
	void setPrevious(Refer* previous);

	Refer(int data);
	Refer(int data, Refer* next, Refer* previous);

	~Refer(void);
};

