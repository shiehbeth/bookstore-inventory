# ifndef LINKED_LIST_H
# define LINKED_LIST_H

# include "book.h"
# include <stdio.h>
# include <stdlib.h>

typedef struct LinkedList_t {
    book *head;
    book *tail;
    int size;
    int max;
}LinkedList;

void displayBooks(LinkedList *bookList);
void addBook(LinkedList *history, book *newBook);
int lenOfbooks(LinkedList *booklist);
void memoryHandler(LinkedList *bookList);
void insertByRating(LinkedList *booklist, book* newBook);
void updateList(LinkedList *booklist);

# endif
