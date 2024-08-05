# include "../include/header.h"

int count = 0;

// addBook method definition
void addBook(LinkedList *history, book *newBook) {
    // if linked list is empty add book
    if (history == NULL) {
        history = (LinkedList *)malloc(sizeof(LinkedList));
        history->head = newBook;
        history->tail = newBook;
        history->size = 1;
        history->max = 5;
        // if head is empty add book
    } else if (history->head == NULL) {
        history->head = newBook;
        history->tail = newBook;
        history->size = 1;
        history->max = 5;
        // if not empty
    } else {
        history->tail->nextBook = newBook;
        //  newBook->prevBook = NULL;
        history->tail = newBook;
        history->size++;
    }
}

// displayBook method definition
void displayBooks(LinkedList *bookList) {
    // while bookList is not null
    if (bookList != NULL) {
        book *curNode = bookList->head;

       // display the books
        while (curNode != NULL) {
            printf("ISBN: %-15s Title: %-50s\n", curNode->ISBN, curNode->bookTitle);
            printf("Author: %-25s Rating: %-49d\n" ,curNode->bookAuthor, curNode->rating);
            printf("----------------------------------------------------------------------\n");
            curNode = curNode->nextBook;
        }
    // if empty, print empty message
    } else {
        printf("There is nothing in the book shelf\n");
    }
}

// lenOfbooks method definition
int lenOfbooks(LinkedList *booklist) {
    int i = 0;
    // traverse the linked list
    if (booklist != NULL) {
        book *curNode = booklist->head;
        while (curNode != NULL) {
            curNode = curNode->nextBook;
        }
        // increment count
        i++;
    }
    return i;
}


// updateList method definition
void updateList(LinkedList *booklist) {
    // initialize variables
    book *curNode = booklist->head;
    book *tmp = NULL;
    int i = 0;
    while (booklist->size > booklist->max && i < booklist->max) {
        tmp = curNode;
        curNode = curNode->nextBook;
        i++;
    }
    tmp->nextBook = NULL;
    booklist->tail = tmp;
}

// insertByRating method
void insertByRating(LinkedList *booklist, book* newBook) {
    // check for null booklist
    if (booklist == NULL) printf("The booklist shouldn't be NULL.");
    // initialize variables
    book *curNode = booklist->head;
    book *tmp = NULL;
    int rating = newBook->rating;

    // check if booklist is empty
    if (curNode == NULL) {
        booklist->head = newBook;
        booklist->tail = newBook;
        booklist->size = 1;
        booklist->max = 5;
        // check ratings and update list accordingly
    } else {
        if (booklist->head->rating <= rating) {
            newBook->nextBook = booklist->head;
            booklist->head = newBook;
            booklist->size++;
        } else if (booklist->tail->rating >= rating) {
            booklist->tail->nextBook = newBook;
            booklist->tail = newBook;
            booklist->size++;
        } else {
            while (curNode != NULL && curNode->rating > rating) {
                tmp = curNode;
                curNode = curNode->nextBook;
            }
            tmp->nextBook = newBook;
            newBook->nextBook = curNode;
        }
    }
}


// memoryHandler method definition
void memoryHandler(LinkedList *bookList) {
    // initialize variables
    book *curBook = bookList->head;
    book *tmp = NULL;
    // check curBook pointer
    while (curBook != NULL) {
        tmp = curBook;
        curBook = curBook->nextBook;
        free(tmp);
    }
    // free
    free(bookList);
}
