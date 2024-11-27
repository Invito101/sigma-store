#include <stdio.h>
#include <stdbool.h>
#include <ncurses.h>
#include "../headers.h"
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

int zero=0;
int *numberofprods=&zero;


void filterselect2d(int m,int n,const char *a[m][n],Product* (*b[m][n])(int*,char*),int row, int column) {
  
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
                    mvprintw(i*4+row, j*50+column,   "+----------------------------------------+");
                    mvprintw(i*4+row+1, j*50+column, "|            %-18s  |", a[i][j]);
                    mvprintw(i*4+row+2, j*50+column, "+----------------------------------------+");
                    attroff(COLOR_PAIR(2));
                } else {
                    // Render the non-selected buttons
                    attron(COLOR_PAIR(1));
                    mvprintw(i*4+row, j*50+column,   "+----------------------------------------+");
                    mvprintw(i*4+row+1, j*50+column, "|            %-18s  |", a[i][j]);
                    mvprintw(i*4+row+2, j*50+column, "+----------------------------------------+");
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
    
    clear();
    
    Product* products= (b[choice[0]][choice[1]])(numberofprods,selected_cat);

    //Product* products = get_all_category_products(numberofprods,selected_cat);
    
    showproducts(*numberofprods,products,5,1,0,0);
    

    endwin();
}

void filter1(void){
    const char* a[2][1] = {
        {"Sort by price(High to low)"},
        {"Sort by price(Low to high)"}
    };
    Product* (*b[2][1])(int*,char*) = {
        {get_all_category_products},
        {get_all_category_products}
    };

    // Clear the screen and show options
    
    
    filterselect2d(2, 1, a, b,5,90);
}
