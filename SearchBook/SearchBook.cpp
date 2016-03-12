// LibrarySearch.cpp: главный файл проекта.

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include "Book.h"

using namespace std;


int main()
{
/*	Book book(32, "Crime and Punishment", "Dostoevsky", 1865);
	cout<<book.bookToString()<<endl;

	Book book_test;
	book_test.setId(32);
	book_test.setTitle("Crime and Punishment");
	cout<<book.isBookEqual(book_test)<<endl;

	system("pause");
    return 0;
*/
	ifstream in("books.txt");

	int n = 0;
	in>>n;

	Book* books;
	books = new Book[n];

	for (int i = 0; i < n; i++)
	{
		int id;
		string title;
		string author;
		int year;
		
		in>>id>>title>>author>>year;
		books[i].setId(id);
		books[i].setTitle(title);
		books[i].setAuthor(author);
		books[i].setYear(year);
	}

	int k;
	in>>k;
	
	ofstream out("output.txt");

	for (int i = 0; i < k; i++)
	{
		int cr_count;
		in>>cr_count;
		
		Book searching_book;

		for (int j = 0; j < cr_count; j++)
		{
			char cr;
			in>>cr;

			int id;
			string title;
			string author;
			int year;

			switch (cr)
			{
			case 'i':
				in>>id;
				searching_book.setId(id);
				break;

			case 't':
				in>>title;
				searching_book.setTitle(title);
				break;

			case 'a':
				in>>author;
				searching_book.setAuthor(author);
				break;

			case 'y':
				in>>year;
				searching_book.setYear(year);
				break;

			default:
				break;
			}
		}
		out<<"Запрос " + to_string(i + 1) + ":"<<endl;

		for (int j = 0; j < n; j++)
		{
			if (books[j].isBookEqual(searching_book))
				out<<books[j].bookToString()<<endl;
		}
	}

	in.close();
	
	out.close();

	system("pause");
}


