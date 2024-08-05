# include "../include/header.h"

// save a book to the reading list
void saveBookToReadlist(LinkedList *readlist, book *tmpbooks) {
    // create a new book 
    book *newBook = createBook(tmpbooks->bookAuthor, tmpbooks->bookTitle, tmpbooks->pubYear, tmpbooks->ISBN, 0);
    // add book the the readlist
    addBook(readlist, newBook);
}

// searchby method with create a query based on the keyword and the value to retrieve the data from the database
book **searchBy(char *keyword, char *value, int *size) {
    // Initialize the connect with mysql
    MYSQL *con = mysql_init(NULL);

    // Error Handler
    if (con == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        exit(1);
    }

    // connect with mysql
    if (mysql_real_connect(con, "localhost", "root", "Shirley*!(*!!",
            "BOOKDB", 3306, NULL, 0) == NULL) {
        finish_with_error(con);
    }
    printf("Connected to the MySQL database successfully.\n");
    // create a query
    char query[256];
    snprintf(query, sizeof(query), 
            "SELECT * FROM books WHERE %s = '%s'",
            keyword, value);
    printf("%s\n", query);
    if (mysql_query(con, query)) {
        finish_with_error(con);
    }
    // Retrieve the result by using the query
    MYSQL_RES *res = mysql_store_result(con);
    int count = mysql_num_rows(res);
    book **tmpBooks = malloc(sizeof(book *) * count);
    int index = 0;
    if (res == NULL) {
        finish_with_error(con);
    } else {
        MYSQL_ROW bookinfo = NULL;
        int count = 1;
        while ((bookinfo = mysql_fetch_row(res))) {
            // Iterate all result and save it to an array of books
            int year = convertToInt(bookinfo[3]);
            book *newBook = createBook(bookinfo[1],bookinfo[2], year, bookinfo[0],0);
            tmpBooks[index++] = newBook;
            printf("%d %s %s %s %s \n", count++, bookinfo[1],bookinfo[2], bookinfo[3], bookinfo[0]);
        }
        *size = count - 1;
    }
    // free the res and close the connect
    mysql_free_result(res);
    mysql_close(con);
    return tmpBooks;
}

// Handler all search in the inventory
void inventorySearch(User *user) {
    book **tmpBookShelf = NULL;
    int size = 0;
    printf("Which key word would like to use? ");
    char inputStr[20];
    scanf("%s", inputStr);
    toLowercase(inputStr);
    // handle search by isbn
    if (strcmp(inputStr, "isbn") == 0) {
        char inputISBN[20];
        printf("What ISBN is? ");
        scanf("%s", inputISBN);
        tmpBookShelf = searchBy("ISBN", inputISBN, &size);
    }
    // handle search by title
    else if (strcmp(inputStr, "title") == 0) {
        char inputTitle[256];
        printf("What title is?");
        getchar(); // get rid of the white spaces
        printf("Which author do you want to search for? ");
        if (fgets(inputTitle, sizeof(inputTitle), stdin)) {
        // Remove the newline character if present
            size_t len = strlen(inputTitle);
            if (len > 0 && inputTitle[len - 1] == '\n') {
                inputTitle[len - 1] = '\0';
            }
        }
        tmpBookShelf = searchBy("Book_Title", inputTitle, &size);
    }
    // handle search by author
    else if (strcmp(inputStr, "author") == 0) {
        char inputAuthor[50]; // testcase:  Mark Salzman
        getchar(); // get rid of the white spaces
        printf("Which author do you want to search for? ");
        if (fgets(inputAuthor, sizeof(inputAuthor), stdin)) {
            // Remove the newline character if present
            size_t len = strlen(inputAuthor);
            if (len > 0 && inputAuthor[len - 1] == '\n') {
                inputAuthor[len - 1] = '\0';
            }
        }
        tmpBookShelf = searchBy("Book_Author", inputAuthor, &size);
    } else {
        printf("Wrong input string\n");
        exit(1);
    }
    printf("Enter index of the number to save book to the readlist, -1 to quit\n");
    int indexOfBook;
    scanf("%d", &indexOfBook);
    // create a hashset uses for avoiding the duplication in the readinglist
    HashSet* set = createHashSet(user->readingList);
    while (indexOfBook > 0 && indexOfBook <= size) {
        if (containsElement(set, tmpBookShelf[indexOfBook - 1]->ISBN) == 0) {
            saveBookToReadlist(user->readingList, tmpBookShelf[indexOfBook - 1]);
            addElement(set, tmpBookShelf[indexOfBook - 1]->ISBN);
        } else {
            printf("The book already in your reading list, CAN NOT ADD\n");
        }
        printf("Please enter another index to add a book to reading list, enter -1 to quit.\n");
        scanf("%d", &indexOfBook);
    }
    // Memory handler
    if (tmpBookShelf != NULL)
        freeHistoryBooks(tmpBookShelf, size);
    freeHashSet(set);
}
