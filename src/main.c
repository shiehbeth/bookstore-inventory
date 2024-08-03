# include "../include/header.h"
// rowCount is global variable
int rowCount = 0;
const int MAXLEN = 50;
const int TOPFIVE = 5;

int main (void) {
    bool done = false;
    char inputStr[MAXLEN];
    printWelcomeInfo();
    User *user = initUser();
    
    while (!done) {
        printf("What would you like to do?\n");
        scanf("%s", inputStr);
        toLowercase(inputStr);
        if (strcmp(inputStr, "search") == 0) {
            //1.personalSearch()
            //2.search()
            printf("Enter 1 to book inventory, 2 to personal inventory\n");
            int inputNum = 0;
            scanf("%d", &inputNum);
            switch (inputNum) {
                case 1:
                    inventorySearch(user);
                    break;
                case 2:
                    searchPersonal(user->historyBook, rowCount);
                    break;
                default:
                    break;
            }     
        } else if (strcmp(inputStr, "show") == 0) {
            show(user);
        } else if (strcmp(inputStr, "done") == 0) {
            done = true;
        } else {
            printf("Invalid Operation. Please try again.\n");
        }
    }
    freeHistoryBooks(user->historyBook, rowCount);
    memoryHandler(user->readingList);
    free(user);
    return 0;
}
