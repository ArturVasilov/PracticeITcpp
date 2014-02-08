// LibrarySearch.cpp: главный файл проекта.

#include "stdafx.h"
#include <iostream>
#include "Book.h"

using namespace std;

int main()
{
	Book book(32, "Crime and Punishment", "Dostoevsky", 1865);
	cout<<book.bookToString()<<endl;

	Book book_test;
	book_test.setId(32);
	book_test.setTitle("Crime and Punishment");
	cout<<book.isBookEqual(book_test)<<endl;

	system("pause");
    return 0;
}
