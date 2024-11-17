#include <stdio.h>
#include <stdbool.h>
#include <ncurses.h>
#include "headers.h"  // Ensure this file exists and is in the correct path
#include <wchar.h> // This is temporary as I'm trying to put in unicode characters
#include <ctype.h>
#include <string.h>
#include <stdlib.h>


// Function declarations
void select1(int n,const char *a[],void (*b[])());  //Function allows user to input options    
//here n is the number of options, a is the array of label names, and b is the function pointer array  // Function to allow user to choose signup or login
void signup(void);
void login1(void);
void quit(void);

int main(void) {
    create_tables();
    // Initialize ncurses
    initscr();
    
    const char *a[3]={"Sign up","Login","Quit"};
    void (*b[])()={signup,login1,quit};
    
    // Clear the screen and show options
    clear();
    select1(3,a,b);

    // Cleanup ncurses
    endwin();
    return 0;
}


void select1(int n,const char *a[],void (*b[])()) {
  
    int choice=0;
    int tco = 0; //the_chosen_one
    
    int sizea=n;
    int ch;
    //char opencircle[]="\u25EF";
    //char closedcircle[]="\u2B24";

    initscr();
    raw();
    clear();
    start_color();
    cbreak();
    noecho();
    curs_set(0);     

    keypad(stdscr, TRUE);

    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_YELLOW, COLOR_BLACK);


    while(true){
        clear();
        attron(COLOR_PAIR(1));
        mvprintw(5, 10, "Welcome! Please live:");
        attroff(COLOR_PAIR(1));
        for(int i=0;i<sizea;i++){
            if(i==tco){
                attron(COLOR_PAIR(2));
                mvprintw(7+i,12,"> %s",a[i]);
                attroff(COLOR_PAIR(2));
                refresh();
            }
            else{
                attron(COLOR_PAIR(1));
                mvprintw(7+i,12,"  %s",a[i]);
                attroff(COLOR_PAIR(1));
                refresh();
            }
        }
        
        attron(COLOR_PAIR(1));
        mvprintw(10, 10, "Use arrow keys to navigate, Enter to select1.");
        attroff(COLOR_PAIR(1));
        refresh();

        ch=getch();
        
        if(ch =='\n'){
            choice=tco;
            break;
        }
        else if(ch==KEY_DOWN){
            if(tco==sizea-1)
                tco=0;
                else
                tco+=1;
                
        }
        else if(ch==KEY_UP){
            if(tco==0)
                tco=sizea-1;
                else
                tco-=1;
                
        }
        else
        continue;

    } 

    b[choice]();
    endwin();
}


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
            break; // Valid input
        }

        // error message if invalid input
        attron(COLOR_PAIR(1));
        mvprintw(row + 1, 10, "Invalid %s. Please try again.", label);
        attroff(COLOR_PAIR(1));
        refresh();
    } while (1);
}


void signup() {
    clear();
    int max_length = 100;
    char name[max_length], email[max_length];
    char password[max_length], phoneNumber[max_length], address[max_length];
    char pincode[max_length], state[max_length];

    start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLACK); 
    init_pair(2, COLOR_YELLOW, COLOR_BLACK); 

    attron(COLOR_PAIR(1));
    mvprintw(2, 10, "Signup Form");
    mvprintw(3, 10, "Press Enter to submit each field, and type carefully:");
    attroff(COLOR_PAIR(1));
    refresh();

    get_valid_input(5, "Name", name, max_length, is_valid_name);
    get_valid_input(6, "Email", email, max_length, is_valid_email);
    attron(COLOR_PAIR(1));
    mvprintw(7, 10, "Password: ");
    attroff(COLOR_PAIR(1));
    refresh();
    attron(COLOR_PAIR(2));
    noecho();
    int ch, index = 0;
    while ((ch = getch()) != '\n') {
        if (ch == KEY_BACKSPACE || ch == 127) {
            if (index > 0) {
                index--;
                mvaddch(7, 20 + index, ' '); 
                move(7, 20 + index);
            }
        } else if (index < max_length - 1) {
            password[index++] = ch;
            mvaddch(7, 20 + index - 1, '*'); 
        }
    }
    password[index] = '\0';
    attroff(COLOR_PAIR(2));
    echo();

    get_valid_input(8, "Phone Number", phoneNumber, max_length, is_valid_phone);
    get_valid_input(9, "Address", address, max_length, NULL);
    get_valid_input(10, "Pincode", pincode, max_length, is_valid_pincode);
    get_valid_input(11, "State", state, max_length, NULL);
    clear();

    char *admin_domain = "@sigmastore.in";
    if (strlen(email) >= strlen(admin_domain) && strcmp(email + strlen(email) - strlen(admin_domain), admin_domain) == 0) {
        create_admin(name, email, password, phoneNumber, address, atoi(pincode), state);
    } else {
        create_customer(name, email, password, phoneNumber, address, atoi(pincode), state);
    }
    attron(COLOR_PAIR(1));
    mvprintw(5, 10, "Signup Successful! Here's the data you entered:");
    mvprintw(6, 10, "Name:");
    mvprintw(7, 10, "Email:");
    mvprintw(8, 10, "Password:");
    mvprintw(9, 10, "Phone Number:");
    mvprintw(10, 10, "Address:");
    mvprintw(11, 10, "Pincode:");
    mvprintw(12, 10, "State:");
    attroff(COLOR_PAIR(1));
    attron(COLOR_PAIR(2));
    mvprintw(6, 30, "%s", name);
    mvprintw(7, 30, "%s", email);
    mvprintw(8, 30, "%s (hidden during entry)", password);
    mvprintw(9, 30, "%s", phoneNumber);
    mvprintw(10, 30, "%s", address);
    mvprintw(11, 30, "%s", pincode);
    mvprintw(12, 30, "%s", state);
    attroff(COLOR_PAIR(2));
    refresh();

    attron(COLOR_PAIR(1));
    mvprintw(15, 10, "Press any key to return to the menu.");
    attroff(COLOR_PAIR(1));
    getch();
    main();
}

void login1(){
    clear();
    mvprintw(5, 10, "Login function called");
    refresh();
    getch();
}
void quit(){
    clear();
}