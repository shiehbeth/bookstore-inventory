#ifndef BOOK_H
#define BOOK_H
#include "const.h"

typedef struct book {
    char bookTitle[256];
    char bookAuthor[50];
    int pubYear;
    char ISBN[20];
    int rating;
    struct book* nextBook;
    // struct book* prevBook;
} book;

book* createBook(char* title, char* author, int year, char *isbn, int rating);
void freeBooks(book* head);

#endif
