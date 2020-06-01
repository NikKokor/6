#include <iostream>
#include <string>
#include <vector>
using namespace std;

class book
{
    string name;
    string author;
public:
    book(string _name, const string _author)
    {
        name = _name;
        author = _author;
    }

    string getName()
    {
        return(name);
    }

    string getAuthor()
    {
        return(author);
    }

    /*void setName(string _name)
    {
        name = _name;
    }

    void setAuthor(string _author)
    {
        author = _author;
    }*/

};

class library
{
protected:
    vector<book> books;

public:
    library() {};

    library(vector<book> _books) {
        books = _books;
    }

protected:
    void addBook(book _book)
    {
        books.push_back(_book);
    }

    void delBook(book _book)
    {
        for(int i = 0; i < books.size(); i++)
        {
            if ((_book.getName() == books[i].getName()) && (_book.getAuthor() == books[i].getAuthor()))
            {
                books.erase(books.begin() + i);
                return;
            }
        }
    }

public:

    void print()
    {
        cout << "Books in the library: " << endl;
        for(int i = 0; i < books.size(); i++)
        {
            cout << books[i].getName() << " by " << books[i].getAuthor() << endl;
        }
        cout << endl;
    }
};

class reader
{
    vector<book> books;

    friend class librarian;

    void pickUpBook(book _book)
    {
        books.push_back(_book);
    }
public:
    book returnBook(string name, string author)
    {
        for(int i = 0; i < books.size(); i++)
        {
            if ((name == books[i].getName()) && (author == books[i].getAuthor()))
            {
                book b("","");
                b = books[i];
                books.erase(books.begin() + i);
                return b;
            }
        }
    }

    book pickUpBook(string name, string author)
    {
        book b(name, author);
        return b;
    }



    void print()
    {
        cout << "Books at the reader: " << endl;
        for(int i = 0; i < books.size(); i++)
        {
            cout << books[i].getName() << " by " << books[i].getAuthor() << endl;
        }
        cout << endl;
    }
};

class librarian : public library
{
    book searchByName(string name)
    {
        book b("","");
        for(int i = 0; i < books.size(); i++)
        {
            if(name == books[i].getName())
            {
                b = books[i];
                delBook(books[i]);
                //books.erase(books.begin() + i);
                return b;
            }
        }
        return b;
    }

    book searchByAuthor(string author)
    {
        book b("","");
        for(int i = 0; i < books.size(); i++)
        {
            if(author == books[i].getAuthor())
            {
                b = books[i];
                books.erase(books.begin() + i);
                return b;
            }
        }
        return b;
    }

    book searchByNameAndAuthor(string name, string author)
    {
        book b("","");
        for(int i = 0; i < books.size(); i++)
        {
            if ((name == books[i].getName()) && (author == books[i].getAuthor()))
            {
                b = books[i];
                books.erase(books.begin() + i);
                return b;
            }
        }
        return b;
    }
public:
    librarian(vector<book> _books) : library(_books)
    {

    }

    void putBook(book _book)
    {
        addBook(_book);
    }

    void takeBook(reader &r, book _book)
    {
        book b("","");
        if(_book.getName() != "" && _book.getAuthor() != "")
            b = searchByNameAndAuthor(_book.getName(), _book.getAuthor());
        if (_book.getName() == "" && _book.getAuthor() != "")
            b = searchByAuthor(_book.getAuthor());
        if (_book.getName() != "" && _book.getAuthor() == "")
            b = searchByName(_book.getName());
        if (b.getName() != "" && b.getAuthor() != "")
            r.pickUpBook(b);
    }

    void printLibrary()
    {
     print();
    }
};



int main() {
    book A("The Great Gatsby", "F. Scott Fitzgerald");
    book B("Moby Dick", "Herman Melville");
    book C("War and Peace", "Leo Tolstoy");
    book D("Lolita", "Vladimir Nabokov");
    book E("Hamlet", "William Shakespeare");

    vector<book> books = {A, B, C, D, E};

    librarian librarian(books);
    reader reader;

    librarian.printLibrary();
    reader.print();

    librarian.takeBook(reader, reader.pickUpBook("Moby Dick", ""));
    librarian.takeBook(reader, reader.pickUpBook("", "Leo Tolstoy"));
    librarian.takeBook(reader, reader.pickUpBook("Lolita", "Vladimir Nabokov"));
    book F("Name", "Author");
    librarian.putBook(F);

    librarian.printLibrary();
    reader.print();

    librarian.putBook(reader.returnBook("Lolita", "Vladimir Nabokov"));
    librarian.putBook(reader.returnBook("War and Peace", "Leo Tolstoy"));

    librarian.printLibrary();
    reader.print();

    return 0;
}
