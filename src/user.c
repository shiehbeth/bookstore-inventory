# include <stdlib.h>
# include <stdio.h>
# include "book.h"
# include "linkedlist.h"

const int TOPFIVE = 5;
typedef struct User_t {
    int ID;
    char *name;
    book **historyBook;
    LinkedList *TopFiveFavoriateBooks;
    LinkedList *readingList;
} User;