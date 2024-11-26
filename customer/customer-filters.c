#include <stdio.h>
#include <ncurses.h>

void cart(void);
void wallet(void);
void categories(void);
void settings(void);
void cartselect(int m, int n, const char *a[m][n], void (*b[m][n])(), int row, int col);

int main(){
    const char *a[2][2] = {
        {"CART","WALLET"},{"CART","WALLET"}};
    void (*b[2][2])() = {
        {cart,wallet},{cart,wallet}};

    // Clear the screen and show options
    cartselect(2, 2, a, b,5,1);
}
void cartselect(int m, int n, const char *a[m][n], void (*b[m][n])(), int row, int col) {
    int choice[2] = {0, 0};
    int tco[2] = {0, 0}; // the_chosen_one

    int sizer = m;
    int sizec = n;
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
        "+-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+\n",
        "|                                                                                                                                                                               |\n",
        "|                                                                                                                                                                               |\n",
        "|                                                                                                                                                                               |\n",
        "|                                                                                                                                                                               |\n",
        "|                                                                                                                                                                               |\n",
        "|                                                                                                                                                                               |\n",
        "|                                                                                                                                                                               |\n",
        "+-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+\n"};

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
        mvprintw(5, 10, "Welcome! Please live:");
        attroff(COLOR_PAIR(1));

        for (int i = 0; i < sizer; i++) {
            if (i == tco[0]&&tco[1]==0) {
                attron(COLOR_PAIR(2));
                for (int j = 0; j < 9; j++) { // Render the main box
                    mvprintw(row * (1 + 2 * i) + j, col, box[j]);

                }
                attroff(COLOR_PAIR(2));

                // Render the plus box on the right side of the current box
                
                attron(COLOR_PAIR(3));

                for (int k = 0; k < 7; k++) {
                    mvprintw(row * (1 + 2 * i) + k + 1, col + 140, plus[k]);

                }
                
                attroff(COLOR_PAIR(3));

                attron(COLOR_PAIR(2));
                
                for (int k = 0; k < 7; k++) {
                    mvprintw(row * (1 + 2 * i) + k + 1, col + 160, minus[k]);

                }
                attroff(COLOR_PAIR(2));

                } 
                else if(tco[0]==i&&tco[1]==1){
                attron(COLOR_PAIR(2));

                for (int j = 0; j < 9; j++) { // Render the main box
                    mvprintw(row * (1 + 2 * i) + j, col, box[j]);

                }

                // Render the plus box on the right side of the non-selected box
                for (int k = 0; k < 7; k++) {
                    mvprintw(row * (1 + 2 * i) + k + 1, col + 140, plus[k]);

                }
                attroff(COLOR_PAIR(2));
                attron(COLOR_PAIR(3));

                // Render the minus box below the plus box
                for (int k = 0; k < 7; k++) {
                    mvprintw(row * (1 + 2 * i) + k + 1, col + 160, minus[k]);

                }
                attroff(COLOR_PAIR(3));

            }
            else{

                attron(COLOR_PAIR(1));

                for (int j = 0; j < 9; j++) { // Render the main box
                    mvprintw(row * (1 + 2 * i) + j, col, box[j]);

                }

                // Render the plus box on the right side of the non-selected box
                for (int k = 0; k < 7; k++) {
                    mvprintw(row * (1 + 2 * i) + k + 1, col + 140, plus[k]);

                }
                

                // Render the minus box below the plus box
                for (int k = 0; k < 7; k++) {
                    mvprintw(row * (1 + 2 * i) + k + 1, col + 160, minus[k]);

                }
                attroff(COLOR_PAIR(1));

            

            }

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
    

    b[choice[0]][choice[1]]();
    endwin();
}



void cart() {
    clear();
    mvprintw(5, 10, "Cart function called.");
    refresh();
    getch();
}

void wallet() {
    clear();
    mvprintw(5, 10, "Wallet function called.");
    refresh();
    getch();
}

void categories() {
    clear();
    //mvprintw(5, 10, "Categories function called.");
    const char *a[2][2] = {
        {"CART","WALLET"},{"CART","WALLET"}};
    void (*b[2][2])() = {
        {cart,wallet},{cart,wallet}};

    // Clear the screen and show options
    cartselect(2, 2, a, b,5,50);
    refresh();
    getch();
}

void settings() {
    clear();
    mvprintw(5, 10, "Settings function called.");
    refresh();
    getch();
}