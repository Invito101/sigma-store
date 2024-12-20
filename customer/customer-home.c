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
void exitprogram(void);
void buttonselect2d(int m,int n,const char *a[m][n],void (*b[m][n])(),int row, int column);

void cart() {
    clear();
    DisplayCart(userdetails->id);
}

void wallet() {
    clear();
     char *email = userdetails->email;
    int current_money = get_money_of_user(email);
    float random_float = (float)rand() / (float)RAND_MAX;
    int final_money = (int) (random_float * 1000000);
    mvprintw(1, 5, "Wallet Balance: %d", current_money);
    mvprintw(3, 5, "Solve the question to earn %d!", final_money);
    mvprintw(5, 5, "What is 2 + 2 / 2?");
    mvprintw(7, 5, "Your Answer: ");
    refresh();
    char input[10];
    echo();
    getstr(input);
    noecho();
    if (strcmp(input, "3") == 0) {
        current_money += final_money;
        modify_money_of_user(email, current_money);
        mvprintw(9, 5, "Correct! %d has been added to your wallet.", final_money);
        mvprintw(10, 5, "New Wallet Balance: %d", current_money);
    } else {
        mvprintw(9, 5, "Incorrect! No money added.");
    }
    mvprintw(12, 5, "Press any key to return.");
    refresh();
    getch();
    menu1();
    clear();
}

char c[]=" ";
char* selected_cat=c;

void categories() {
    clear();
    //mvprintw(5, 10, "Categories function called.");
    const char *a[4][2] = {
        {"Books", "Electronics"},               //    const char* categ[7]= {"Books","Electronics","Fashion","Sports and Fitness","Games","Edibles","Home and Kitchen"};
        {"Fashion", "Sports and Fitness"},{"Games","Edibles"},{"Home and Kitchen","BACK"}
    };
    void (*b[4][2])() = {
        {filter1, filter1},
        {filter1, filter1},{filter1,filter1},{filter1,menu1}
    };

    buttonselect2d(4, 2, a, b,5,50);
    refresh();
    getch();
}

void settings() {
    clear();

    const char *a[1][2] = {
        {"BACK", "LOGOUT"}
    };
    void (*b[1][2])() = {
        {menu1, authpage}
    };

    buttonselect2d(1, 2, a, b, 5, 50);
    refresh();
    getch();
}

void exitprogram(){
    initscr();
    clear();
    endwin();
    exit(0);
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

    const char *a[3][2] = {
        {"CART", "WALLET"},
        {"CATEGORIES", "SETTINGS"},
        {"Quit",""}
    };
    void (*b[3][2])() = {
        {cart, wallet},
        {categories, settings},
        {exitprogram,exitprogram}
    };

    buttonselect2d(3, 2, a, b,5,102);

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
                
                if(strcmp(a[i][1],"")==0){
                    if (i == tco[0]) {
                    attron(COLOR_PAIR(2));
                    mvprintw(i*4+row+30,column-5, "+--------------------------------+");
                    mvprintw(i*4+row+31,column-5, "|            %-18s  |", a[i][j]);
                    mvprintw(i*4+row+32,column-5, "+--------------------------------+");
                    attroff(COLOR_PAIR(2));
                } else {
                    attron(COLOR_PAIR(1));
                    mvprintw(i*4+row+30, column-5, "+--------------------------------+");
                    mvprintw(i*4+row+31, column-5, "|            %-18s  |", a[i][j]);
                    mvprintw(i*4+row+32, column-5, "+--------------------------------+");
                    attroff(COLOR_PAIR(1));
                }
                break;

                }
                else{
                if (i == tco[0] && j == tco[1]) {
                    attron(COLOR_PAIR(2));
                    mvprintw(i*4+row, j*50+column, "+--------------------------------+");
                    mvprintw(i*4+row+1, j*50+column, "|            %-18s  |", a[i][j]);
                    mvprintw(i*4+row+2, j*50+column, "+--------------------------------+");
                    attroff(COLOR_PAIR(2));
                } else {
                    attron(COLOR_PAIR(1));
                    mvprintw(i*4+row, j*50+column, "+--------------------------------+");
                    mvprintw(i*4+row+1, j*50+column, "|            %-18s  |", a[i][j]);
                    mvprintw(i*4+row+2, j*50+column, "+--------------------------------+");
                    attroff(COLOR_PAIR(1));
                }
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
        PlaceOrder(userdetails->id);
    }
    else if(strcmp(a[choice[0]][choice[1]],"BACK")==0){
        endwin();
        menu1();
        
    }

    else{
    clear();
    selected_cat=a[choice[0]][choice[1]];
    b[choice[0]][choice[1]]();
    endwin();}
}
