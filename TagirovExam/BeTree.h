#pragma once

#include <string>

using namespace std;

class BeTree
{
private:
	struct Node
	{
		int data;
		Node* left;
		Node* right;

		Node(int data = 0, Node* left = NULL, Node* right = NULL)
		{
			this->data = data;
			this->left = left;
			this->right = right;
		}
	};

	Node* root;

	string BeTree::printInOrderHelp(Node* root);

public:

	BeTree(void);
	
	BeTree(int x);

	void add(int x);

	string printByLevels();
	string printInOrder();

	int sum();

	int isLeftTreesMoreThanRight();
	
	int deep();

	~BeTree(void);
};

