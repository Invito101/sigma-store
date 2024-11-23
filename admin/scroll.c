#include <ncurses.h>

void scr() {
    clear();
    // Create a pad of 1000 rows and 200 columns
    int pad_rows = 1000;
    int pad_cols = 200;
    WINDOW *pad = newpad(pad_rows, pad_cols);
    if (pad == NULL) {
        endwin();
        printf("Error creating pad.\n");
        return 1;
    }

    // Fill the pad with some content
    for (int i = 0; i < pad_rows; i++)  {
            mvwprintw(pad, i, 0, "%d", i); // Example content
        
    }

    // Display part of the pad on the screen
    int start_row = 0, start_col = 0;
    int display_rows = LINES < 40 ? LINES : 40;
    int display_cols = COLS < 50 ? COLS : 50;
    prefresh(pad, start_row, start_col, 0, 0, display_rows - 1, display_cols - 1);

    int ch;
    while ((ch = getch()) != 'q') { // Press 'q' to exit
        switch (ch) {
            case KEY_UP:
                if (start_row > 0) start_row--;
                break;
            case KEY_DOWN:
                if (start_row < pad_rows - display_rows) start_row++;
                break;
            case KEY_LEFT:
                if (start_col > 0) start_col--;
                break;
            case KEY_RIGHT:
                if (start_col < pad_cols - display_cols) start_col++;
                break;
        }
        prefresh(pad, start_row, start_col, 0, 0, display_rows - 1, display_cols - 1);
    }

    // Cleanup
    delwin(pad);
}

void selectany1(int n,const char *a[],void (*b[])()) {
  
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

