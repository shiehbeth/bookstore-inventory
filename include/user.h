#ifndef USER_H
#define USER_H

// Node of the linkedlist
typedef struct book {
    char bookTitle[256];
    char bookAuthor[50];
    int pubYear;
    char ISBN[20];
    int rating;
    struct book* nextBook;
} book;

// struct of linkedlist
typedef struct LinkedList_t {
    book *head;
    book *tail;
    int size;
    int max;
}LinkedList;

// struct of User
typedef struct User_t {
    char ID[20];
    char name[20];
    book **historyBook;
    LinkedList *TopFiveFavoriateBooks;
    LinkedList *readingList;
} User;

// methods for books 
book* createBook(char* title, char* author, int year, char *isbn, int rating);
void freeBooks(book* head);

// methods for the linkedlist
void displayBooks(LinkedList *bookList);
void addBook(LinkedList *history, book *newBook);
int lenOfbooks(LinkedList *booklist);
void memoryHandler(LinkedList *bookList);
void insertByRating(LinkedList *booklist, book* newBook);
void updateList(LinkedList *booklist);

#endif
