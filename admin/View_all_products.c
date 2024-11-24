#include "../headers.h"
#include <stdio.h>
#include <stdbool.h>
#include <ncurses.h> // Ensure this file exists and is in the correct path
#include <wchar.h> // This is temporary as I'm trying to put in unicode characters

int view_category_wise()
{
    clear();
    create_tables();
    

     const char *aa[5]={"View products by category","Create product","Delete product","Modify product","Quit"};
    void (*bb[])()={view_category_wise,create_product1,delete_product1,modify_product1,quit3};



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

    int size;
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
    int display_cols = COLS < 50 ? COLS : 50;
    prefresh(pad, start_row, start_col, 15, 0, display_rows - 1, display_cols - 1);


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





    prefresh(pad, start_row, start_col, 15, 0, display_rows - 1, display_cols - 1);



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
                prefresh(pad, start_row, start_col, 15, 0, display_rows - 1, display_cols - 1);
        }
        else if (ch == KEY_NPAGE){
                if (start_row < pad_rows - display_rows) start_row++;
                prefresh(pad, start_row, start_col, 15, 0, display_rows - 1, display_cols - 1);
        }
        else if (ch== KEY_LEFT){
                if (start_col > 0) start_col--;
                prefresh(pad, start_row, start_col, 15, 0, display_rows - 1, display_cols - 1);
        }
        else if(ch==KEY_RIGHT){
                if (start_col < pad_cols - display_cols) start_col++;
                prefresh(pad, start_row, start_col, 15, 0, display_rows - 1, display_cols - 1);
        }
        
        else
        continue;
    }


    bb[choice]();
    endwin();
    delwin(pad);
    return 0;
}

void create_product1()
{
    clear();
    


}
void modify_product1()
{
    clear();
    mvprintw(5, 10, "modify_product function called");

    refresh();
}


void delete_product1() {
    clear();
    initscr();
    raw();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    start_color();

    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_YELLOW, COLOR_BLACK);

    int count = count_all_products();
    if (count == 0) {
        attron(COLOR_PAIR(2));
        mvprintw(5, 10, "No products available to delete.");
        attroff(COLOR_PAIR(2));
        refresh();
        getch();
        endwin();
        return;
    }

    Product *products = get_all_products(&count);
    if (products == NULL) {
        endwin();
        fprintf(stderr, "Failed to retrieve products.\n");
        return;
    }

    // Extract unique categories
    const char categories[][50] = {"Books","Electronics","Fashion","Sports and Fitness","Games","Edibles","Home and Kitchen"};
    int category_count = 7;


    int category_choice = 0;
    int ch;

    while (true) {
        clear();
        attron(COLOR_PAIR(2));
        mvprintw(1, 10, "Select a category:");
        attroff(COLOR_PAIR(2));

        // Display categories
        for (int i = 0; i < category_count; i++) {
            if (i == category_choice) {
                attron(COLOR_PAIR(2));
                mvprintw(3 + i, 10, "> %s", categories[i]);
                attroff(COLOR_PAIR(2));
            } else {
                attron(COLOR_PAIR(1));
                mvprintw(3 + i, 12, "%s", categories[i]);
                attroff(COLOR_PAIR(1));
            }
        }

        mvprintw(LINES - 2, 3, "Use arrow keys to navigate, Enter to select, q to quit.");
        refresh();

        ch = getch();
        if (ch == 'q') {
            break;
        }

        switch (ch) {
            case KEY_UP:
                category_choice = (category_choice == 0) ? category_count - 1 : category_choice - 1;
                break;
            case KEY_DOWN:
                category_choice = (category_choice == category_count - 1) ? 0 : category_choice + 1;
                break;
            case '\n': {
                // Display products under the selected category
                clear();
                attron(COLOR_PAIR(2));
                mvprintw(1, 10, "Select a product to delete from category: %s", categories[category_choice]);
                attroff(COLOR_PAIR(2));

                int filtered_indices[count];
                int filtered_count = 0;

                for (int i = 0; i < count; i++) {
                    if (strcmp(products[i].category, categories[category_choice]) == 0) {
                        filtered_indices[filtered_count++] = i;
                    }
                }

                if (filtered_count == 0) {
                    mvprintw(3, 10, "No products available in this category.");
                    mvprintw(LINES - 2, 3, "Use arrow keys to navigate, Enter to delete, b to go back.");
                    refresh();
                    getch();
                    break;
                }

                int product_choice = 0;

                while (true) {
                    clear();
                    attron(COLOR_PAIR(2));
                    mvprintw(1, 10, "Select a product to delete from category: %s", categories[category_choice]);
                    attroff(COLOR_PAIR(2));

                    for (int i = 0; i < filtered_count; i++) {
                        int index = filtered_indices[i];
                        if (i == product_choice) {
                            attron(COLOR_PAIR(2));
                            mvprintw(3 + i, 10, "> %s", products[index].name);
                            attroff(COLOR_PAIR(2));
                        } else {
                            attron(COLOR_PAIR(1));
                            mvprintw(3 + i, 12, "%s", products[index].name);
                            attroff(COLOR_PAIR(1));
                        }
                    }

                    mvprintw(LINES - 2, 3, "Use arrow keys to navigate, Enter to delete, b to go back.");
                    refresh();

                    ch = getch();
                    if (ch == 'b') break;

                    switch (ch) {
                        case KEY_UP:
                            product_choice = (product_choice == 0) ? filtered_count - 1 : product_choice - 1;
                            break;
                        case KEY_DOWN:
                            product_choice = (product_choice == filtered_count - 1) ? 0 : product_choice + 1;
                            break;
                        case '\n': {
                            int delete_index = filtered_indices[product_choice];
                            attron(COLOR_PAIR(2));
                            mvprintw(LINES - 4, 10, "Are you sure you want to delete '%s'? (y/n)", products[delete_index].name);
                            attroff(COLOR_PAIR(2));
                            refresh();
                            ch = getch();
                            if (ch == 'y') {
                                delete_product(products[delete_index].name); // Assume a delete_product function exists
                                move(LINES-4,10);
                                clrtoeol();
                                attron(COLOR_PAIR(2));
                                mvprintw(LINES - 4, 10, "'%s' deleted successfully!", products[delete_index].name);
                                attroff(COLOR_PAIR(2));
                                getch();
                                clear();
                                new();
                                break;
                            }
                            refresh();
                            break;
                        }
                    }
                }
                break;
            }
        }
    }

    // Clean up
    endwin();
    free(products);
}

void quit3()
{
    clear();
    endwin();
    exit(0);
}
