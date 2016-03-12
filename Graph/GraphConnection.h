#pragma once
class GraphConnection
{
private:
	int n;

	bool* flags;

	int** matrix;

	bool isConnected;

	void getAnswer();

	void flag(int index);

public:
	GraphConnection(int n, int** matrix);

	bool graphConnected();

	~GraphConnection(void);
};

