#pragma once
class Refer
{
private:
	int data;
	Refer* next;
public:
	Refer(int data, Refer* next);
	int getData();
	void setDet(int data);
	Refer* getNext();
	void setNext(Refer* next);
};

