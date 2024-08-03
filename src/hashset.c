# include "../include/header.h"

unsigned int hash(int key, int size) {
    return key % size;
}

HashSet* createHashSet(int size) {
    HashSet* set = (HashSet*)malloc(sizeof(HashSet));
    set->table = (Node**)malloc(sizeof(Node*) * size);
    for (int i = 0; i < size; i++) {
        set->table[i] = NULL;
    }
    set->size = size;
    return set;
}

void addElementToSet(HashSet* set, int key) {
    unsigned int hashValue = hash(key, set->size);
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = key;
    newNode->next = set->table[hashValue];
    set->table[hashValue] = newNode;
}

int contains(HashSet* set, int key) {
    unsigned int hashValue = hash(key, set->size);
    Node* node = set->table[hashValue];
    while (node != NULL) {
        if (node->data == key) {
            return 1; // Found
        }
        node = node->next;
    }
    return 0; // Not found
}


void freeHashSet(HashSet* set) {
    for (int i = 0; i < set->size; i++) {
        Node* node = set->table[i];
        while (node != NULL) {
            Node* tmp = node;
            node = node->next;
            free(tmp);
        }
    }
    free(set->table);
    free(set);
}
