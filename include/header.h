#ifndef HEADER_H
#define HEADER_H

# include <stdio.h>
# include <stdlib.h>
# include <ctype.h>
# include <mysql/mysql.h>
# include <stdbool.h>
# include <string.h>
# include "user.h"
# include "hashset.h"

// method declaration
int partition(book* input[], int low, int high, int (*compare)(book*, book*));
void quicksort(book* input[], int low, int high, int (*compare)(book*, book*));
void searchPersonal(book* input[], int numBooks);
int binarySearchByTitle(book* input[], int left, int right, char* title);
int binarySearchByAuthor(book* input[], int left, int right, char* author);
int binarySearchByISBN(book* input[], int left, int right, char* isbn);
int compareByTitle(book* a, book* b);
int compareByAuthor(book* a, book* b);
int compareByISBN(book* a, book* b);
void toLowercase(char *str);
void finish_with_error(MYSQL *con);
void inventorySearch(User *user);
int convertToInt(char str[]);
void display(book **historyBooks, int rowCount);
void freeHistoryBooks(book **historyBooks, int rowCount);
User *initUser();
void printWelcomeInfo();
void show(User *user);
void markAsRead(User *user);

#endif
