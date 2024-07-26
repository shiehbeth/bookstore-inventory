#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "book.h"
#include "const.h"

const int MAX_CHAR_LENGTH = 50;

book* createBook(char* title, char* author, int year, long isbn) {
    // dynamically allocate memory
    book* node = (book*) malloc(sizeof(book));

    // check that memory allocation worked
    if (node == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    // initialize values and next node
    strcpy(node->bookTitle, title);
    strcpy(node->bookAuthor, author);
    node->pubYear = year;
    node->ISBN = isbn;
    node->nextBook = NULL;
    node->prevBook = NULL;
    return node;
}

void freeBooks(book* head) {
    book* tmp;
    while (head != NULL) {
        tmp = head;
        head = head->nextBook;
        free(tmp);
    }
}
