#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <mysql/mysql.h>
# include <stdbool.h>
# include <string.h>
#include "../include/book.h"

// gcc -Wall -Wextra  -std=c99 -pedantic -fsanitize=address -g -lmysqlclient retrieveData.c  
int const MAXLEN = 50;

void finish_with_error(MYSQL *con) {
  fprintf(stderr, "%s\n", mysql_error(con));
  mysql_close(con);
  exit(1);
}

int retrieve() {
    MYSQL *con = mysql_init(NULL);

    if (con == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        exit(1);
    }

    if (mysql_real_connect(con, "localhost", "root", "xiaoxueFang811819",
            "BOOKDB", 3306, NULL, 0) == NULL) {
        finish_with_error(con);
    }
    printf("Connected to the MySQL database successfully.\n");
  

    if (mysql_query(con, "SELECT * FROM Books limit 5")) {
        finish_with_error(con);
    }

    MYSQL_RES *result = mysql_store_result(con);

    if (result == NULL) {
        finish_with_error(con);
    }

    int num_fields = mysql_num_fields(result); 

    MYSQL_ROW row;
    
    while ((row = mysql_fetch_row(result))) {

        for(int i = 0; i < num_fields; i++) {
        printf("%s ", row[i] ? row[i] : "NULL");
        }
        printf("\n");
    }

    mysql_free_result(result);
    mysql_close(con);

    exit(0);
}


void printWelcomeInfo() {
    printf("Welcome Beth && Shirley Book Management System\n");
    printf("Please enter an operation: \n");
    printf("Add: find a book in the inventory.\n");
    printf("Show: display all books in your personal inventory.\n");
    printf("Search: search a book is in your personal inventory.\n");
    printf("Done: quit the book management system.\n");
}

void toLowercase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower((unsigned char)str[i]);
    }
}


int main (void) {
    bool done = false;
    char inputStr[MAXLEN];
    // search
    printWelcomeInfo();
    retrieve();
    // loadingUserInfo();
    while (!done) {
        printf("What would you like to do?\n");
        scanf("%s", inputStr);
        toLowercase(inputStr);
        if (strcmp(inputStr, "search") == 0) {
            printf("search\n");
        } else if (strcmp(inputStr, "add") == 0) {
            printf("add");
        } else if (strcmp(inputStr, "show") == 0) {
            printf("show");
        } else if (strcmp(inputStr, "done") == 0) {
            done = true;
        } else {
            printf("Invalid Operation. Please try again.\n");
        }
    }
    return 0;
}
