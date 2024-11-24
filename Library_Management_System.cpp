#include<bits/stdc++.h>
using namespace std;

class Book
{
    int bookID;
    string title, author;
    bool isAvailable;

public:
    Book(int id, string t, string a) : bookID(id), title(t), author(a), isAvailable(true) {}
    int getBookID() const { return bookID; }
    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    bool getAvailability() const { return isAvailable; }
    void setAvailability(bool status) { isAvailable = status; }
    void display() const
    {
        cout << "ID: " << bookID << ", Title: " << title << ", Author: " << author
             << ", Available: " << (isAvailable ? "Yes" : "No") << endl;
    }
};

class User
{
    int userID, borrowedBookID;
    string name;

public:
    User(int id, string n) : userID(id), name(n), borrowedBookID(-1) {}
    int getUserID() const { return userID; }
    string getName() const { return name; }
    int getBorrowedBookID() const { return borrowedBookID; }
    void borrowBook(int bookID) { borrowedBookID = bookID; }
    void returnBook() { borrowedBookID = -1; }
    void display() const
    {
        cout << "User ID: " << userID << ", Name: " << name;
        if (borrowedBookID == -1)
            cout << ", No books borrowed." << endl;
        else
            cout << ", Borrowed Book ID: " << borrowedBookID << endl;
    }
};

class Library
{
    vector<Book> books;
    vector<User> users;

public:
    void addBook(const Book &book)
    {
        books.push_back(book);
        cout << "Book added successfully.\n";
    }
    void addUser(const User &user)
    {
        users.push_back(user);
        cout << "User added successfully.\n";
    }
    void displayAllBooks() const
    {
        cout << "Displaying all books:\n";
        for (size_t i = 0; i < books.size(); ++i)
        {
            books[i].display();
        }
    }
    void displayAllUsers() const
    {
        cout << "Displaying all users:\n";
        for (size_t i = 0; i < users.size(); ++i)
        {
            users[i].display();
        }
    }
    void borrowBook(int userID, int bookID)
    {
        for (size_t i = 0; i < users.size(); ++i)
        {
            if (users[i].getUserID() == userID)
            {
                for (size_t j = 0; j < books.size(); ++j)
                {
                    if (books[j].getBookID() == bookID && books[j].getAvailability())
                    {
                        books[j].setAvailability(false);
                        users[i].borrowBook(bookID);
                        cout << "Book borrowed successfully.\n";
                        return;
                    }
                }
                cout << "Book not available.\n";
                return;
            }
        }
        cout << "User not found.\n";
    }
    void returnBook(int userID, int bookID)
    {
        for (size_t i = 0; i < users.size(); ++i)
        {
            if (users[i].getUserID() == userID && users[i].getBorrowedBookID() == bookID)
            {
                for (size_t j = 0; j < books.size(); ++j)
                {
                    if (books[j].getBookID() == bookID)
                    {
                        books[j].setAvailability(true);
                        users[i].returnBook();
                        cout << "Book returned successfully.\n";
                        return;
                    }
                }
            }
        }
        cout << "Book return failed.\n";
    }
    void searchBookByID(int bookID) const
    {
        for (size_t i = 0; i < books.size(); ++i)
        {
            if (books[i].getBookID() == bookID)
            {
                books[i].display();
                return;
            }
        }
        cout << "Book not found.\n";
    }
    void searchBookByTitle(const string &title) const
    {
        bool found = false;
        for (size_t i = 0; i < books.size(); ++i)
        {
            if (books[i].getTitle() == title)
            {
                books[i].display();
                found = true;
            }
        }
        if (!found)
            cout << "No books found with the title: " << title << endl;
    }
    void searchBookByAuthor(const string &author) const
    {
        bool found = false;
        for (size_t i = 0; i < books.size(); ++i)
        {
            if (books[i].getAuthor() == author)
            {
                books[i].display();
                found = true;
            }
        }
        if (!found)
            cout << "No books found by the author: " << author << endl;
    }
    void updateBookDetails(int bookID, const string &newTitle, const string &newAuthor)
    {
        for (size_t i = 0; i < books.size(); ++i)
        {
            if (books[i].getBookID() == bookID)
            {
                books[i] = Book(bookID, newTitle, newAuthor); // Assuming book ID is unique
                cout << "Book details updated successfully.\n";
                return;
            }
        }
        cout << "Book not found.\n";
    }
    void deleteBook(int bookID)
    {
        for (size_t i = 0; i < books.size(); ++i)
        {
            if (books[i].getBookID() == bookID)
            {
                books.erase(books.begin() + i);
                cout << "Book deleted successfully.\n";
                return;
            }
        }
        cout << "Book not found.\n";
    }
    void deleteUser(int userID)
    {
        for (size_t i = 0; i < users.size(); ++i)
        {
            if (users[i].getUserID() == userID)
            {
                users.erase(users.begin() + i);
                cout << "User deleted successfully.\n";
                return;
            }
        }
        cout << "User not found.\n";
    }
};

