#include "stdafx.h"
#include "Book.h"

using namespace std;

const string Book::START_TITLE = "";
const string Book::START_AUTHOR = "";

int Book::getId()
{
	return id;
}
void Book::setId(int id)
{
	this->id = id;
}

string Book::getTitle()
{
	return title;
}
void Book::setTitle(string title)
{
	this->title = title;
}

string Book::getAuthor()
{
	return author;
}
void Book::setAuthor(string author)
{
	this->author = author;
}

int Book::getYear()
{
	return year;
}
void Book::setYear(int year)
{
	this->year = year;
}

Book::Book()
{
	setId(START_ID);
	setTitle(START_TITLE);
	setAuthor(START_AUTHOR);
}

Book::Book(int id, string title, string author, int year)
{
	setId(id);
	setTitle(title);
	setAuthor(author);
	setYear(year);
}

string Book::bookToString()
{
	return to_string(getId()) + " " + getTitle() + " " + getAuthor()
		+ " " + to_string(getYear());
}

bool Book::isBookEqual(Book book)
{
	bool equalId = (this->getId() == book.getId()) || (book.getId() == START_ID);
	bool equalTitle = (this->getTitle() == book.getTitle()) ||
		(book.getTitle() == START_TITLE);
	bool equalAuthor = (this->getAuthor() == book.getAuthor()) ||
		(book.getAuthor() == START_AUTHOR);
	bool equalYear = (this->getId() == book.getId()) || (book.getId() == START_YEAR);

	return (equalId && equalTitle && equalAuthor && equalYear);
}
