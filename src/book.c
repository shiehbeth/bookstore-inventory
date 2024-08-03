# include "../include/header.h"

const int MAX_CHAR_LENGTH = 50;

book* createBook(char* title, char* author, int year, char *isbn, int rating) {
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
    strcpy(node->ISBN, isbn);
    node->rating = rating;
    node->nextBook = NULL;
    // node->prevBook = NULL;
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


