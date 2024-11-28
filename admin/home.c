#include "../headers.h"
#include <stdbool.h>
#include <ncurses.h> // Ensure this file exists and is in the correct path
#include <wchar.h> // This is temporary as I'm trying to put in unicode characters


int view_all(void);
void quit2(void);
int admin_home(void) {
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
    const char *aa[6][2] = {
        {"View products by category","View all products"},
        {"View a particular product","Create product"},
        {"Delete product","Modify product"},
        {"View Bestselling Products", "View Top Rated Products"},
        {"Complete order","Order History"},
        {"Settings","Quit"}
    };
    void (*bb[6][2])() = {
        {(void *)view_category_wise,view_all_products},
        {view_particular,create_product1},
        {delete_product1,modify_product1},
        {view_bestsellers,view_highest_rated},
        {complete_order1,order_history1},
        {settings2,quit2}
    };


    int m = 6;
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
    init_pair(4, COLOR_YELLOW , COLOR_YELLOW);

    refresh();

char categories[][50] = {"Books","Electronics","Fashion","Sports and Fitness","Games","Edibles","Home and Kitchen"};


mvprintw(2,5, "        _____ _____ _____ __  __             _____ _______ ____  _____  ______ ");
mvprintw(3, 10, "  / ____|_   _/ ____|  \\/  |   /\\      / ____|__   __/ __ \\|  __ \\|  ____|");
mvprintw(4, 10, " | (___   | || |  __| \\  / |  /  \\    | (___    | | | |  | | |__) | |__   ");
mvprintw(5, 10, "  \\___ \\  | || | |_ | |\\/| | / /\\ \\    \\___ \\   | | | |  | |  _  /|  __|  ");
mvprintw(6, 10, "  ____) |_| || |__| | |  | |/ ____ \\   ____) |  | | | |__| | | \\ \\| |____ ");
mvprintw(7, 10, " |_____/|_____\\_____|_|  |_/_/    \\_\\ |_____/   |_|  \\____/|_|  \\_\\______|");
attron(COLOR_PAIR(3) | A_BOLD);
mvprintw(5, 150, "GRAPH OF NUMBER OF PRODUCTS IN EACH CATEGORY");
for (int i =0 ; i<7 ;i++)
{
    char name[50];
    strcpy(name,categories[i]);
    int l = strlen(name);
    mvprintw(36 - 3*i,124 - l,"%s",name);

}
attroff(COLOR_PAIR(3) | A_BOLD);
attron(COLOR_PAIR(2) | A_BOLD);
for (int j =0;j<(COLS - 127)/3;j+=5)
{
    mvprintw(39,126+j*3,"%d",j);
}
attroff(COLOR_PAIR(2) | A_BOLD);

refresh();





    int pad_rows = 3*7+20;
    int pad_cols = 200;
    WINDOW *pad2 = newpad(pad_rows, pad_cols);
    if (pad2 == NULL) {
        endwin();
        printf("Error creating pad.\n");
        return 0;
    }



        for (int i = 0; i < 7; i++) {
        int bar_height = count_all_category_products(categories[i]); // Height of each bar
        for (int j = 0; j < bar_height; j++) {
            wattron(pad2,COLOR_PAIR(4));
            mvwprintw(pad2, 28 - 3*i, 3*j+1, "   "); 
            wattroff(pad2, COLOR_PAIR(4));
        }
        attron(A_BOLD);
        mvwprintw(pad2, 28 - 3*i, 3*bar_height +2 , "%d",bar_height);
        attroff(A_BOLD);

  }




    int start_row = 0, start_col = 0 ;
    int display_rows = LINES < 30 ? LINES : 30;
    int display_cols = COLS < 100 ? COLS : 100;
    prefresh(pad2, start_row, start_col, 8, 126,  10 +display_rows - 4, COLS - 2);


    while(true){
            int height = 7*3 + 5;
    int width = COLS - 2;

        for (int y = 0; y < height; y++) {
        mvaddch( 8+30 - y -1, 125, ACS_VLINE);
    }
    // mvaddch(10,125,ACS_UARROW);

    // Draw the horizontal axis
    for (int x = 0; x < width - 125 ; x++) {
        mvaddch( 8+30, 125+x, ACS_HLINE);
    }
    // mvaddch(37, COLS - 2 , ACS_RARROW);
    // Draw intersection (origin)
    mvaddch(8+30, 125, ACS_LLCORNER); // Axis intersection
    refresh();

        prefresh(pad2, start_row, start_col, 8, 126,  10 +display_rows - 4, COLS - 2);
    
    for (int i = 0; i < sizer; i++) {
        
        
            for (int j = 0; j < sizec; j++) {
                int row;
                if (i==0) row = 36 - 20;
                else if (i==1) row = 36 - 16;
                else if (i==2) row = 36 - 12;
                else if (i==3) row = 36 - 8;
                else if (i==4) row = 36 - 4;
                else if (i==5) row = 36;
                int col= j==0? 5:55;

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


        
        else
        continue;

    } 

    bb[choice[0]][choice[1]]();

    endwin();
    return 0;
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

void settings2() {
    clear();

    // Define the labels and corresponding functions for the buttons
    const char *a[1][2] = {
        {"BACK", "LOGOUT"}
    };
    void (*b[1][2])() = {
        {(void*)admin_home, authpage} // Map "Back" to menu1 and "Logout" to login1
    };

    // Use buttonselect2d to display the buttons
    buttonselect2d(1, 2, a, b, 5, 50);
    refresh();
    getch();
}