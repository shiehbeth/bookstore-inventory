#ifndef BOOKQUEUE_H
#define BOOKQUEUE_H
#include "book.h"

typedef struct bookQueue {
    book* front;
    book* rear;
    int size;
} queue;

queue* create_queue();
book* addBookToQueue(queue*q, book* b);
book* removeBookFromQueue(queue* q);
void free_queue(queue* q);

#endif
