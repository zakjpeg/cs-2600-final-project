#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Group members: Zak El-Assaad, Michael Liang

const short int OP_SYS = 0; // Set to 1 when using windows, 0 when using Unix


struct Expense {
    float amount;
    char category[20];
    char date[100];
};

void viewAllExpenses(struct Expense* expenses, int expensesLen);

void importExpenses(struct Expense** expenses, int *expensesLen);

float getTotalSpend(struct Expense* expenses, int expensesLen);

void logExpense(struct Expense** expenses, int *expensesLen);

void analyzeSpending(struct Expense* expenses, int expensesLen);


// Function: clearScreen
// Purpose: clears the terminal
void clearScreen() {

    // val == 1 : Windows
    // val == 0 : Unix

    if (OP_SYS) {
        system("cls");
    } else {
        system("clear");
    }
}

void closeProgram(struct Expense* expenses, int expensesLen) {
    char temp = 0;
    clearScreen();
    printf(
                                                                                                                                                   
"                                                                   ddddddddbbbbbbbb                                                        \n"
"        GGGGGGGGGGGGG                                              d::::::db::::::b                                                    !!! \n"
"     GGG::::::::::::G                                              d::::::db::::::b                                                   !!:!!\n"
"   GG:::::::::::::::G                                              d::::::db::::::b                                                   !:::!\n"
"  G:::::GGGGGGGG::::G                                              d:::::d  b:::::b                                                   !:::!\n"
" G:::::G       GGGGGG   ooooooooooo      ooooooooooo       ddddddddd:::::d  b:::::bbbbbbbbb yyyyyyy           yyyyyyy eeeeeeeeeeee    !:::!\n"
"G:::::G               oo:::::::::::oo  oo:::::::::::oo   dd::::::::::::::d  b::::::::::::::bby:::::y         y:::::yee::::::::::::ee  !:::!\n"
"G:::::G              o:::::::::::::::oo:::::::::::::::o d::::::::::::::::d  b::::::::::::::::by:::::y       y:::::ye::::::eeeee:::::ee!:::!\n"
"G:::::G    GGGGGGGGGGo:::::ooooo:::::oo:::::ooooo:::::od:::::::ddddd:::::d  b:::::bbbbb:::::::by:::::y     y:::::ye::::::e     e:::::e!:::!\n"
"G:::::G    G::::::::Go::::o     o::::oo::::o     o::::od::::::d    d:::::d  b:::::b    b::::::b y:::::y   y:::::y e:::::::eeeee::::::e!:::!\n"
"G:::::G    GGGGG::::Go::::o     o::::oo::::o     o::::od:::::d     d:::::d  b:::::b     b:::::b  y:::::y y:::::y  e:::::::::::::::::e !:::!\n"
"G:::::G        G::::Go::::o     o::::oo::::o     o::::od:::::d     d:::::d  b:::::b     b:::::b   y:::::y:::::y   e::::::eeeeeeeeeee  !!:!!\n"
" G:::::G       G::::Go::::o     o::::oo::::o     o::::od:::::d     d:::::d  b:::::b     b:::::b    y:::::::::y    e:::::::e            !!! \n"
"  G:::::GGGGGGGG::::Go:::::ooooo:::::oo:::::ooooo:::::od::::::ddddd::::::dd b:::::bbbbbb::::::b     y:::::::y     e::::::::e               \n"
"   GG:::::::::::::::Go:::::::::::::::oo:::::::::::::::o d:::::::::::::::::d b::::::::::::::::b       y:::::y       e::::::::eeeeeeee   !!! \n"
"     GGG::::::GGG:::G oo:::::::::::oo  oo:::::::::::oo   d:::::::::ddd::::d b:::::::::::::::b       y:::::y         ee:::::::::::::e  !!:!!\n"
"        GGGGGG   GGGG   ooooooooooo      ooooooooooo      ddddddddd   ddddd bbbbbbbbbbbbbbbb       y:::::y            eeeeeeeeeeeeee   !!! \n"
"                                                                                                  y:::::y                                  \n"
"                                                                                                 y:::::y                                   \n"
"                                                                                                y:::::y                                    \n"
"                                                                                               y:::::y                                     \n"
"                                                                                              yyyyyyy                                      \n"
"                                                                                                                                           \n"
"                                                                   ( Press ENTER to exit )                                                 \n"
    );
    scanf("%c", &temp);
    scanf("%c", &temp);
    clearScreen();

    // save to file
    FILE* fptr = fopen("expenses.log", "w");
    for (int i = 0; i < expensesLen; i++) {
        fprintf(fptr, "%f\n", expenses[i].amount);
        fprintf(fptr, "%s\n",  expenses[i].category);
        fprintf(fptr, "%s\n",  expenses[i].date);
    }

    free(expenses);

}

