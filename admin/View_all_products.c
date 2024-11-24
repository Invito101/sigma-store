#include "../headers.h"
#include <stdio.h>
#include <stdbool.h>
#include <ncurses.h> // Ensure this file exists and is in the correct path
#include <wchar.h> // This is temporary as I'm trying to put in unicode characters
int max_l=100;
int view_category_wise()
{

    return 0;
}

void view_particular()
{   char *name;
    clear();
    endwin();
    
    create_tables();
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

    move(2, 10);
    clrtoeol();

    attron(COLOR_PAIR(1));
    mvprintw(2, 10, "%s: ", "Enter the name of the product: ");
    attroff(COLOR_PAIR(1));
    refresh();

    attron(COLOR_PAIR(2));
    echo();
    getnstr(name, max_l);
    noecho();
    attroff(COLOR_PAIR(2));

    move(2 + 1, 10); // makes sure it doesnt clash with any error message
    clrtoeol();


}

void view_all_products()
{
    clear();
    endwin();
    
    create_tables();
    initscr();
    raw();
    clear();
    start_color();
    cbreak();
    noecho();
    curs_set(0);     

    keypad(stdscr, TRUE);

    mvprintw(2,55, "        _____ _____ _____ __  __             _____ _______ ____  _____  ______ ");
mvprintw(3, 60, "  / ____|_   _/ ____|  \\/  |   /\\      / ____|__   __/ __ \\|  __ \\|  ____|");
mvprintw(4, 60, " | (___   | || |  __| \\  / |  /  \\    | (___    | | | |  | | |__) | |__   ");
mvprintw(5, 60, "  \\___ \\  | || | |_ | |\\/| | / /\\ \\    \\___ \\   | | | |  | |  _  /|  __|  ");
mvprintw(6, 60, "  ____) |_| || |__| | |  | |/ ____ \\   ____) |  | | | |__| | | \\ \\| |____ ");
mvprintw(7, 60, " |_____/|_____\\_____|_|  |_/_/    \\_\\ |_____/   |_|  \\____/|_|  \\_\\______|");

refresh();


    int count = count_all_products(); 

    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_YELLOW, COLOR_BLACK);
    init_pair(3, COLOR_BLUE , COLOR_BLACK);
    attron(COLOR_PAIR(3));
    attron(A_BOLD);
    mvprintw(10,90,"%s","PRODUCT INFORMATION");
    attroff(A_BOLD);
    mvprintw(12,3,"%s","Press Enter to return to home page.");
    mvprintw(45,3,"%s","Use PAGE_UP and PAGE_DOWN to see all products.");
    attroff(COLOR_PAIR(3));
    refresh();
    int pad_rows = 7*count+2;
    int pad_cols = 200;
    WINDOW *pad2 = newpad(pad_rows, pad_cols);
    if (pad2 == NULL) {
        endwin();
        printf("Error creating pad.\n");
        return;

    }

    int size;
    Product *products = get_all_products(&size);


    for (int i = 0; i < count; i++) {
        int row = 7*i;
        wattron(pad2,COLOR_PAIR(1));
        mvwprintw(pad2, row, 0, "Name:");       // Print product name
        mvwprintw(pad2, row + 1, 0, "Price:"); // Print product category
        mvwprintw(pad2, row + 2, 0, "Description:");
        mvwprintw(pad2, row + 3, 0, "Category:");
        mvwprintw(pad2, row + 4, 0, "Manufactured by:");
        wattroff(pad2,COLOR_PAIR(1));

        wattron(pad2,COLOR_PAIR(2));
        mvwprintw(pad2, row, 17, "%s", products[i].name);       // Print product name
        mvwprintw(pad2, row + 1, 17, "%d", products[i].price); // Print product category
        mvwprintw(pad2, row + 2, 17, "%s", products[i].description);
        mvwprintw(pad2, row + 3, 17, "%s", products[i].category);
        mvwprintw(pad2, row + 4, 17, "%s", products[i].manufacturedBy);
        wattroff(pad2,COLOR_PAIR(2));
        
    }


    int start_row = 0, start_col = 0;
    int display_rows = LINES < 40 ? LINES : 40;
    int display_cols = COLS < 130 ? COLS : 130;
    prefresh(pad2, start_row, start_col, 15, 80, display_rows - 1, display_cols - 1);

    int ch;
        
        while(true){
        ch = getch();

        if (ch=='\n') break;
        else if (ch== KEY_PPAGE){
                if (start_row > 0) start_row--;
                prefresh(pad2, start_row, start_col, 15, 80, display_rows - 1, display_cols - 1);
        }
        else if (ch == KEY_NPAGE){
                if (start_row < (pad_rows - display_rows)+15) start_row++;
                prefresh(pad2, start_row, start_col, 15, 80, display_rows - 1, display_cols - 1);
        }
        else if (ch== KEY_LEFT){
                if (start_col > 0) start_col--;
                prefresh(pad2, start_row, start_col, 15, 80, display_rows - 1, display_cols - 1);
        }
        else if(ch==KEY_RIGHT){
                if (start_col < (pad_cols - display_cols)) start_col++;
                prefresh(pad2, start_row, start_col, 15, 80, display_rows - 1, display_cols - 1);
        }
        }


            clear();
            delwin(pad2);
            endwin();
            admin_home();
}

