#include <string>

using namespace std;

class Book
{

private:

	int id;
	string title;
	string author;
	int year;

	const static int START_ID = -1;
	const static string START_TITLE;
	const static string START_AUTHOR;
	const static int START_YEAR = -1;

public:
	
	int getId();
	void setId(int id);

	string getTitle();
	void setTitle(string title);

	string getAuthor();
	void setAuthor(string author);

	int getYear();
	void setYear(int year);

	Book();
	Book(int id, string title, string author, int year);
	
	string bookToString();
	bool isBookEqual(Book book);
};

