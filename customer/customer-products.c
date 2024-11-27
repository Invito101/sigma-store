#include <stdio.h>
#include <ncurses.h>
#include "../headers.h"

void cart(void);
void wallet(void);
void categories(void);
void settings(void);
void showproducts(int count,Product* b, int row, int col);


void showproducts(int count,Product* b, int row, int col) {
    int (*c[2])(int,int)={AddItemToOrder,DecreaseItemQuantity};
    int choice[2] = {0, 0};
    int tco[2] = {0, 0}; // the_chosen_one

    int sizer = count;
    int sizec = 2;
    int ch;

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
    init_pair(3, COLOR_BLUE,COLOR_BLACK);

    const char *box[] = {
        "+--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+\n",
        "|                       %s                                                                                                                                                                                 |\n",
        "|                                                                                                                                                                                                        |\n",
        "|                                                                                                                                                                                                        |\n",
        "|                                                                                                                                                                                                        |\n",
        "|                                                                                                                                                                                                        |\n",
        "|                                                                                                                                                                                                        |\n",
        "|                                                                                                                                                                                                        |\n",
        "+--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+\n"};

    const char *plus[] = {
        "     +-------+\n",
        "     |   _   |\n",
        "Add  | _| |_ |\n",
        "to   ||_   _||\n",
        "Cart |  |_|  |\n",
        "     |       |\n",
        "     +-------+\n"};

    const char *minus[] = {
        "      +-------+\n",
        "      |       |\n",
        "Remove|  ___  |\n",
        "from  | |___| |\n",
        "cart  |       |\n",
        "      |       |\n",
        "      +-------+\n"};

    while (true) {
        clear();
        attron(COLOR_PAIR(1));
        mvprintw(5, 10, "Welcome to %s:",selected_cat);
        attroff(COLOR_PAIR(1));

        for (int i = 0; i < sizer; i++) {

            if (i == tco[0]&&tco[1]==0) {
                attron(COLOR_PAIR(2));
                for (int j = 0; j < 9; j++) { // Render the main box
                    mvprintw(row * (1 + 2 * i) + j, col, box[j],b[i].name);   //get_product_by_id(b[i]->id)->name

                }
                attroff(COLOR_PAIR(2));

                // Render the plus box on the right side of the current box
                
                attron(COLOR_PAIR(3));

                for (int k = 0; k < 7; k++) {
                    mvprintw(row * (1 + 2 * i) + k + 1, col + 160, plus[k]);

                }
                
                attroff(COLOR_PAIR(3));

                attron(COLOR_PAIR(2));
                
                for (int k = 0; k < 7; k++) {
                    mvprintw(row * (1 + 2 * i) + k + 1, col + 180, minus[k]);

                }
                attroff(COLOR_PAIR(2));

                } 
                else if(tco[0]==i&&tco[1]==1){
                attron(COLOR_PAIR(2));

                for (int j = 0; j < 9; j++) { // Render the main box
                    mvprintw(row * (1 + 2 * i) + j, col, box[j],b[i].name);

                }

                // Render the plus box on the right side of the non-selected box
                for (int k = 0; k < 7; k++) {
                    mvprintw(row * (1 + 2 * i) + k + 1, col + 160, plus[k]);

                }
                attroff(COLOR_PAIR(2));
                attron(COLOR_PAIR(3));

                // Render the minus box below the plus box
                for (int k = 0; k < 7; k++) {
                    mvprintw(row * (1 + 2 * i) + k + 1, col + 180, minus[k]);

                }
                attroff(COLOR_PAIR(3));

            }
            else{

                attron(COLOR_PAIR(1));
                
                for (int j = 0; j < 9; j++) { // Render the main box
                    mvprintw(row * (1 + 2 * i) + j, col, box[j],b[i].name);

                }

                // Render the plus box on the right side of the non-selected box
                for (int k = 0; k < 7; k++) {
                    mvprintw(row * (1 + 2 * i) + k + 1, col + 160, plus[k]);

                }
                

                // Render the minus box below the plus box
                for (int k = 0; k < 7; k++) {
                    mvprintw(row * (1 + 2 * i) + k + 1, col + 180, minus[k]);

                }
                attroff(COLOR_PAIR(1));

            

            }
            /*
printw("Product %d:\n", choice[0] + 1);
printw("ID: %d\n", b[choice[0]].id);
printw("Name: %s\n", b[choice[0]].name);
printw("Price: %d\n", b[choice[0]].price);
printw("Description: %s\n", b[choice[0]].description);
printw("Category: %s\n", b[choice[0]].category);
printw("Manufactured By: %s\n", b[choice[0]].manufacturedBy);
printw("Rating: %.2f\n", b[choice[0]].rating);
printw("Number of Ratings: %d\n", b[choice[0]].noOfRatings);
printw("Amount Bought: %d\n", b[choice[0]].amountBought);
printw("Created At: %s\n", ctime(&(b[choice[0]].createdAt))); // Convert time_t to string
printw("\n"); // Add a blank line after the selected product
refresh();*/
        }
            refresh();


        ch = getch();

        if (ch == '\n') {
            choice[0] = tco[0];
            choice[1] = tco[1];
            break;
        } else if (ch == KEY_DOWN) {
            if (tco[0] == sizer - 1)
                tco[0] = 0;
            else
                tco[0] += 1;

        } else if (ch == KEY_UP) {
            if (tco[0] == 0)
                tco[0] = sizer - 1;
            else
                tco[0] -= 1;

        } else if (ch == KEY_RIGHT) {
            if (tco[1] == sizec - 1)
                tco[1] = 0;
            else
                tco[1] += 1;
        } else if (ch == KEY_LEFT) {
            if (tco[1] == 0)
                tco[1] = sizec - 1;
            else
                tco[1] -= 1;
        } else
            continue;
    }
    

    //Product* selected_product = b[choice[0]];


    c[choice[1]](b[choice[0]].id, userdetails->id);  

    endwin();
}

