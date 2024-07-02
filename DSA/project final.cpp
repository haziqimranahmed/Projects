#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;

struct Book
{
    string title;
    string author;
    int ISBN;
};

struct BinarySearchTree
{
    Book book;
    BinarySearchTree *left;
    BinarySearchTree *right;
};

BinarySearchTree *root;

//Function to create a new node
BinarySearchTree *CreateNewNode(Book book)
{
    BinarySearchTree *temp = new BinarySearchTree;
    temp->book = book;
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}

//Function to insert a book into the tree
BinarySearchTree *InsertBook(Book book, BinarySearchTree *node)
{
    if (node == NULL)
    {
        node = CreateNewNode(book);
    }
    else if (book.ISBN < node->book.ISBN)
    {
        node->left = InsertBook(book, node->left);
    }
    else if (book.ISBN > node->book.ISBN)
    {
        node->right = InsertBook(book, node->right);
    }
    return node;
}

//Function to delete a book from the tree
BinarySearchTree *DeleteBook(int ISBN, BinarySearchTree *node)
{
    if (node == NULL)
    {
        return node;
    }
    else if (ISBN < node->book.ISBN)
    {
        node->left = DeleteBook(ISBN, node->left);
    }
    else if (ISBN > node->book.ISBN)
    {
        node->right = DeleteBook(ISBN, node->right);
    }
    else
    {
        //No Children
        if (node->left == NULL && node->right == NULL)
        {
            delete node;
            node = NULL;
        }
        //One Child
        else if (node->left == NULL)
        {
            BinarySearchTree *temp = node;
            node = node->right;
            delete temp;
        }
        else if (node->right == NULL)
        {
            BinarySearchTree *temp = node;
            node = node->left;
            delete temp;
        }
        //Two Children
        else
        {
            BinarySearchTree *temp = node->right;
            while (temp->left != NULL)
            {
                temp = temp->left;
            }
            node->book = temp->book;
            node->right = DeleteBook(temp->book.ISBN, node->right);
        }
    }
    return node;
}

//Function to search for a book in the tree
bool SearchBook(int ISBN, BinarySearchTree *node)
{
    if (node == NULL)
    {
        return false;
    }
    else if (ISBN < node->book.ISBN)
    {
        return SearchBook(ISBN, node->left);
    }
    else if (ISBN > node->book.ISBN)
    {
        return SearchBook(ISBN, node->right);
    }
    else
    {
        return true;
    }
}

//Function to list all books in the tree
void ListAllBooks(BinarySearchTree *node)
{
    if (node == NULL)
    {
        return;
    }
    ListAllBooks(node->left);
    cout << "Title: " << node->book.title << endl;
    cout << "Author: " << node->book.author << endl;
    cout << "ISBN: " << node->book.ISBN << endl;
    ListAllBooks(node->right);
}

//Function to list all books by an author
void ListAllByAuthor(string author, BinarySearchTree *node)
{
    if (node == NULL)
    {
        return;
    }
    ListAllByAuthor(author, node->left);
    if (node->book.author == author)
    {
        cout << "Title: " << node->book.title << endl;
        cout << "Author: " << node->book.author << endl;
        cout << "ISBN: " << node->book.ISBN << endl;
    }
    ListAllByAuthor(author, node->right);
}

int main()
{
    int userChoice;

    //Menu to select user action
    do
    {
        cout<<"\t\t<<=========================>>\n\t\t>>LIBRARY MANAGEMENT SYSTEM<< \n\t\t<<=========================>>"<<endl;
        cout << "1. Add a book" << endl;
        cout << "2. Delete a book" << endl;
        cout << "3. Search for a book" << endl;
        cout << "4. List all books" << endl;
        cout << "5. List all books by an author" << endl;
        cout << "6. Exit" << endl;
        cout << "Please enter your choice: ";
        cin >> userChoice;

        switch (userChoice)
        {
        case 1:
        {
            Book book;
            cout << "Enter book title: ";
            cin.ignore();
            getline(cin, book.title);
            cout << "Enter book author: ";
            getline(cin, book.author);
            cout << "Enter ISBN: ";
            cin >> book.ISBN;

            root = InsertBook(book, root);
            cout << "Book added successfully!" << endl;
            break;
        }
        case 2:
        {
            cout << "1. Delete by title" << endl;
            cout << "2. Delete by ISBN" << endl;
            int deleteChoice;
            cout << "Please enter your choice: ";
            cin >> deleteChoice;

            if (deleteChoice == 1)
            {
                string title;
                cout << "Enter book title: ";
                cin.ignore();
                getline(cin, title);
            }
            else if (deleteChoice == 2)
            {
                int ISBN;
                cout << "Enter ISBN: ";
                cin >> ISBN;
                root = DeleteBook(ISBN, root);
                cout << "Book deleted successfully!" << endl;
            }
            break;
        }
        case 3:
        {
            int ISBN;
            cout << "Enter ISBN: ";
            cin >> ISBN;
            if (SearchBook(ISBN, root))
            {
                cout << "Book found!" << endl;
            }
            else
            {
                cout << "Book not found!" << endl;
            }
            break;
        }
        case 4:
        {
            ListAllBooks(root);
            break;
        }
        case 5:
        {
            string author;
            cout << "Enter author: ";
            cin.ignore();
            getline(cin, author);
            ListAllByAuthor(author, root);
            break;
        }
        case 6:
        {
            exit(0);
            break;
        }
        default:
            cout << "Invalid input!" << endl;
            break;
        }
    } while (true);
}
