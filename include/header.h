#ifndef HEADER_H
#define HEADER_H

# include <stdio.h>
# include <stdlib.h>
# include <ctype.h>
# include <mysql/mysql.h>
# include <stdbool.h>
# include <string.h>
# include "book.h"
# include "linkedList.h"
# include "user.h"

void toLowercase(char *str);
void finish_with_error(MYSQL *con);
void inventorySearch();
#endif
