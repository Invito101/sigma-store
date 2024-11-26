#include "../headers.h"
#include <stdbool.h>
#include <ncurses.h> // Ensure this file exists and is in the correct path
#include <wchar.h> // This is temporary as I'm trying to put in unicode characters


int view_all(void);
void quit2(void);
int admin_home(void) {
    create_tables();
    // Initialize ncurses
    initscr();
    
    
    // Clear the screen and show options
    clear();

    view_all();

    // Cleanup ncurses
    endwin();
    return 0;
}

void quit2() {
    clear();
    endwin();
    exit(0);

}

int view_all()
{
    clear();
    const char *aa[3][2] = {
        {"View products by category","View all products"},
        {"View a particular product","Create product"},
        {"Delete product","Modify product"},
        // {"View bestsellers", "View highest rated products"}
    };
    void (*bb[3][2])() = {
        {(void *)view_category_wise,view_all_products},
        {view_particular,create_product1},
        {delete_product1,modify_product1},
        // {view_bestsellers,view_highest_rated}
    };


    int m = 3;
    int n = 2;
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
    init_pair(3, COLOR_BLUE , COLOR_BLACK);
    attron(COLOR_PAIR(3));
    mvprintw(10,5,"Press q to quit.");
    
    attroff(COLOR_PAIR(3));
    refresh();




mvprintw(2,55, "        _____ _____ _____ __  __             _____ _______ ____  _____  ______ ");
mvprintw(3, 60, "  / ____|_   _/ ____|  \\/  |   /\\      / ____|__   __/ __ \\|  __ \\|  ____|");
mvprintw(4, 60, " | (___   | || |  __| \\  / |  /  \\    | (___    | | | |  | | |__) | |__   ");
mvprintw(5, 60, "  \\___ \\  | || | |_ | |\\/| | / /\\ \\    \\___ \\   | | | |  | |  _  /|  __|  ");
mvprintw(6, 60, "  ____) |_| || |__| | |  | |/ ____ \\   ____) |  | | | |__| | | \\ \\| |____ ");
mvprintw(7, 60, " |_____/|_____\\_____|_|  |_/_/    \\_\\ |_____/   |_|  \\____/|_|  \\_\\______|");

refresh();

    

    while(true){
    
    for (int i = 0; i < sizer; i++) {
            for (int j = 0; j < sizec; j++) {
                int row;
                if (i==0) row = 20;
                else if (i==1) row = 25;
                else if (i==2) row = 30;
                int col= j==0? 55:105;

                if (i == tco[0] && j == tco[1]) {
                    // Highlight the selected button
                    attron(COLOR_PAIR(2));
                    mvprintw(row, col, "+--------------------------------+");
                    mvprintw(row + 1, col, "|  %-30s|", aa[i][j]);
                    mvprintw(row + 2, col, "+--------------------------------+");
                    attroff(COLOR_PAIR(2));
                } else {
                    // Render the non-selected buttons
                    attron(COLOR_PAIR(1));
                    mvprintw(row, col, "+--------------------------------+");
                    mvprintw(row + 1, col, "|  %-30s|", aa[i][j]);
                    mvprintw(row + 2, col, "+--------------------------------+");
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
        else if(ch == 'Q'|| ch == 'q'){
            endwin();
            exit(0);
        }

        
        else
        continue;

    } 

    bb[choice[0]][choice[1]]();

    endwin();
}



void selectany1func(int n,const char *a[],void (*b[])()) {
  
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
        mvprintw(1, 1, "Welcome! Please live:");
        attroff(COLOR_PAIR(1));
        for(int i=0;i<sizea;i++){
            if(i==tco){
                attron(COLOR_PAIR(2));
                mvprintw(3+i,3,"> %s",a[i]);
                attroff(COLOR_PAIR(2));
                refresh();
            }
            else{
                attron(COLOR_PAIR(1));
                mvprintw(3+i,3,"  %s",a[i]);
                attroff(COLOR_PAIR(1));
                refresh();
            }
        }
        
        attron(COLOR_PAIR(1));
        mvprintw(n+4, 3, "Use arrow keys to navigate, Enter to select1.");
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

