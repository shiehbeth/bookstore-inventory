# ifndef HASH_SET_H
# define HASH_SET_H
# include "user.h"

// Define a node in the linked list
typedef struct Node {
    char* data;
    struct Node* next;
} Node;

// Define the HashSet structure
typedef struct {
    Node** table;
    int size;
} HashSet;

unsigned int hash(const char* key, int size);
HashSet* createHashSet(LinkedList *readingList);
void addElement(HashSet* set, const char* key);
int containsElement(HashSet* set, const char* key);
void freeHashSet(HashSet* set);
void removeElement(HashSet* set, const char* key);
# endif
