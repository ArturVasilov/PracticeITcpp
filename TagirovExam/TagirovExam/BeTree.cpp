#include "stdafx.h"
#include "BeTree.h"

#include <queue>

BeTree::BeTree(void)
{
	root = NULL;
}

BeTree::BeTree(int x)
{
	root = new Node(x);
}

void BeTree::add(int x)
{
	Node* cur = root;
	Node* parent = root;
	while (cur != NULL)
	{
		parent = cur;
		if (cur->data == x)
			return;
		if (cur->data > x)
			cur = cur->left;
		else 
			cur = cur->right;
	}
	if (x < parent->data)
		parent->left = new Node(x);
	else
		parent->right = new Node(x);
}

string BeTree::printByLevels()
{
	if (root == NULL)
		return "";
	string s = "1: ";
	queue<pair<Node*, int>> q;
	pair<Node*, int> p(root, 1);
	q.push(p);
	int prevLevel = 1;
	while (!q.empty())
	{
		p = q.front();
		q.pop();
		int currentLevel = p.second;
		if (currentLevel > prevLevel)
		{
			prevLevel++;
			s += "\n" + to_string(prevLevel) + ": ";
		}
		s += to_string(p.first->data) + " ";
		pair<Node*, int> p1;
		if (p.first->left != NULL)
		{
			p1.first = p.first->left;
			p1.second = currentLevel + 1;
			q.push(p1);
		}
		if (p.first->right != NULL)
		{
			p1.first = p.first->right;
			p1.second = currentLevel + 1;
			q.push(p1);
		}
	}
	return s;
}

string BeTree::printInOrder()
{
	return printInOrderHelp(root);
}

string BeTree::printInOrderHelp(Node* root)
{
	string s = "";
	if (root == NULL)
		return s;
	else
		return printInOrderHelp(root->left) + " " +
		to_string(root->data) + " " + printInOrderHelp(root->right);
}

int BeTree::sum()
{
	int result = 0;
	if (root == NULL)
		return result;
	queue<Node*> q;
	q.push(root);
	while (!q.empty())
	{
		Node* p = q.front();
		q.pop();
		result += p->data;
		if (p->left != NULL)
			q.push(p->left);
		if (p->right != NULL)
			q.push(p->right);
	}
	return result;
}

int BeTree::isLeftTreesMoreThanRight()
{
	if (root == NULL)
		return 0;
	int left = 0;
	int right = 0;
	queue<Node*> q;
	q.push(root);
	while (!q.empty())
	{
		Node* p = q.front();
		q.pop();
		if (p->left != NULL)
		{
			q.push(p->left);
			left++;
		}
		if (p->right != NULL)
		{
			q.push(p->right);
			right++;
		}
	}
	return left > right ? 1 : left == right ? 0 : -1;
}

int BeTree::deep()
{
	int result = 0;
	if (root == NULL)
		return result;
	
}

BeTree::~BeTree(void)
{
	if (root == NULL)
		return;
	queue<Node*> q;
	Node* cur;
	q.push(root);
	while (!q.empty())
	{
		cur = q.front();
		q.pop();
		if (cur->left != NULL)
			q.push(cur->left);
		if (cur->right != NULL)
			q.push(cur->right);
		delete(cur);
	}
}
