#include <stdio.h>
#include <stdbool.h>
#include <ncurses.h>
#include "../headers.h"
#include <wchar.h> // This is temporary as I'm trying to put in unicode characters
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

void menu1(void);
void cart(void);
void wallet(void);
void categories(void);
void settings(void);
void buttonselect2d(int m,int n,const char *a[m][n],void (*b[m][n])(),int row, int column);

void cart() {
    clear();
    DisplayCart(userdetails->id);
}

void wallet() {
    clear();
    mvprintw(5, 10, "Wallet function called.");
    refresh();
    getch();
}

void categories() {
    clear();
    //mvprintw(5, 10, "Categories function called.");
    const char *a[3][2] = {
        {"cat1", "cat2"},
        {"cat3", "cat4"},{"cat5","cat6"}
    };
    void (*b[3][2])() = {
        {cart, wallet},
        {categories, settings},{categories,categories}
    };

    // Clear the screen and show options
    buttonselect2d(3, 2, a, b,5,50);
    refresh();
    getch();
}

void settings() {
    clear();
    mvprintw(5, 10, "Settings function called.");
    refresh();
    getch();
}

void menu1(void){

    initscr();
    clear();
    mvprintw(5, 5, "        _____ _____ _____ __  __             _____ _______ ____  _____  ______ ");
mvprintw(6, 10, "  / ____|_   _/ ____|  \\/  |   /\\      / ____|__   __/ __ \\|  __ \\|  ____|");
mvprintw(7, 10, " | (___   | || |  __| \\  / |  /  \\    | (___    | | | |  | | |__) | |__   ");
mvprintw(8, 10, "  \\___ \\  | || | |_ | |\\/| | / /\\ \\    \\___ \\   | | | |  | |  _  /|  __|  ");
mvprintw(9, 10, "  ____) |_| || |__| | |  | |/ ____ \\   ____) |  | | | |__| | | \\ \\| |____ ");
mvprintw(10, 10, " |_____/|_____\\_____|_|  |_/_/    \\_\\ |_____/   |_|  \\____/|_|  \\_\\______|");

refresh();

    const char *a[2][2] = {
        {"CART", "WALLET"},
        {"CATEGORIES", "SETTINGS"}
    };
    void (*b[2][2])() = {
        {cart, wallet},
        {categories, settings}
    };

    // Clear the screen and show options
    buttonselect2d(2, 2, a, b,5,90);
    // Cleanup ncurses
    
refresh();
endwin();

}   

void buttonselect2d(int m,int n,const char *a[m][n],void (*b[m][n])(),int row, int column) {
  
    int choice[2]={0,0};
    int tco[2] = {0,0}; //the_chosen_one
    
    int sizer=m;
    int sizec=n;
    int ch;
    //char opencircle[]="\u25EF";
    //char closedcircle[]="\u2B24";

    initscr();
    raw();
    start_color();
    cbreak();
    noecho();
    curs_set(0);     

    keypad(stdscr, TRUE);

    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_YELLOW, COLOR_BLACK);

    while(true){
    
    for (int i = 0; i < sizer; i++) {
            for (int j = 0; j < sizec; j++) {
                

                if (i == tco[0] && j == tco[1]) {
                    // Highlight the selected button
                    attron(COLOR_PAIR(2));
                    mvprintw(i*4+row, j*50+column, "+--------------------------------+");
                    mvprintw(i*4+row+1, j*50+column, "|            %-18s  |", a[i][j]);
                    mvprintw(i*4+row+2, j*50+column, "+--------------------------------+");
                    attroff(COLOR_PAIR(2));
                } else {
                    // Render the non-selected buttons
                    attron(COLOR_PAIR(1));
                    mvprintw(i*4+row, j*50+column, "+--------------------------------+");
                    mvprintw(i*4+row+1, j*50+column, "|            %-18s  |", a[i][j]);
                    mvprintw(i*4+row+2, j*50+column, "+--------------------------------+");
                    attroff(COLOR_PAIR(1));
                }
            }
        }
        

        ch=getch();
        
        if(ch =='\n'){
            choice[0]=tco[0];
            choice[1]=tco[1];
            break;
        }
        else if(ch==KEY_DOWN){
            if(tco[0]==sizer-1)
                tco[0]=0;
            else
                tco[0]+=1;
                
        }
        else if(ch==KEY_UP){
            if(tco[0]==0)
                tco[0]=sizer-1;
            else
                tco[0]-=1;
                
        }
        else if(ch==KEY_RIGHT){
            if(tco[1]==sizec-1)
                tco[1]=0;
                else
                tco[1]+=1;
        }
        else if(ch==KEY_LEFT){
            if(tco[1]==0)
                tco[1]=sizec-1;
            else
                tco[1]-=1;
        }


        else
        continue;

    } 
    if(strcmp(a[choice[0]][choice[1]],"PLACE ORDER")==0){
        printw("Order has been placed. Press any key to continue");
        refresh();
        getch();
        clear();
        endwin();
        PlaceOrder(userdetails->id);
        

    }
    else if(strcmp(a[choice[0]][choice[1]],"BACK")==0){
        endwin();
        menu1();
        
    }

    else{
    clear();
    b[choice[0]][choice[1]]();
    endwin();}
}
