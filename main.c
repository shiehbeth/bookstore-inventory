#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/book.h"
#include "include/bookQueue.h"
#include "include/const.h"

int main() {
    // Create a queue
    queue* q = create_queue();

    // Add some books to the queue
    book* book1 = (book*)malloc(sizeof(book));
    strcpy(book1->bookTitle, "Book 1");
    strcpy(book1->bookAuthor, "Author 1");
    book1->pubYear = 2001;
    book1->ISBN = 1234567890;
    book1->nextBook = book1->prevBook = NULL;
    addBookToQueue(q, book1);

    book* book2 = (book*)malloc(sizeof(book));
    strcpy(book2->bookTitle, "Book 2");
    strcpy(book2->bookAuthor, "Author 2");
    book2->pubYear = 2002;
    book2->ISBN = 2345678901;
    book2->nextBook = book2->prevBook = NULL;
    addBookToQueue(q, book2);

    // Remove a book from the queue
    book* removedBook = removeBookFromQueue(q);
    printf("Removed book: %s by %s\n", removedBook->bookTitle, removedBook->bookAuthor);
    free(removedBook);

    // Free the queue
    free_queue(q);

    return 0;
}
