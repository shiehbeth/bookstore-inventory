# include <stdlib.h>
# include <stdio.h>
# include "book.h"
# include "LLT.h"

const int TOPFIVE = 5;
typedef struct User_t {
    int ID;
    char *name;
    LLT *history;
    char *topFiveBooks[TOPFIVE];
} User;