void openingScreen() {
    char temp = 0;
    clearScreen();
    printf(
                                                                                                                          
"                                                                                                                  dddddddd\n"
"        CCCCCCCCCCCCC        SSSSSSSSSSSSSSS                                                                      d::::::d\n"
"     CCC::::::::::::C      SS:::::::::::::::S                                                                     d::::::d\n"
"   CC:::::::::::::::C     S:::::SSSSSS::::::S                                                                     d::::::d\n"
"  C:::::CCCCCCCC::::C     S:::::S     SSSSSSS                                                                     d:::::d \n"
" C:::::C       CCCCCC     S:::::S           ppppp   ppppppppp       eeeeeeeeeeee    nnnn  nnnnnnnn        ddddddddd:::::d \n"
"C:::::C                   S:::::S           p::::ppp:::::::::p    ee::::::::::::ee  n:::nn::::::::nn    dd::::::::::::::d \n"
"C:::::C                    S::::SSSS        p:::::::::::::::::p  e::::::eeeee:::::een::::::::::::::nn  d::::::::::::::::d \n"
"C:::::C                     SS::::::SSSSS   pp::::::ppppp::::::pe::::::e     e:::::enn:::::::::::::::nd:::::::ddddd:::::d \n"
"C:::::C                       SSS::::::::SS  p:::::p     p:::::pe:::::::eeeee::::::e  n:::::nnnn:::::nd::::::d    d:::::d \n"
"C:::::C                          SSSSSS::::S p:::::p     p:::::pe:::::::::::::::::e   n::::n    n::::nd:::::d     d:::::d \n"
"C:::::C                               S:::::Sp:::::p     p:::::pe::::::eeeeeeeeeee    n::::n    n::::nd:::::d     d:::::d \n"
" C:::::C       CCCCCC                 S:::::Sp:::::p    p::::::pe:::::::e             n::::n    n::::nd:::::d     d:::::d \n"
"  C:::::CCCCCCCC::::C     SSSSSSS     S:::::Sp:::::ppppp:::::::pe::::::::e            n::::n    n::::nd::::::ddddd::::::dd\n"
"   CC:::::::::::::::C     S::::::SSSSSS:::::Sp::::::::::::::::p  e::::::::eeeeeeee    n::::n    n::::n d:::::::::::::::::d\n"
"     CCC::::::::::::C     S:::::::::::::::SS p::::::::::::::pp    ee:::::::::::::e    n::::n    n::::n  d:::::::::ddd::::d\n"
"        CCCCCCCCCCCCC      SSSSSSSSSSSSSSS   p::::::pppppppp        eeeeeeeeeeeeee    nnnnnn    nnnnnn   ddddddddd   ddddd\n"
"                                             p:::::p                                                                      \n"
"                                             p:::::p                                                                      \n"
"                                            p:::::::p                                                                     \n"
"                                            p:::::::p                                                                     \n"
"                                            p:::::::p                                                                     \n"
"                                            ppppppppp                                                                     \n"
                                                                                                                          
    );

    printf(
        "\n\n                                            By Zak El-Assaad and Michael Liang"
        "\n                                               Press ENTER to continue...\n\n"
    );
    scanf("%c", &temp);
    clearScreen();

}


