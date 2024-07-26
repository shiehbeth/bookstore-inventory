#ifndef BOOK_H
#define BOOK_H
#include "const.h"

typedef struct book {
    char bookTitle[50];
    char bookAuthor[50];
    int pubYear;
    long ISBN;
    struct book* nextBook;
    struct book* prevBook;
} book;

book* createBook(char* title, char* author, int year, long isbn);
void freeBooks(book* head);

#endif
