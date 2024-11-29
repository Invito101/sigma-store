#include <stdio.h>
#include <ncurses.h>
#include "../headers.h"

void showproducts(int count, Product* b, int row, int col,int starter,int chooser) {
    
    clear();

    int (*c[2])(int,int)={AddItemToOrder,DecreaseItemQuantity};
    int choice[2] = {0, 0};
    int tco[2] = {0, 0}; // the_chosen_one
    int stopper;

    if(chooser==0)
    tco[0]=starter;
    else if(chooser==1)
    tco[0]=starter+4;

    int sizer = count;
    int sizec = 2;
    int ch;

    if(count<5){
        stopper=count;
    }
    else
    stopper=starter+5;

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
    init_pair(3, COLOR_CYAN,COLOR_BLACK);


    const char *box[] = {
        "+--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+\n",
        "|                %-40s                               Number of sales: %s                                                                                                                                                         |\n",
        "|                Rs.%s                                                                                                                                                                               |\n",
        "|                                                                                                                                                                                                        |\n",
        "|                %-40s                               Ratings: %s                                                                                                                                                  |\n",
        "|                                                                                                                                                                                                        |\n",
        "|                Manufactured by: %s                                                                                                                                                                                      |\n",
        "|                Release date: %s                                                                                                                                                                                     |\n",
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
    while(true){
        int flag=0;
    while (true) {
        clear();
        attron(COLOR_PAIR(1));
        mvprintw(1,2, "Welcome to %s. Press 'b' to go back to menu.",selected_cat);
        attroff(COLOR_PAIR(1));

        for (int i = starter; i < stopper; i++) {
        
            char buffer[1000];

            if (i == tco[0]&&tco[1]==0) {

                attron(COLOR_PAIR(2));
                for (int j = 0; j < 9; j++) {
                    
                    if(j==1){
                        attron(A_BOLD);
                        snprintf(buffer,sizeof(buffer),"%d",b[i].amountBought);
                        mvprintw(row * (1 + 2 * (i-starter)) + j, col, box[j],b[i].name,buffer);
                        attroff(A_BOLD);


                    }
                    else if(j==2){
                        attron(A_BOLD);
                        snprintf(buffer,sizeof(buffer),"%d",b[i].price);
                        mvprintw(row * (1 + 2 * (i-starter)) + j, col, box[j],buffer);
                        attroff(A_BOLD);

                    }
                    else if(j==4){
                        snprintf(buffer,sizeof(buffer),"%.1lf",b[i].rating);
                        mvprintw(row * (1 + 2 * (i-starter)) + j, col, box[j],b[i].description,buffer);
                    }
                    else if(j==6){
                        mvprintw(row * (1 + 2 * (i-starter)) + j, col, box[j],b[i].manufacturedBy);
                    }
                    else if(j==7){
                        char* ptr =get_date_from_time(b[i].createdAt);
                        mvprintw(row * (1 + 2 * (i-starter)) + j, col, box[j],ptr);
                    }
                    else{
                        mvprintw(row * (1 + 2 * (i-starter)) + j, col, box[j]);

                    }

                }
                attroff(COLOR_PAIR(2));

                
                attron(COLOR_PAIR(3));

                for (int k = 0; k < 7; k++) {
                    mvprintw(row * (1 + 2 * (i-starter)) + k + 1, col + 160, plus[k]);

                }
                
                attroff(COLOR_PAIR(3));

                attron(COLOR_PAIR(2));
                
                for (int k = 0; k < 7; k++) {
                    mvprintw(row * (1 + 2 * (i-starter)) + k + 1, col + 180, minus[k]);

                }
                attroff(COLOR_PAIR(2));

                } 
                else if(tco[0]==i&&tco[1]==1){
                attron(COLOR_PAIR(2));
                for (int j = 0; j < 9; j++) {

                    if(j==1){
                        attron(A_BOLD);
                        snprintf(buffer,sizeof(buffer),"%d",b[i].amountBought);
                        mvprintw(row * (1 + 2 * (i-starter)) + j, col, box[j],b[i].name,buffer);
                        attroff(A_BOLD);


                    }
                    else if(j==2){
                        attron(A_BOLD);
                        snprintf(buffer,sizeof(buffer),"%d",b[i].price);
                        mvprintw(row * (1 + 2 * (i-starter)) + j, col, box[j],buffer);
                        attroff(A_BOLD);

                    }
                    else if(j==4){
                        snprintf(buffer,sizeof(buffer),"%.1lf",b[i].rating);
                        mvprintw(row * (1 + 2 * (i-starter)) + j, col, box[j],b[i].description,buffer);
                    }
                    else if(j==6){
                        mvprintw(row * (1 + 2 * (i-starter)) + j, col, box[j],b[i].manufacturedBy);
                    }
                    else if(j==7){
                        char* ptr =get_date_from_time(b[i].createdAt);
                        mvprintw(row * (1 + 2 * (i-starter)) + j, col, box[j],ptr);
                    }
                    else{
                        mvprintw(row * (1 + 2 * (i-starter)) + j, col, box[j]);

                    }
                }

                for (int k = 0; k < 7; k++) {
                    mvprintw(row * (1 + 2 * (i-starter)) + k + 1, col + 160, plus[k]);

                }
                attroff(COLOR_PAIR(2));
                attron(COLOR_PAIR(3));

                for (int k = 0; k < 7; k++) {
                    mvprintw(row * (1 + 2 * (i-starter)) + k + 1, col + 180, minus[k]);

                }
                attroff(COLOR_PAIR(3));

            }
            else{

                attron(COLOR_PAIR(1));
                
                for (int j = 0; j < 9; j++) {
                    if(j==1){
                        attron(A_BOLD);
                        snprintf(buffer,sizeof(buffer),"%d",b[i].amountBought);
                        mvprintw(row * (1 + 2 * (i-starter)) + j, col, box[j],b[i].name,buffer);
                        attroff(A_BOLD);


                    }
                    else if(j==2){
                        attron(A_BOLD);
                        snprintf(buffer,sizeof(buffer),"%d",b[i].price);
                        mvprintw(row * (1 + 2 * (i-starter)) + j, col, box[j],buffer);
                        attroff(A_BOLD);
                    }
                    else if(j==4){
                        snprintf(buffer,sizeof(buffer),"%.1lf",b[i].rating);
                        mvprintw(row * (1 + 2 * (i-starter)) + j, col, box[j],b[i].description,buffer);
                    }
                    else if(j==6){
                        mvprintw(row * (1 + 2 * (i-starter)) + j, col, box[j],b[i].manufacturedBy);
                    }
                    else if(j==7){
                        char* ptr =get_date_from_time(b[i].createdAt);
                        mvprintw(row * (1 + 2 * (i-starter)) + j, col, box[j],ptr);
                    }
                    else{
                        mvprintw(row * (1 + 2 * (i-starter)) + j, col, box[j]);

                    }
                }

                for (int k = 0; k < 7; k++) {
                    mvprintw(row * (1 + 2 * (i-starter)) + k + 1, col + 160, plus[k]);

                }
                

                for (int k = 0; k < 7; k++) {
                    mvprintw(row * (1 + 2 * (i-starter)) + k + 1, col + 180, minus[k]);

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
printw("Created At: %s\n", ctime(&(b[choice[0]].createdAt)));
printw("\n");
refresh();*/
        }
            refresh();


        ch = getch();

        if (ch == '\n') {
            choice[0] = tco[0];
            choice[1] = tco[1];
            break;
        } else if (ch == KEY_DOWN) {
            if (tco[0] == starter + 4){
                if(tco[0]==sizer-1){
                    showproducts(count,b,row,col,0,0);
                    return;
                }
                else{
                    
                    showproducts(count,b,row,col,starter+1,1);
                    return;
                }

            }
            else{
                if(tco[0]==sizer-1){
                    tco[0]=0;
                }
                else
                tco[0] += 1;
            }

        } else if (ch == KEY_UP) {
            if (tco[0] == starter){
                if(tco[0]==0){
                    
                    showproducts(count,b,row,col,sizer-5,1);
                    return;
                }
                else{
                    
                    showproducts(count,b,row,col,starter-1,0);
                    return;
                }

            }
            else{
                if(tco[0]==0){
                    tco[0]=sizer-1;
                }
                else
                tco[0] -= 1;
            }

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
        } else if(ch== 'b'){
            flag=1;
            break;
            }
        else
        continue;
    }
    

    //Product* selected_product = b[choice[0]];

    if(flag==1){
        break;
    }

    c[choice[1]](b[choice[0]].id, userdetails->id);

    
    }
    menu1();

    endwin();
}

