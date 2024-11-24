#include "../headers.h"
#include <stdio.h>
#include <stdbool.h>
#include <ncurses.h> // Ensure this file exists and is in the correct path
#include <wchar.h> // This is temporary as I'm trying to put in unicode characters


int view_all(void);
void quit2(void);
int new(void) {
    create_tables();
    // Initialize ncurses
    initscr();
    
    const char *a[2]={"View All Products","Quit"};
    void (*b[])()={(void *)view_all,quit2};
    
    // Clear the screen and show options
    clear();

    view_all();

    // Cleanup ncurses
    endwin();
    return 0;
}

<<<<<<< HEAD

=======
>>>>>>> d976f5b6fd0a138c447d054bf5ad74bfdebcddcf
void quit2() {
    clear();
    endwin();
    exit(0);

}

int view_all()
{
    clear();
     const char *aa[5]={"View products by category","Create product","Delete product","Modify product","Quit"};
    void (*bb[])()={(void *)view_category_wise,create_product1,delete_product1,modify_product1,quit3};



    int choice=0;
    int tco = 0; //the_chosen_one
    int n=5;
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
    int count = count_all_products(); 

    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_YELLOW, COLOR_BLACK);
    attron(COLOR_PAIR(1));
    mvprintw(12,3,"%s","Product information");
    attroff(COLOR_PAIR(1));
    refresh();
    int pad_rows = count*4+2;
    int pad_cols = 200;
    WINDOW *pad = newpad(pad_rows, pad_cols);
    if (pad == NULL) {
        endwin();
        printf("Error creating pad.\n");
        return 1;

    }

    int size;aa
    Product *products = get_all_products(&size);


    for (int i = 0; i < count; i++) {
  
        int row = 4 * i;
        wattron(pad,COLOR_PAIR(1));
        mvwprintw(pad, row, 0, "%s", products[i].name);       // Print product name
        mvwprintw(pad, row + 1, 0, "%s", products[i].category); // Print product category
        wattroff(pad,COLOR_PAIR(1));
    }


    int start_row = 0, start_col = 0;
    int display_rows = LINES < 45 ? LINES : 45;
    int display_cols = COLS < 130 ? COLS : 130;
    prefresh(pad, start_row, start_col, 15, 60, display_rows - 1, display_cols - 1);


    while(true){
        clear();
        attron(COLOR_PAIR(1));
        mvprintw(1, 1, "Welcome! Please live:");
        attroff(COLOR_PAIR(1));
        for(int i=0;i<sizea;i++){
            if(i==tco){
                attron(COLOR_PAIR(2));
                mvprintw(3+i,3,"> %s",aa[i]);
                attroff(COLOR_PAIR(2));
                refresh();
            }
            else{
                attron(COLOR_PAIR(1));
                mvprintw(3+i,3,"  %s",aa[i]);
                attroff(COLOR_PAIR(1));
                refresh();
            }
        }
        
        attron(COLOR_PAIR(1));
        mvprintw(n+4, 3, "Use arrow keys to navigate, Enter to select1.");
        attroff(COLOR_PAIR(1));
        refresh();





    prefresh(pad, start_row, start_col, 15, 60, display_rows - 1, display_cols - 1);



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
        else if (ch== KEY_PPAGE){
                if (start_row > 0) start_row--;
                prefresh(pad, start_row, start_col, 15, 60, display_rows - 1, display_cols - 1);
        }
        else if (ch == KEY_NPAGE){
                if (start_row < pad_rows - display_rows) start_row++;
                prefresh(pad, start_row, start_col, 15, 60, display_rows - 1, display_cols - 1);
        }
        else if (ch== KEY_LEFT){
                if (start_col > 0) start_col--;
                prefresh(pad, start_row, start_col, 15, 60, display_rows - 1, display_cols - 1);
        }
        else if(ch==KEY_RIGHT){
                if (start_col < pad_cols - display_cols) start_col++;
                prefresh(pad, start_row, start_col, 15, 60, display_rows - 1, display_cols - 1);
        }
        
        else
        continue;
    }


    bb[choice]();
    endwin();
    delwin(pad);
    return 0;
}
