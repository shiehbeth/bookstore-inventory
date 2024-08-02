# include "../include/header.h"

void searchBy(char *keyword, char *value) {
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
    char query[256];
    snprintf(query, sizeof(query), 
            "SELECT * FROM books WHERE %s = '%s'",
            keyword, value);
    printf("%s\n", query);
    if (mysql_query(con, query)) {
        finish_with_error(con);
    }
    MYSQL_RES *res = mysql_store_result(con);
    // int count = mysql_num_fields(res);
    // MYSQL_ROW bookinfo = mysql_fetch_row(res);
    if (res == NULL) {
        finish_with_error(con);
    } else {
        MYSQL_ROW bookinfo = NULL;
        int count = 1;
        while ((bookinfo = mysql_fetch_row(res))) {
            printf("%d %s %s %s %s \n", count++, bookinfo[1],bookinfo[2], bookinfo[3], bookinfo[0]);
        }
    }
    
}

void search() {
    printf("Which key word would like to use? ");
    char inputStr[20];
    scanf("%s", inputStr);
    toLowercase(inputStr);
    if (strcmp(inputStr, "isbn") == 0) {
        char inputISBN[20];
        printf("What ISBN is? ");
        scanf("%s", inputISBN);
        searchBy("ISBN", inputISBN);
    } else if (strcmp(inputStr, "title") == 0) {
        char inputTitle[20];
        printf("What title is?");
        getchar();
        printf("Which author do you want to search for? ");
        if (fgets(inputTitle, sizeof(inputTitle), stdin)) {
        // Remove the newline character if present
            size_t len = strlen(inputTitle);
            if (len > 0 && inputTitle[len - 1] == '\n') {
                inputTitle[len - 1] = '\0';
            }
        }
        searchBy("Book_Title", inputTitle);
    } else if (strcmp(inputStr, "author") == 0) {
        // Mark Salzman
        char inputAuthor[20];
        getchar();
        printf("Which author do you want to search for? ");
        if (fgets(inputAuthor, sizeof(inputAuthor), stdin)) {
        // Remove the newline character if present
        size_t len = strlen(inputAuthor);
        if (len > 0 && inputAuthor[len - 1] == '\n') {
            inputAuthor[len - 1] = '\0';
        }
    }

        // fgets(inputAuthor, 256, stdin);
        // inputAuthor[strlen(inputAuthor)] = '\0';
        searchBy("Book_Author", inputAuthor);
    } else {
        printf("Wrong input string");
    }
}

int main(void) {
    search();
}
