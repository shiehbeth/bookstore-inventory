#ifndef HEADER_H
#define HEADER_H

# include <stdio.h>
# include <stdlib.h>
# include <ctype.h>
# include <mysql/mysql.h>
# include <stdbool.h>
# include <string.h>
# include "user.h"
# include "hashset.h"

void toLowercase(char *str);
void finish_with_error(MYSQL *con);
void inventorySearch(User *user);
int convertToInt(char str[]);
void display(book **historyBooks, int rowCount);
void freeHistoryBooks(book **historyBooks, int rowCount);

#endif