int main() {

    // 0: program is closed, 1: program is open
    short int programOpen = 1;

    float spendThisMonth = 1149.52;

    // Declare expenses
    struct Expense* expenses = NULL;
    int expensesLen = 0;

    // Import expenses
    importExpenses(&expenses, &expensesLen);

    // Show opening screen
    openingScreen();

    // Main Menu
    while (programOpen) {

        clearScreen();
        float totalSpend = getTotalSpend(expenses, expensesLen);



        printf(
"==============================\n"
"      Welcome to CSpend          \n"
"\n"
"You spent $%.2f in total         \n"
"==============================\n"
"  1. Log an Expense              \n"
"  2. View my Expenses              \n"
"  3. Analyze my Spending            \n"
"------------------------------\n"
"  0. Save & Exit                    \n"
"==============================\n"
"Enter choice: ",
totalSpend
);

        int menuChoice = 0;
        
        scanf("%d", &menuChoice);

        switch (menuChoice) {
            // Close program
            case 0:
                programOpen = 0;
                closeProgram(expenses, expensesLen);
                break;

            case 1:
                logExpense(&expenses, &expensesLen);
                break;

            case 2:
                viewAllExpenses(expenses, expensesLen);
                break;
            case 3:
                analyzeSpending(expenses, expensesLen);
                break;

            default:
                break;

        }




    }

    return 0;
}










// view all expenses
void viewAllExpenses(struct Expense* expenses, int expensesLen) {
    clearScreen();
    if (expensesLen == 0) {
        printf("No expenses logged!\n");
    }
    for (int i = 0; i < expensesLen; i++) {
        printf("$%.2f\n%s\n%s\n---\n", expenses[i].amount, expenses[i].category, expenses[i].date);
    }
    printf("Press ENTER to continue...");
    char temp = 0;
    scanf("%c", &temp);
    scanf("%c", &temp);
}

void importExpenses(struct Expense** expenses, int *expensesLen) {
    
    // open log file
    FILE* fptr;
    fptr = fopen("expenses.log", "r"); // open in read mode

    // check if log file is open, else create a log file
    if (fptr == NULL) {
        fptr = fopen("expenses.log", "w");
        fclose(fptr);
        return;
    }

    *expenses = NULL;

    int loopIdx = 0;
    // while loop
    while (1) {

        // store all three inputs
        struct Expense newExpense;
        char inAmount[100];
        char inCategory[100];
        char inDate[100];

        if (fgets(inAmount, 100, fptr) == NULL) break;
        
        if (fgets(inCategory, 100, fptr) == NULL) break;
        if (fgets(inDate, 100, fptr) == NULL) break;

        newExpense.amount = atof(inAmount);
        strcpy(newExpense.category, inCategory);
        strcpy(newExpense.date, inDate);
        newExpense.category[strcspn(newExpense.category, "\r\n")] = '\0';
        newExpense.date[strcspn(newExpense.date, "\r\n")] = '\0';

        // memory allocate expenses
        *expenses = realloc(*expenses, sizeof(struct Expense) * (loopIdx + 1));
        (*expenses)[loopIdx] = newExpense;

        loopIdx++;


    }

    // close file
    *expensesLen = loopIdx;
    fclose(fptr);


}

float getTotalSpend(struct Expense* expenses, int expensesLen) {
    float total = 0;
    for (int i = 0; i < expensesLen; i++) {
        total += expenses[i].amount;
    }
    return total;
}