void create_product1()
{   
    clear();
    endwin();
    
    create_tables();
    initscr();
    raw();
    clear();
    start_color();
    cbreak();
    noecho();
    curs_set(0);     

    keypad(stdscr, TRUE);

    int max_len = 100;
    char name[max_len],price[max_len];
    char description[max_len], category[max_len], manufacturedBy[max_len];


    init_pair(1, COLOR_GREEN, COLOR_BLACK); 
    init_pair(2, COLOR_YELLOW, COLOR_BLACK); 

    attron(COLOR_PAIR(1));
    mvprintw(2, 10, "Create a new product:");
    mvprintw(3, 10, "Press Enter to submit each field, and type carefully:");
    attroff(COLOR_PAIR(1));
    refresh();

    get_valid_input_for_product(5, "Name", name, max_len, is_valid_product_name);
    get_valid_input_for_product(6, "Price", price, max_len, is_valid_price);
    get_valid_input_for_product(7, "Description",description, max_len, NULL);

    const char* categ[7]= {"Books","Electronics","Fashion","Sports and Fitness","Games","Edibles","Home and Kitchen"};
    int selected = selectany1(7,categ);
    strncpy(category, categ[selected], max_len);

    attron(COLOR_PAIR(1));
    mvprintw(8,10, "Category");
    attroff(COLOR_PAIR(1));

    attron(COLOR_PAIR(2));
    mvprintw(8,20, "%s",category);
    attroff(COLOR_PAIR(2));
    refresh();
    get_valid_input_for_product(9, "Manufactured by",manufacturedBy, max_len, is_valid_manufacturedBy);

    int sf = create_product(name,atoi(price),description,category, manufacturedBy);

    clear();
    if (sf==0){
    attron(COLOR_PAIR(1));
    mvprintw(5, 10, "Product created successfully! Here's the data you entered:");
    mvprintw(6, 10, "Name:");
    mvprintw(7, 10, "Price:");
    mvprintw(8, 10, "Description:");
    mvprintw(9, 10, "Category:");
    mvprintw(10, 10, "Manufactured by:");
    attroff(COLOR_PAIR(1));
    attron(COLOR_PAIR(2));
    mvprintw(6, 30, "%s", name);
    mvprintw(7, 30, "%s", price);
    mvprintw(8, 30, "%s", description);
    mvprintw(9, 30, "%s", category);
    mvprintw(10, 30, "%s", manufacturedBy);
    attroff(COLOR_PAIR(2));
    refresh();
    }
    else 
    {
        attron(COLOR_PAIR(1));
    mvprintw(10, 10, "Product not created.");
    attroff(COLOR_PAIR(1));
    }
    attron(COLOR_PAIR(1));
    mvprintw(15, 10, "Press any key to return to the menu.");
    attroff(COLOR_PAIR(1));
    getch();
    endwin();
    admin_home();
    
}


void modify_product1()
{
    clear();
    mvprintw(5, 10, "modify_product function called");

    refresh();
}
void delete_product1()
{
    clear();
    mvprintw(5, 10, "delete_product function called");

    refresh();
}
void quit3()
{
    clear();
    endwin();
    exit(0);
}





int selectany1(int n,const char *a[]) {
  
    int choice=0;
    int tco = 0; //the_chosen_one
    
    int sizea=n;
    int ch;
    //char opencircle[]="\u25EF";
    //char closedcircle[]="\u2B24";

    raw();
    start_color();
    cbreak();
    noecho();
    curs_set(0);     

    keypad(stdscr, TRUE);

    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_YELLOW, COLOR_BLACK);

    while(true){
        attron(COLOR_PAIR(1));
        mvprintw(8, 10, "Category: ");
        attroff(COLOR_PAIR(1));
        for(int i=0;i<sizea;i++){
            if(i==tco){
                attron(COLOR_PAIR(2));
                mvprintw(8+i,20,"> %s",a[i]);
                attroff(COLOR_PAIR(2));
                refresh();
            }
            else{
                attron(COLOR_PAIR(1));
                mvprintw(8+i,20,"  %s",a[i]);
                attroff(COLOR_PAIR(1));
                refresh();
            }
        }
        
        // attron(COLOR_PAIR(1));
        // mvprintw(n+4, 3, "Use arrow keys to navigate, Enter to select1.");
        // attroff(COLOR_PAIR(1));
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
    for(int k=0;k<n;k++)
    {
        move(8+k,10);
        clrtoeol();
    }
    refresh();

    return choice;
}

