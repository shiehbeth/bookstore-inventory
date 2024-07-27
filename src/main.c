#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/book.h"
#include "../include/bookQueue.h"
#include "../include/const.h"

int main() {
    // Create a queue
    queue* q = create_queue();

    // Add some books to the queue
    book* book1 = createBook("Book 1", "Author 1", 2001, 12345678);
    addBookToQueue(q, book1);

    book* book2 = createBook("Book2", "Author2", 2014, 2385194);
    addBookToQueue(q, book2);

    // Remove a book from the queue
    book* removedBook = removeBookFromQueue(q);
    printf("Removed book: %s by %s\n", removedBook->bookTitle, removedBook->bookAuthor);
    free(removedBook);

    // Free the queue
    free_queue(q);

    return 0;
}
