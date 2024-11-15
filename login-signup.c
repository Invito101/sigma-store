#include <stdio.h>
#include <stdbool.h>
#include <ncurses.h>
#include "headers.h"  // Ensure this file exists and is in the correct path
#include <wchar.h> // This is temporary as I'm trying to put in unicode characters


// Function declarations
void choices(void);  // Function to allow user to choose signup or login
void signup(void);
void login1(void);
void quit(void);

int main(void) {
    create_tables();
    // Initialize ncurses
    initscr();
    raw();
    noecho();
    keypad(stdscr, TRUE);  // Enable arrow keys and other extended keys

    // Clear the screen and show options
    clear();
    choices();

    // Cleanup ncurses
    endwin();
    return 0;
}

void choices(void) {
    
    int choice=0;
    int tco = 0; //the_chosen_one
    const char *a[3]={"signup","login","quit"};
    void (*b[])()={signup,login1,quit};
    int sizea=sizeof(a)/sizeof(a[0]);
    int ch;
    //char opencircle[]="\u25EF";
    //char closedcircle[]="\u2B24";

    initscr();
    start_color();
    cbreak();
    noecho();
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
        mvprintw(10, 10, "Use arrow keys to navigate, Enter to select.");
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
    /*
    switch (choice){
        case 0:
            signup();
            break;
        case 1:
            clear();
            mvprintw(5, 10, "Welcome to login");
            refresh();
            getch();
            break;
        case 2:
            clear();

    }*/

    endwin();
}
void signup() {
    // Placeholder for signup function
    clear();
    mvprintw(5, 10, "Signup function called");
    refresh();
    getch();
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