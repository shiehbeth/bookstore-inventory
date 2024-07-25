#ifndef BOOK_H
#define BOOK_H

const int MAX_CHAR_LENGTH = 50;

typedef struct book_struct {
    char bookTitle[MAX_CHAR_LENGTH];
    char bookAuthor[MAX_CHAR_LENGTH];
    int pubYear;
    int ISBN;
    book* nextBook;
} book;

book* createBook(char* title, char* author, int year, int isbn);
void freeBooks(book* head);

#endif
