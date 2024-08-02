#ifndef USER_H
#define USER_H
// #include "bookQueue.h"
// #include "DLL.h"
// #include "const.h"
# include "book.h"
# include "linkedList.h"

// typedef struct user_struct {
//     char firstName[MAX_CHAR_LENGTH];
//     char lastName[MAX_CHAR_LENGTH];
//     int userID;
//     queue* wishList;
//     DLL* booksRead;
// } user;


typedef struct User_t {
    char ID[20];
    char name[20];
    book **historyBook;
    LinkedList *TopFiveFavoriateBooks;
    LinkedList *readingList;
} User;

#endif
