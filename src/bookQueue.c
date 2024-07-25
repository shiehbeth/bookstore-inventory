#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "book.h"
#include "bookqueue.h"

queue* create_queue() {
    queue* q = (queue*)malloc(sizeof(queue));
    if (q == NULL) {
        printf("Memory alloc failed\n");
        exit(1);
    }
    q->front = q->rear = NULL;
    q->size = 0;
    return q;
}

book* addBookToQueue(queue*q, book* b) {
    if (q->size == 10) {
        removeBookFromQueue(q);
    }
    if (q->rear == NULL) {
        q->front = q->rear = b;
    }
    else {
        q->rear->nextBook = b;
        q->rear = b;
    }
    q->size += 1;
}

book* removeBookFromQueue(queue* q) {
    if (q->front == NULL) {
        return NULL;
    }
    book* tmp = q->front;
    q->front = q->front->nextBook;
    if (q->front == NULL) {
        q->rear = NULL;
    }
    q->size -= 1;

    return tmp;
}

void free_queue(queue* q) {
    while (q->front != NULL) {
        book* tmp = dequeue(q);
        free(tmp);
    }
    free(q);
}
