// TestParser.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

#include <iostream>
#include <fstream>

#include <string>

using namespace std;

int main()
{
	string word;
	cin >> word;
	int len = word.length();
	ifstream in("input.txt");
	ofstream out("out.txt");
	while (!in.eof())
	{
		int count = 0;
		char c;
		in.get(c);
		if (in.eof())
			break;
		out << c;
		int currentIndex = 0;
		bool areSame = word[currentIndex] == c;
		while (c != '.' && !in.eof())
		{
			if (currentIndex > len - 1)
			{
				if (!areSame)
				{
					while (c != ' ')
					{
						in.get(c);
						out << c;
						if (c == '.')
						{
							out<<count;
						}
					}
					in.get(c);
					out << c;
					currentIndex = 0;
					areSame = word[currentIndex] == c;
					in.get(c);
					out << c;
					if (areSame)
						currentIndex++;
					continue;
				}
			}

			if (c == ' ')
			{
				if (areSame && currentIndex == len - 1)
				{
					currentIndex = 0;
					count++;
					in.get(c);
					out << c;
					areSame = word[currentIndex] == c;
					if (areSame)
						currentIndex++;
				}
			}
			else
			{
				areSame = word[currentIndex] == c;
				if (areSame)
					currentIndex++;
				if (currentIndex == len)
				{
					count++;
					currentIndex = 0;
				}
			}
			in.get(c);
			out << c;
		}
		out<<count;
	}
	in.close();
	out.close();
	return 0;
}

