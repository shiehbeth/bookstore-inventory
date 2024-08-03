# include "../include/header.h"

// gcc -Wall -Wextra  -std=c99 -pedantic -fsanitize=address -g -lmysqlclient retrieveData.c  
extern int rowCount;

int convertToInt(char str[]) {
    int digit = 1;
    int num = 0;
    int i = strlen(str) - 1;
    while (i >= 0) {
        num += digit * ((int)(str[i] - '0'));
        digit *= 10;
        i--;
    }
    return num;
}

void finish_with_error(MYSQL *con) {
  fprintf(stderr, "%s\n", mysql_error(con));
  mysql_close(con);
  exit(1);
}

void display(book **historyBooks, int rowCount) {
    for (int i = 0; i < rowCount; ++i) {
        printf("ISBN: %-15s Title: %-50s\n", historyBooks[i]->ISBN, historyBooks[i]->bookTitle);
        printf("Author: %-25s Rating: %-49d\n" ,historyBooks[i]->bookAuthor, historyBooks[i]->rating);
        printf("---------------------------------------------------------------------\n");
    }
}


book **retrieveFakeUserInfo(LinkedList *top5Books) {
    MYSQL *con = mysql_init(NULL);

    if (con == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        exit(1);
    }

    if (mysql_real_connect(con, "localhost", "root", "Shirley*!(*!!",
            "BOOKDB", 3306, NULL, 0) == NULL) {
        finish_with_error(con);
    }
    printf("Connected to the MySQL database successfully.\n");
    

    if (mysql_query(con, "SELECT ISBN, book_rating FROM rating WHERE user_id = 276925")) {
        finish_with_error(con);
    }
    
    MYSQL_RES *result = mysql_store_result(con);

    if (result == NULL) {
        finish_with_error(con);
    }

    rowCount = mysql_num_rows(result);
    book **historyBooks = malloc(sizeof(book *) * rowCount);
    int rowIndex = 0;
    MYSQL_ROW row;
    while ((row = mysql_fetch_row(result))) {
        MYSQL_RES *res = NULL;
        if (row[0] != NULL){
            char query[256]; 

            // Construct the query
            snprintf(query, sizeof(query), 
            "SELECT ISBN, Book_Title, Book_Author, Year_Of_Publication FROM books WHERE ISBN = '%s'",
            row[0]);
            // Execute the query
            if (mysql_query(con, query)) {
                finish_with_error(con);
            }
            res = mysql_store_result(con);
            MYSQL_ROW bookinfo = mysql_fetch_row(res);
            if (res == NULL) {
                finish_with_error(con);
            } else {
                int year = convertToInt(bookinfo[3]);
                int rating = convertToInt(row[1]);
                book *newBook = createBook(bookinfo[1],bookinfo[2], year, bookinfo[0],rating);
                historyBooks[rowIndex++] = newBook;
                if (rating > 0) {
                    insertByRating(top5Books, historyBooks[rowIndex - 1]);
                }
            }
        }
        if (res != NULL){
            mysql_free_result(res);
        }
        
    }
    updateList(top5Books);
    mysql_free_result(result);
    mysql_close(con);
    return historyBooks;
}

void freeHistoryBooks(book **historyBooks, int rowCount) {
    for (int i = 0; i < rowCount; ++i) {
        free(historyBooks[i]);
    }
    free(historyBooks);
}

// target user: id : 276925
void printWelcomeInfo() {
    printf("**********************************************************\n");
    printf("*                                                        *\n");
    printf("*            Welcome to the Beth & Shirley Book          *\n");
    printf("*                     Management System!                 *\n");
    printf("*                                                        *\n");
    printf("**********************************************************\n");
    printf("Please enter an operation:                                \n");
    printf(" - Add:    Find a book in the inventory.                  \n");
    printf(" - Show:   Display all books in your personal inventory.  \n");
    printf(" - Search:                                                \n");
    printf("      -1. Book InventorySearch                            \n");
    printf("      -2. Personal Inventory                              \n");
    printf(" - Done:   Quit the book management system.               \n");
    printf("**********************************************************\n");
    printf("*               Happy Reading & Managing!                *\n");
    printf("**********************************************************\n");
}





void toLowercase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower((unsigned char)str[i]);
    }
}

LinkedList *initLinkedList() {
    LinkedList *Top5Books = (LinkedList *)malloc(sizeof(LinkedList));
    Top5Books->head = NULL;
    Top5Books->tail = NULL;
    Top5Books->max = 5;
    Top5Books->size = 0;
    return Top5Books;
}

LinkedList *initReadList() {
    LinkedList *readList = (LinkedList *)malloc(sizeof(LinkedList));
    readList->head = NULL;
    readList->tail = NULL;
    readList->max = 10;
    readList->size = 0;
    return readList;
}

User *initUser() {
    User *user = (User *)malloc(sizeof(User));
    strcpy(user->ID, "276925");
    strcpy(user->name, "Faked User");
    user->readingList = initReadList();
    user->TopFiveFavoriateBooks = initLinkedList();
    user->historyBook = retrieveFakeUserInfo(user->TopFiveFavoriateBooks);
    return user;
}

void show(User *user) {
    printf("************************************************************************\n");
    printf("*                             Hello %s!                        *\n", user->name);
    printf("************************************************************************\n");
     printf("=============================HISTORY BOOKS=============================\n");
    display(user->historyBook, rowCount);
    printf("==============================TOP 5 BOOKS===============================\n");
    displayBooks(user->TopFiveFavoriateBooks);
    printf("==========================Current Reading list==========================\n");
    displayBooks(user->readingList);
    printf("========================================================================\n\n");

}
