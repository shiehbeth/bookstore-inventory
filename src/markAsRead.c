#include "../include/header.h"
extern int rowCount;

// markAsRead method definition
void markAsRead(User *user) {
    char inputISBN[20];
    // get user input for ISBN
    printf("Enter ISBN of the book read: ");
    scanf("%s", inputISBN);

    // initialize pointers
    book* tmp = user->readingList->head;
    book* prev = NULL;

    // traverse LL to find the book
    while(tmp != NULL) {
        if (strcmp(tmp->ISBN, inputISBN) == 0) {
            break;
        }
        prev = tmp;
        tmp = tmp->nextBook;
    }

    // if book is not found in the reading list
    if (tmp == NULL) {
        printf("Book not found in reading list. Cannot be marked as read.\n");
        return;
    }

    // if book is the first book, update head
    if (prev == NULL) {
        user->readingList->head = tmp->nextBook;
    }
    // if not the first book, update prev pointer
    else {
        prev->nextBook = tmp->nextBook;
    }

    // sort history book
    quicksort(user->historyBook, 0, rowCount-1, compareByISBN);
    // search history book
    int index = binarySearchByISBN(user->historyBook, 0, rowCount-1, inputISBN);
    // if book is not already in history book
    if (index == -1) {
        // add book to history book
        user->historyBook[rowCount] = tmp;
        rowCount++;
        printf("Marked book as read. Added to history books.\n");
    }
    // book is already in history book
    else {
        printf("Book has already been marked as read previously.\n");
    }
}
