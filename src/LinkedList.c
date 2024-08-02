# include "../include/book.h"
# include <stdio.h>
# include <stdlib.h>
# include "../include/linkedList.h"

// typedef struct LinkedList_t {
//     book *head;
// }LLT;
int count = 0;
void addBook(LinkedList *history, book *newBook) {
    if (history == NULL) {
        history = (LinkedList *)malloc(sizeof(LinkedList));
        history->head = newBook;
        history->tail = newBook;
        history->size = 1;
        history->max = 5;
    } else if (history->head == NULL) {
        history->head = newBook;
        history->tail = newBook;
        history->size = 1;
        history->max = 5;
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

// void insertFront(LinkedList* booklist, book *newBook) {

// }

void updateList(LinkedList *booklist, book *newBook) {
    printf("Updated\n");
    printf("The %d times, Before: \n", count);
    // displayBooks(booklist);
    book *curNode = booklist->head;
    int i = 0;
    while(i < booklist->size) {
        curNode = curNode->nextBook;
        i++;
    }
    book *tmp = curNode->nextBook;
    curNode->nextBook = NULL;
    booklist->tail = curNode;
    booklist->tail->nextBook = NULL;
    booklist->size--;
    // printf("After: \n");
    // displayBooks(booklist);
}

void insertByRating(LinkedList *booklist, book* newBook) {
    if (booklist == NULL) printf("The booklist shouldn't be NULL.");
    book *curNode = booklist->head;
    book *tmp = NULL;
    int rating = newBook->rating;
    if (curNode == NULL) {
        booklist->head = newBook;
        booklist->tail = newBook;
        booklist->size = 1;
        booklist->max = 5;
    } else {
        if (booklist->head->rating <= rating) {
            // displayBooks(booklist);
            newBook->nextBook = booklist->head;
            booklist->head = newBook;
            booklist->size++;
        } else if (booklist->tail->rating > rating) {
            booklist->tail->nextBook = newBook;
            booklist->tail = newBook;
            booklist->size++;
        } else {
            while (curNode != NULL) {
                tmp = curNode;
                if (curNode->rating < rating) {
                    tmp->nextBook = newBook;
                    newBook->nextBook = curNode;
                    booklist->size++;
                    break;
                } 
                curNode = curNode->nextBook;
            }
        }
    }
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