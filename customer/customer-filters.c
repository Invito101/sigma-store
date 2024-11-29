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
    int flag=0;
    int choice[2]={0,0};
    int tco[2] = {0,0}; //the_chosen_one
    
    int sizer=m;
    int sizec=n;
    int ch;


    initscr();
    raw();
    start_color();
    cbreak();
    noecho();
    curs_set(0);     

    keypad(stdscr, TRUE);

    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_YELLOW, COLOR_BLACK);

    attron(COLOR_PAIR(1));
    mvprintw(5,75,"Select a filter. Press 'b' to go back to menu");
    attroff(COLOR_PAIR(1));

    while(true){
    
    for (int i = 0; i < sizer; i++) {
            for (int j = 0; j < sizec; j++) {
                

                if (i == tco[0] && j == tco[1]) {
                    attron(COLOR_PAIR(2));
                    mvprintw(i*4+row, j*60+column,   "+-----------------------------------------------------+");
                    mvprintw(i*4+row+1, j*60+column, "|            %s", a[i][j]);
                    mvprintw(i*4+row+2, j*60+column, "+-----------------------------------------------------+");
                    attroff(COLOR_PAIR(2));
                } else {
                    attron(COLOR_PAIR(1));
                    mvprintw(i*4+row, j*60+column,   "+-----------------------------------------------------+");
                    mvprintw(i*4+row+1, j*60+column, "|            %s", a[i][j]);
                    mvprintw(i*4+row+2, j*60+column, "+-----------------------------------------------------+");
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
        else if(ch=='b'){
            flag=1;
            break;
        }


        else
        continue;

    } 
    if(flag==0){
    clear();
    
    Product* products= (b[choice[0]][choice[1]])(numberofprods,selected_cat);

    //Product* products = get_all_category_products(numberofprods,selected_cat);
    
    if(products==NULL){
        
        attron(COLOR_PAIR(1));
        mvprintw(5,10,"No products in this category! Press any key to go back to menu.");
        attroff(COLOR_PAIR(1));        
        getch();
        endwin();
        menu1();
    
    }
    else{
    showproducts(*numberofprods,products,5,1,0,0);
    

    endwin();
    }
    }
    else{
        menu1();
        return;
    }
}

void filter1(void){
    const char* a[2][2] = {
    {"Sort by Price (Descending)", "Sort by Price (Ascending)"},
    {"Sort by Number of Sales (Descending)", "Sort by Ratings(Descending)"}
};

    Product* (*b[2][2])(int*, char*) = {
    {get_all_category_products_price_desc, get_all_category_products_price_asc},
    {get_all_category_products_top_sold, get_all_category_products_top_rated}
};


    

    filterselect2d(2, 2, a, b,15,40);
}

