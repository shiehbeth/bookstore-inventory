#ifndef BOOKQUEUE_H
#define BOOKQUEUE_H

#include "book.h"

typedef struct queue {
    book* front;
    book* rear;
    int size;
} queue;

queue* create_queue();
void addBookToQueue(queue* q, book* b);
book* removeBookFromQueue(queue* q);
void free_queue(queue* q);

#endif