void logExpense(struct Expense** expenses, int *expensesLen) {

    // Clear screen
    clearScreen();

    float inAmount;
    char inCategory[100];

    // Prompt amount
    printf("NEW EXPENSE\nEnter total: $");
    scanf("%f", &inAmount);

    // Prompt category
    printf("Which category is this expense?\n");
    printf(
        "1. Housing\n" // needs
        "2. Food\n"
        "3. Transportation\n"
        "4. Utilities\n"
        "5. Savings\n" // savings
        "6. Entertainment\n" // entertainment
        "7. Subscriptions\n"
        "8. Personal Care\n"
        "9. Other\n" // other
    );

    int userSelection = 0;
    while (userSelection < 1 || userSelection > 9) {
        scanf("%d", &userSelection);
    }

    // construct new expense
    struct Expense newExpense;
    newExpense.amount = inAmount;
    switch (userSelection) {
        case (1):
            strcpy(newExpense.category, "Housing");
            break;
        case (2):
            strcpy(newExpense.category, "Food");
            break;
        case (3):
            strcpy(newExpense.category, "Transportation");
            break;
        case (4):
            strcpy(newExpense.category, "Utilities");
            break;
        case (5):
            strcpy(newExpense.category, "Savings");
            break;
        case (6):
            strcpy(newExpense.category, "Entertainment");
            break;
        case (7):
            strcpy(newExpense.category, "Subscriptions");
            break;
        case (8):
            strcpy(newExpense.category, "Personal Care");
            break;
        case (9):
            strcpy(newExpense.category, "Other");
            break;
    }
    strcpy(newExpense.date, "Today");

    // reallocate expenses, add new expense to end
    *expenses = realloc(*expenses, sizeof(struct Expense) * (*expensesLen + 1));
    (*expenses)[*expensesLen] = newExpense;

    // increaese expenses length
    (*expensesLen)++;


}

void analyzeSpending(struct Expense* expenses, int expensesLen) {
    // log the totals into each category
    float wantsTotal = 0;
    float needsTotal = 0;
    float savingsTotal = 0;

    for (int i = 0; i < expensesLen; i++) {
        char* currCat = expenses[i].category;
        float currAmount = expenses[i].amount;
        if (!strcmp(currCat, "Housing") || !strcmp(currCat, "Food") || !strcmp(currCat, "Transportation") || !strcmp(currCat, "Utilities")) {
            needsTotal += currAmount;
        } else if (!strcmp(currCat, "Entertainment") || !strcmp(currCat, "Subscriptions") || !strcmp(currCat, "Personal Care") ) {
            wantsTotal += currAmount;
        } else if (!strcmp(currCat, "Savings")) {
            savingsTotal += currAmount;
        }
    }

    float total = wantsTotal + needsTotal + savingsTotal;

    float wantsRatio = wantsTotal / total;
    float needsRatio = needsTotal / total;
    float savingsRatio = savingsTotal / total;

    clearScreen();
    printf("Follow the 50/30/20 rule:\n50%% spending on needs, 30%% spending on wants, 20%% of income saved\n\n");
    printf(
        "YOUR TOTAL SPENDING: $%.2f\n\n"
        "Needs: $%.2f (%.1f%%)\n"
        "Wants: $%.2f (%.1f%%)\n"
        "Savings: $%.2f (%.1f%%)\n",
        total, needsTotal, needsRatio*100, wantsTotal, wantsRatio*100, savingsTotal, savingsRatio*100
    );

    
    if (wantsRatio > 0.3) {
        printf("\nADVICE:\nYou're spending %.0f%% of your income on wants.\nTry to get this number below 30%%.\n\n", wantsRatio*100);
    }  else if (savingsRatio < 0.2) {
        printf("\nADVICE:\nYou're saving %.0f%% of your income.\nTry to save 20%% or more.\n.", savingsRatio*100);
    } else if (needsRatio > 0.5) {
        printf("\nADVICE:\nYou're spending %.0f%% of your income on needs.\nTry to get this number below 50%%.\n\n", needsRatio*100);
    } else {
        printf("\nYou have good spending habits!\nKeep it up.\n\n");
    }

    char temp = '0';
    printf("Press ENTER to continue...");
    scanf("%c", &temp);
    scanf("%c", &temp);


}