int main()
{
    Library library;
    library.addBook(Book(1, "The Great Gatsby", "F. Scott Fitzgerald"));
    library.addBook(Book(2, "1984", "George Orwell"));
    library.addUser(User(1, "Alice"));
    library.addUser(User(2, "Bob"));

    int choice = 0;
    while (choice != 8)
    {
        cout << "\nLibrary Management System\n";
        cout << "1. Display all books\n2. Display all users\n3. Borrow a book\n4. Return a book\n";
        cout << "5. Search for a book\n6. Update book details\n7. Delete a book/user\n8. Exit\nEnter your choice: ";
        cin >> choice;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        int userID, bookID, deleteID;
        string title, author, newTitle, newAuthor;
        switch (choice)
        {
        case 1:
            library.displayAllBooks();
            break;
        case 2:
            library.displayAllUsers();
            break;
        case 3:
            cout << "Enter user ID: ";
            cin >> userID;
            cout << "Enter book ID: ";
            cin >> bookID;
            library.borrowBook(userID, bookID);
            break;
        case 4:
            cout << "Enter user ID: ";
            cin >> userID;
            cout << "Enter book ID: ";
            cin >> bookID;
            library.returnBook(userID, bookID);
            break;
        case 5:
            cout << "Search by (1) ID (2) Title (3) Author: ";
            int searchChoice;
            cin >> searchChoice;
            if (searchChoice == 1)
            {
                cout << "Enter book ID: ";
                cin >> bookID;
                library.searchBookByID(bookID);
            }
            else if (searchChoice == 2)
            {
                cout << "Enter book title: ";
                cin.ignore(); // Ignore newline character from previous input
                getline(cin, title);
                library.searchBookByTitle(title);
            }
            else if (searchChoice == 3)
            {
                cout << "Enter author name: ";
                cin.ignore(); // Ignore newline character from previous input
                getline(cin, author);
                library.searchBookByAuthor(author);
            }
            else
            {
                cout << "Invalid search option.\n";
            }
            break;
        case 6:
            cout << "Enter book ID to update: ";
            cin >> bookID;
            cout << "Enter new title: ";
            cin.ignore();
            getline(cin, newTitle);
            cout << "Enter new author: ";
            getline(cin, newAuthor);
            library.updateBookDetails(bookID, newTitle, newAuthor);
            break;
        case 7:
            cout << "Delete (1) Book (2) User: ";
            int deleteChoice;
            cin >> deleteChoice;
            if (deleteChoice == 1)
            {
                cout << "Enter book ID to delete: ";
                cin >> deleteID;
                library.deleteBook(deleteID);
            }
            else if (deleteChoice == 2)
            {
                cout << "Enter user ID to delete: ";
                cin >> deleteID;
                library.deleteUser(deleteID);
            }
            else
            {
                cout << "Invalid delete option.\n";
            }
            break;
        case 8:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice.\n";
        }
    }

    return 0;
}
