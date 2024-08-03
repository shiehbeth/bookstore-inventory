# ifndef HASH_SET_H
# define HASH_SET_H

// Define a node in the linked list
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Define the HashSet structure
typedef struct {
    Node** table;
    int size;
} HashSet;

unsigned int hash(int key, int size);
HashSet* createHashSet(int size);
void addElementToSet(HashSet* set, int key);
int contains(HashSet* set, int key);
void freeHashSet(HashSet* set);

# endif
