#include <stdio.h>
#include <stdbool.h>
#include <ncurses.h>
#include "headers.h"  // Ensure this file exists and is in the correct path
#include <wchar.h> // This is temporary as I'm trying to put in unicode characters

 
// Function declarations
void select1(int n,const char *a[],void (*b[])());  //Function allows user to input options    
//here n is the number of options, a is the array of label names, and b is the function pointer array  // Function to allow user to choose signup or login
void signup(void);
void login1(void);
void quit(void);

int main(void) {
    create_tables();
    create_product("Harry Potter",300,"Magic","Books","Penguin House");
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
void signup() {
    // Placeholder for signup function
    clear();
    mvprintw(5, 10, "Signup function called");
    refresh();
    getch();
}
void login1(){
    clear();
    //mvprintw(5, 10, "Login function called");
    new();
    refresh();
    getch();
}
void quit(){
    clear();
}