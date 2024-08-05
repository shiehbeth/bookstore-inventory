#include "../include/header.h"

// Compare by title
int compareByTitle(book* a, book* b) {
    return strcmp(a->bookTitle, b->bookTitle);
}

// Compare by author
int compareByAuthor(book* a, book* b) {
    return strcmp(a->bookAuthor, b->bookAuthor);
}

// compare by isbn
int compareByISBN(book* a, book* b) {
    return strcmp(a->ISBN, b->ISBN);
}

// partition method definition
int partition(book* input[], int low, int high, int (*compare)(book*, book*)) {
    // initialize variables
    int midpoint = low + (high - low) / 2;
    book* pivot = input[midpoint];
    bool done = false;
    // compare values to the pivot
    while (!done) {
        while (compare(input[low], pivot) < 0) {
            low += 1;
        }
        while (compare(pivot, input[high]) < 0) {
            high -= 1;
        }
        if (low >= high) {
            done = true;
        } else {
            // swap the values
            book* tmp = input[low];
            input[low] = input[high];
            input[high] = tmp;
            low += 1;
            high -= 1;
        }
    }
    return high;
}

// quicksort method
void quicksort(book* input[], int low, int high, int (*compare)(book*, book*)) {
    if (low >= high) {
        return;
    }
    // call partition
    int lowEnd = partition(input, low, high, compare);
    // recursively call quicksort
    quicksort(input, low, lowEnd, compare);
    quicksort(input, lowEnd + 1, high, compare);
}

// search personal method definition
void searchPersonal(book** input, int numBooks) {
    // initialize index
    int index = -1;
    // prompt for search criteria
    printf("Which key word would you like to use? ");
    char inputStr[20];
    scanf("%s", inputStr);
    // convert to lower
    for (int i = 0; inputStr[i]; i++) {
        inputStr[i] = tolower((unsigned char)inputStr[i]);
    }
    // isbn criteria
    if (strcmp(inputStr, "isbn") == 0) {
        char inputISBN[20];
        printf("Enter the ISBN: ");
        scanf("%s", inputISBN);
        // call quicksort comparing by isbn
        quicksort(input, 0, numBooks-1, compareByISBN);
        // binary search by isbn
        index = binarySearchByISBN(input, 0, numBooks-1, inputISBN);
    // search by title criteria
    } else if (strcmp(inputStr, "title") == 0) {
        char inputTitle[256];
        printf("Searching by title - ");
        getchar();
        printf("Enter the title: ");
        if (fgets(inputTitle, sizeof(inputTitle), stdin)) {
        // Remove the newline character if present
            size_t len = strlen(inputTitle);
            if (len > 0 && inputTitle[len - 1] == '\n') {
                inputTitle[len - 1] = '\0';
            }
        }
        // call quicksort comparing by title
        quicksort(input, 0, numBooks-1, compareByTitle);
        // binary search by title
        index = binarySearchByTitle(input, 0, numBooks-1, inputTitle);
    // search criteria by author
    } else if (strcmp(inputStr, "author") == 0) {
        char inputAuthor[20];
        getchar();
        printf("Searching by author - ");
        printf("Enter the author: ");
        if (fgets(inputAuthor, sizeof(inputAuthor), stdin)) {
        // Remove the newline character if present
            size_t len = strlen(inputAuthor);
            if (len > 0 && inputAuthor[len - 1] == '\n') {
                inputAuthor[len - 1] = '\0';
            }
        }
        // call quicksort comparing by author
        quicksort(input, 0, numBooks-1, compareByAuthor);
        // binary search by author
        index = binarySearchByAuthor(input, 0, numBooks-1, inputAuthor);
    }

    // check result from binary search and print result
    if (index == -1) {
        printf("Book not found in personal history.\n");
        printf("----------------------------------------------------------------------\n");
    }
    else {
        printf("ISBN: %-15s Title: %-50s\n", input[index]->ISBN, input[index]->bookTitle);
        printf("Author: %-25s Rating: %-49d\n" ,input[index]->bookAuthor, input[index]->rating);
        printf("----------------------------------------------------------------------\n");
    }
}

// binary search by title method definition
int binarySearchByTitle(book* input[], int left, int right, char* title) {
    if (right >= left) {
        int mid = left + (right - left) / 2;
        // check if theres a match
        if (strcmp(input[mid]->bookTitle, title) == 0) {
            return mid;
        } // recursively call binary search
        if (strcmp(input[mid]->bookTitle, title) > 0) {
            return binarySearchByTitle(input, left, mid-1, title);
        }
        // recursively call binary search
        return binarySearchByTitle(input, mid+1, right, title);
    }
    return -1;
}

// binary search by author method definition
int binarySearchByAuthor(book* input[], int left, int right, char* author) {
    if (right >= left) {
        int mid = left + (right - left) / 2;
        // check if theres a match
        if (strcmp(input[mid]->bookAuthor, author) == 0) {
            return mid;
        } // recursively call binary search
        if (strcmp(input[mid]->bookAuthor, author) > 0) {
            return binarySearchByAuthor(input, left, mid-1, author);
        }
        // recursively call binary search
        return binarySearchByAuthor(input, mid+1, right, author);
    }

    return -1;
}

// binary search by isbn method definition
int binarySearchByISBN(book* input[], int left, int right, char* isbn) {
    if (right >= left) {
        int mid = left + (right - left) / 2;
        // check if theres a match
        if (strcmp(input[mid]->ISBN, isbn) == 0) {
            return mid;
        } // recursively call binary search
        if (strcmp(input[mid]->ISBN, isbn) > 0) {
            return binarySearchByISBN(input, left, mid-1, isbn);
        } // recursively call binary search
        return binarySearchByISBN(input, mid+1, right, isbn);
    }

    return -1;
}
