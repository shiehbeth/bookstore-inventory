# include "../include/header.h"

unsigned int hash(const char* key, int size) {
    unsigned int hash = 0;
    unsigned int i = 0;
    for (; i < strlen(key);i++) {
      hash += key[i];
   }
    return hash % size;
}

void initalHashSet(HashSet *set, LinkedList *readingList) {
    book *curNode = readingList->head;
    while (curNode != NULL) {
        addElement(set, curNode->ISBN);
        curNode = curNode->nextBook;
    }
}

HashSet* createHashSet(LinkedList *readingList) {
    HashSet* set = (HashSet*)malloc(sizeof(HashSet));
    int size = readingList->size + 10;
    set->table = (Node**)malloc(sizeof(Node*) * size);
    for (int i = 0; i < size; i++) {
        set->table[i] = NULL;
    }
    set->size = size;
    initalHashSet(set, readingList);
    return set;
}

void addElement(HashSet* set, const char* key) {
    unsigned int index = hash(key, set->size);
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = (char *)malloc(sizeof(char) * (strlen(key) + 1));
    strcpy(newNode->data, key); 
    newNode->next = set->table[index];
    //set up the head of the set->table[index]
    set->table[index] = newNode;
}

int containsElement(HashSet* set, const char* key) {
    unsigned int index = hash(key, set->size);
    Node* node = set->table[index];
    while (node != NULL) {
        if (strcmp(node->data, key) == 0) {
            return 1; // Found
        }
        node = node->next;
    }
    return 0; // Not found
}

void removeElement(HashSet* set, const char* key) {
    unsigned int index = hash(key, set->size);
    Node* curNode = set->table[index];
    Node* prev = NULL;

    while (curNode != NULL && strcmp(curNode->data, key) != 0) {
        prev = curNode;
        curNode = curNode->next;
    }
    // Key not found
    if (curNode == NULL) return;

     // Node to be deleted is the first node
    if (prev == NULL) {
        set->table[index] = curNode->next;
    } else {
        // update the previous node's next to curNode's next
        prev->next = curNode->next; 
    }
    // Memory handler
    free(curNode->data);
    free(curNode);
}

void freeHashSet(HashSet* set) {
    for (int i = 0; i < set->size; i++) {
        Node* node = set->table[i];
        while (node != NULL) {
            Node* tmp = node;
            node = node->next;
            free(tmp->data);
            free(tmp);
        }
    }
    free(set->table);
    free(set);
}
