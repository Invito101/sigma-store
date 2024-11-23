#include "../headers.h"
#include <time.h>
#include <ctype.h>
#include <stdlib.h>

int max_len = 100;
int has_alphabet(char *str)
{
    for (int j = 0; str[j] != '\0'; j++) {
        if (isalpha(str[j]))
            return 1;
    }
    return 0;
}

int is_valid_product_name(char *name)
{
    if (strlen(name)==0) return 0;
    else return 1;
}

int is_valid_price(char *price)
{
    if (is_numeric(price)&& atoi(price)!=0 && strlen(price)!=0)
        return 1;
    else return 0;
 
}
int is_valid_description(char* description)
{
    if (strlen(description)!=0 && has_alphabet(description)) return 1;
    else return 0;
}


int is_valid_manufactured_by(char* manufactured_by)
{
    if (strlen(name)==0) return 0;
    else return 1;
}

void get_valid_input_for_product(int row, char *label, char *buffer, int max_length, int (*validate)(char *)) {
    do {
        move(row, 10);
        clrtoeol();

        attron(COLOR_PAIR(1));
        mvprintw(row, 10, "%s: ", label);
        attroff(COLOR_PAIR(1));
        refresh();

        attron(COLOR_PAIR(2));
        echo();
        getnstr(buffer, max_length);
        noecho();
        attroff(COLOR_PAIR(2));

        move(row + 1, 10); // makes sure it doesnt clash with any error message
        clrtoeol();

        if (validate == NULL || validate(buffer)) { // Checks for valid input if required per the case.
            if(label == "Name of the product: " && is_product_name_taken(buffer)==1){
                attron(COLOR_PAIR(1));
                mvprintw(row + 1, 10, "Product with this name already exists. Please enter a new name.");
                attroff(COLOR_PAIR(1));
                refresh();
                getch();
                page();
            }
            else if(is_product_name_taken(buffer)==0){
                break;

            }

            break; // Valid input
        }

        // error message if invalid input
        attron(COLOR_PAIR(1));
        mvprintw(row + 1, 10, "Invalid %s. Please try again.", label);
        attroff(COLOR_PAIR(1));
        refresh();
    } while (1);
}
