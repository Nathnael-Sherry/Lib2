#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Base class
class Book {
protected:
    string title;
    string author;
    string isbn;
    bool isBorrowed;

public:
    Book(string t, string a, string i) : title(t), author(a), isbn(i), isBorrowed(false) {}

    virtual void display() const {
        cout << "Title: " << title << ", Author: " << author << ", ISBN: " << isbn;
        if (isBorrowed) {
            cout << " (Borrowed)";
        } else {
            cout << " (Available)";
        }
        cout << endl;
    }

    string getTitle() const { return title; }
    bool isAvailable() const { return !isBorrowed; }

    virtual void borrow() {
        if (isBorrowed) {
            cout << "Error: The book '" << title << "' is already borrowed." << endl;
        } else {
            isBorrowed = true;
            cout << "You have successfully borrowed '" << title << "'." << endl;
        }
    }

    virtual void returnBook() {
        if (!isBorrowed) {
            cout << "Error: The book '" << title << "' was not borrowed." << endl;
        } else {
            isBorrowed = false;
            cout << "You have successfully returned '" << title << "'." << endl;
        }
    }
};

// Derived class for EBook
class EBook : public Book {
private:
    string fileSize;

public:
    EBook(string t, string a, string i, string fs) : Book(t, a, i), fileSize(fs) {}

    void display() const override {
        Book::display();
        cout << " (EBook, File Size: " << fileSize << ")" << endl;
    }
};

// Derived class for AudioBook
class AudioBook : public Book {
private:
    int duration; // Duration in minutes

public:
    AudioBook(string t, string a, string i, int d) : Book(t, a, i), duration(d) {}

    void display() const override {
        Book::display();
        cout << " (AudioBook, Duration: " << duration << " mins)" << endl;
    }
};

class Library {
private:
    vector<Book*> books; // Use pointers to base class

public:
    ~Library() {
        for (auto book : books) {
            delete book; // Clean up allocated memory
        }
    }

    void addBook(Book* book) {
        books.push_back(book);
    }

    void borrowBook(const string& title) {
        for (auto& book : books) {
            if (book->getTitle() == title) {
                book->borrow();
                return;
            }
        }
        cout << "Error: Book '" << title << "' not found in the library." << endl;
    }

    void returnBook(const string& title) {
        for (auto& book : books) {
            if (book->getTitle() == title) {
                book->returnBook();
                return;
            }
        }
        cout << "Error: Book '" << title << "' not found in the library." << endl;
    }

    void displayAvailableBooks() const {
        cout << "\nAvailable Books:\n";
        for (const auto& book : books) {
            if (book->isAvailable()) {
                book->display();
            }
        }
    }
};

int main() {
    Library library;

    // Adding some books to the library
    library.addBook(new Book("1984", "George Orwell", "1234567890"));
    library.addBook(new EBook("To Kill a Mockingbird", "Harper Lee", "0987654321", "1.5MB"));
    library.addBook(new AudioBook("The Great Gatsby", "F. Scott Fitzgerald", "1122334455", 300));

    int choice;
    string title;

    do {
        cout << "\nLibrary Book System\n";
        cout << "1. Borrow a book\n";
        cout << "2. Return a book\n";
        cout << "3. Display available books\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter the title of the book to borrow: ";
                cin.ignore();
                getline(cin, title);
                library.borrowBook(title);
                break;
            case 2:
                cout << "Enter the title of the book to return: ";
                cin.ignore();
                getline(cin, title);
                library.returnBook(title);
                break;
            case 3:
                library.displayAvailableBooks();
                break;
            case 4:
                cout << "Exiting the system." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 4);

    return 0;
}
