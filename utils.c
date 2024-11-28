#include "headers.h"
#include <time.h>
#include <ctype.h>

int getISTTime(){
    time_t rawtime;
    struct tm * timeinfo;

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    timeinfo->tm_hour += 5;
    timeinfo->tm_min += 30;

    mktime(timeinfo);

    return mktime(timeinfo);
}

// SQL stuff
int countCallback(void *count, int argc, char **argv, char **azColName){
    *(int *)count = atoi(argv[0]);
    return 0;
}

//Signup stuff

int is_numeric(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isdigit((unsigned char)str[i]))
            return 0;
    }
    return 1;
}

int is_valid_email(char *email) { // if there is one @ in the email, it confirms that it is valid
    int at_count = 0;
    for (int i = 0; email[i] != '\0'; i++) {
        if (email[i] == '@') {
            at_count++;
        }
    }
    return (at_count == 1 && (is_email_taken(email)==0));
}

int is_valid_email_for_login(char *email) { // if there is one @ in the email, it confirms that it is valid
    int at_count = 0;
    for (int i = 0; email[i] != '\0'; i++) {
        if (email[i] == '@') {
            at_count++;
        }
    }
    return at_count == 1;
}

int is_valid_name(char *name) { // name cannot be empty or just numericor have invalid characters
    if (strlen(name) == 0) return 0;
    for (int i = 0; name[i] != '\0'; i++) {
        if (!isalnum(name[i]) && name[i] != ' ') { 
            return 0; 
        }
    }
    return !is_numeric(name); 
    }

int is_valid_phone(char *phone) { // phone number must be 10 digits
    return strlen(phone) == 10 && is_numeric(phone);
}

int is_valid_pincode(char *pincode) { // pincode must be numeric
    return is_numeric(pincode);
}

void get_valid_input(int row, char *label, char *buffer, int max_length, int (*validate)(char *)) {
    do {
        move(row, 10);
        clrtoeol();

        attron(COLOR_PAIR(1)|A_BOLD);
        mvprintw(row, 10, "%s: ", label);
        attroff(COLOR_PAIR(1)|A_BOLD);
        refresh();

        attron(COLOR_PAIR(2));
        echo();
        getnstr(buffer, max_length);
        noecho();
        if (buffer[0] == 27 && buffer[1] == '\0') { // check for escape + enter
        main(); 
        return;
        }
        attroff(COLOR_PAIR(2));

        move(row + 1, 10); // makes sure it doesnt clash with any error message
        clrtoeol();

        if (validate == NULL || validate(buffer)) { // Checks for valid input if required per the case.
            break; // Valid input
        }

        // error message if invalid input
        attron(COLOR_PAIR(1));
        mvprintw(row + 1, 10, "Invalid %s. Please try again.", label);
        attroff(COLOR_PAIR(1));
        refresh();
    } while (1);
}

void get_valid_login(int row, char *label, char *buffer, int max_length, int (*validate)(char *),void page()){
    do {
        move(row, 10);
        clrtoeol();

        attron(COLOR_PAIR(1)|A_BOLD);
        mvprintw(row, 10, "%s: ", label);
        attroff(COLOR_PAIR(1)|A_BOLD);
        refresh();

        attron(COLOR_PAIR(2));
        echo();
        getnstr(buffer, max_length);
        noecho();
        if (buffer[0] == 27 && buffer[1] == '\0') { //escape+enter
        main(); 
        return;
}
        attroff(COLOR_PAIR(2));

        move(row + 1, 10); // makes sure it doesnt clash with any error message
        clrtoeol();

        if (validate == NULL || validate(buffer)) { // Checks for valid input if required per the case.
            if(is_email_taken(buffer)==0){
                attron(COLOR_PAIR(1)|A_BOLD);
                mvprintw(row + 1, 10, "This account does not exist. Please sign up.");
                attroff(COLOR_PAIR(1)|A_BOLD);
                refresh();
                getch();
                page();
            }
            else if(is_email_taken(buffer)==1){
                break;

            }

            break; // Valid input
        }

        // error message if invalid input
        else{
        attron(COLOR_PAIR(1));
        mvprintw(row + 1, 10, "Invalid %s. Please try again.", label);
        attroff(COLOR_PAIR(1));
        refresh();
        }
    } while (1);
}

char* get_date_from_time(time_t timestamp) {
    struct tm *time_info;
    char *formatted_date = malloc(11 * sizeof(char));

    if (formatted_date == NULL) {
        return NULL;
    }

    time_info = localtime(&timestamp);

    strftime(formatted_date, 11, "%Y-%m-%d", time_info);

    return formatted_date;
}