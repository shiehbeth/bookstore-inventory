# include "../include/book.h"
# include <stdio.h>
# include <stdlib.h>
# include "../include/linkedList.h"

// typedef struct LinkedList_t {
//     book *head;
// }LLT;

void addBook(LinkedList *history, book *newBook) {
    if (history == NULL) {
        history = (LinkedList *)malloc(sizeof(LinkedList));
        history->head = newBook;
        history->tail = newBook;
        history->size = 1;
    } else if (history->head == NULL) {
        history->head = newBook;
        history->tail = newBook;
        history->size = 1;
    }else {
        history->tail->nextBook = newBook;
        //  newBook->prevBook = NULL;
        history->tail = newBook;
        history->size++;
    }
}

void displayBooks(LinkedList *bookList) {
    if (bookList != NULL) {
        book *curNode = bookList->head;
        printf("The history books: \n");
        while (curNode != NULL) {
            printf("ISBN: %-15s Title: %-50s\n", curNode->ISBN, curNode->bookTitle);
            printf("Author: %-25s Rating: %-49d\n" ,curNode->bookAuthor, curNode->rating);
            printf("----------------------------------------------------------------------\n");
            curNode = curNode->nextBook;
        }
        printf("-------------------------------------------------------------------------------\n");
    }
}

int lenOfbooks(LinkedList *booklist) {
    int i = 0;
    if (booklist != NULL) {
        book *curNode = booklist->head;
        while (curNode != NULL) {
            curNode = curNode->nextBook;
        }
        i++;
    }
    return i;
}
void memoryHandler(LinkedList *bookList) {
    book *curBook = bookList->head;
    book *tmp = NULL;
    while (curBook != NULL) {
        tmp = curBook;
        curBook = curBook->nextBook;
        free(tmp);
    }
    free(bookList);
}