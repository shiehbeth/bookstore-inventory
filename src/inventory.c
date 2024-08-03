# include "../include/header.h"

void saveBookToReadlist(LinkedList *readlist, book **tmpbooks, int index) {
    book *newBook = createBook(tmpbooks[index]->bookAuthor, tmpbooks[index]->bookTitle, tmpbooks[index]->pubYear, tmpbooks[index]->ISBN, 0);
    addBook(readlist, newBook);
}

book **searchBy(char *keyword, char *value, int *size) {
    MYSQL *con = mysql_init(NULL);

    if (con == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        exit(1);
    }

    if (mysql_real_connect(con, "localhost", "root", "Shirley*!(*!!",
            "BOOKDB", 3306, NULL, 0) == NULL) {
        finish_with_error(con);
    }
    printf("Connected to the MySQL database successfully.\n"); //771074670
    char query[256];
    snprintf(query, sizeof(query), 
            "SELECT * FROM books WHERE %s = '%s'",
            keyword, value);
    printf("%s\n", query);
    if (mysql_query(con, query)) {
        finish_with_error(con);
    }
    MYSQL_RES *res = mysql_store_result(con);
    int count = mysql_num_rows(res);
    book **tmpBooks = malloc(sizeof(book *) * count);
    int index = 0;
    // MYSQL_ROW bookinfo = mysql_fetch_row(res);
    if (res == NULL) {
        finish_with_error(con);
    } else {
        MYSQL_ROW bookinfo = NULL;
        int count = 1;
        while ((bookinfo = mysql_fetch_row(res))) {
            int year = convertToInt(bookinfo[3]);
            book *newBook = createBook(bookinfo[1],bookinfo[2], year, bookinfo[0],0);
            tmpBooks[index++] = newBook;
            
            printf("%d %s %s %s %s \n", count++, bookinfo[1],bookinfo[2], bookinfo[3], bookinfo[0]);
        }
        *size = count - 1;
        // display(tmpBooks, 1);
    }

    mysql_free_result(res);
    mysql_close(con);
    return tmpBooks;
}

void inventorySearch(User *user) {
    book **tmpBookShelf = NULL;
    int size = 0;
    printf("Which key word would like to use? ");
    char inputStr[20];
    scanf("%s", inputStr);
    toLowercase(inputStr);
    if (strcmp(inputStr, "isbn") == 0) {
        char inputISBN[20];
        printf("What ISBN is? ");
        scanf("%s", inputISBN);
        tmpBookShelf = searchBy("ISBN", inputISBN, &size);
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
        tmpBookShelf = searchBy("Book_Title", inputTitle, &size);
        
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
        tmpBookShelf = searchBy("Book_Author", inputAuthor, &size);
    } else {
        printf("Wrong input string\n");
        exit(1);
    }
    printf("Enter index of the number to save book to the readlist, -1 to quit\n");
    //
    int indexOfBook;
    scanf("%d", &indexOfBook);
    HashSet* set = createHashSet(10);
    while (indexOfBook > 0 && indexOfBook <= size) {
        if (contains(set, indexOfBook) == 0) {
            saveBookToReadlist(user->readingList, tmpBookShelf,indexOfBook - 1);
            addElementToSet(set, indexOfBook);
        } else {
            printf("The book already in your reading list, CAN NOT ADD\n");
        }
        printf("Please enter another index to add a book to reading list, enter -1 to quit.\n");
        scanf("%d", &indexOfBook);
    }
    if (tmpBookShelf != NULL)
        freeHistoryBooks(tmpBookShelf, size);
    freeHashSet(set);
    // int sizeOfTmpBookShelf = sizeof(tmpBookShelf) / sizeof(book);
    // printf("The size of the books list%d\n", sizeOfTmpBookShelf);
    // if (indexOfBook <= sizeOfTepBookShelf)
    // displayBooks(user->readingList);

}

// int main(void) {
//     search();
// }
