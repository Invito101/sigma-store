//This file contains product functions.
#include "../headers.h"
#include <stdio.h>
#include <stdbool.h>
#include<string.h>
#include <ncurses.h> // Ensure this file exists and is in the correct path
#include <wchar.h> // This is temporary as I'm trying to put in unicode characters
#define max_len 100
void check_for_back(const char *input) {
        if (strcmp(input, "b") == 0) {
            clear();
            endwin();
            admin_home();
            exit(0); // Ensure the function exits immediately
        }
    }


void create_product1(){   
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
    mvprintw(2,28, "        _____ _____ _____ __  __             _____ _______ ____  _____  ______ ");
    mvprintw(3, 33, "  / ____|_   _/ ____|  \\/  |   /\\      / ____|__   __/ __ \\|  __ \\|  ____|");
    mvprintw(4, 33, " | (___   | || |  __| \\  / |  /  \\    | (___    | | | |  | | |__) | |__   ");
    mvprintw(5, 33, "  \\___ \\  | || | |_ | |\\/| | / /\\ \\    \\___ \\   | | | |  | |  _  /|  __|  ");
    mvprintw(6, 33, "  ____) |_| || |__| | |  | |/ ____ \\   ____) |  | | | |__| | | \\ \\| |____ ");
    mvprintw(7, 33, " |_____/|_____\\_____|_|  |_/_/    \\_\\ |_____/   |_|  \\____/|_|  \\_\\______|");

    refresh();

    
    char name[max_len],price[max_len];
    char description[max_len], category[max_len], manufacturedBy[max_len];


    init_pair(1, COLOR_GREEN, COLOR_BLACK); 
    init_pair(2, COLOR_YELLOW, COLOR_BLACK); 

    attron(COLOR_PAIR(1));
    mvprintw(9, 10, "Create a new product:");
    mvprintw(10, 10, "Press Enter to submit each field, and type carefully:");
    attroff(COLOR_PAIR(1));
    refresh();

    get_valid_input_for_product(12, "Name", name, max_len, is_valid_product_name);
    get_valid_input_for_product(13, "Price", price, max_len, is_valid_price);
    get_valid_input_for_product(14, "Description",description, max_len, NULL);

    const char* categ[7]= {"Books","Electronics","Fashion","Sports and Fitness","Games","Edibles","Home and Kitchen"};
    int selected = selectany1(7,categ);
    strncpy(category, categ[selected], max_len);
    for(int i=0;i<7;i++){
        move(15+i,10);
        clrtoeol();
    }

    attron(COLOR_PAIR(1));
    mvprintw(15,10, "Category: ");
    attroff(COLOR_PAIR(1));

    attron(COLOR_PAIR(2));
    mvprintw(15,20, "%s",category);
    attroff(COLOR_PAIR(2));
    refresh();
    get_valid_input_for_product(16, "Manufactured by",manufacturedBy, max_len, is_valid_manufacturedBy);

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


void modify_product1(){
    clear();
    endwin();
    initscr();
    mvprintw(5, 10, "modify_product function called");
    
    create_tables();
    raw();
    clear();
    start_color();
    cbreak();
    noecho();
    curs_set(0); 
    keypad(stdscr,TRUE);

    mvprintw(1,28, "        _____ _____ _____ __  __             _____ _______ ____  _____  ______ ");
    mvprintw(2, 33, "  / ____|_   _/ ____|  \\/  |   /\\      / ____|__   __/ __ \\|  __ \\|  ____|");
    mvprintw(3, 33, " | (___   | || |  __| \\  / |  /  \\    | (___    | | | |  | | |__) | |__   ");
    mvprintw(4, 33, "  \\___ \\  | || | |_ | |\\/| | / /\\ \\    \\___ \\   | | | |  | |  _  /|  __|  ");
    mvprintw(5, 33, "  ____) |_| || |__| | |  | |/ ____ \\   ____) |  | | | |__| | | \\ \\| |____ ");
    mvprintw(6, 33, " |_____/|_____\\_____|_|  |_/_/    \\_\\ |_____/   |_|  \\____/|_|  \\_\\______|");

    refresh();
    
    
    char name[max_len];
    char new_name[max_len],new_price[max_len];
    char new_description[max_len], new_category[max_len], new_manufactured_by[max_len];
    init_pair(1, COLOR_GREEN, COLOR_BLACK); 
    init_pair(2, COLOR_YELLOW, COLOR_BLACK); 
    attron(COLOR_PAIR(1));
    mvprintw(8, 10, "Modify The Product :");
    mvprintw(9, 10, "Press Enter To Submit Each Field, And Type Carefully: ");
    
    attroff(COLOR_PAIR(1));
    refresh();
    
    // char ch1=getch();
    // check_for_back(&ch1);


    attron(COLOR_PAIR(1));
    mvprintw(25,10,"Press 'b' And Press Enter Key To Go Back To Main Menu.");
    attroff(COLOR_PAIR(1));

    get_valid_input_for_existing_product(11, "Name Of The Product Do You Wanna Modify: ", name, max_len, is_valid_name);
    check_for_back(name);
    

    get_valid_input_for_product(12, "New Name ", new_name, max_len, is_valid_name);
    check_for_back(new_name);

    get_valid_input_for_product(13, "New Price ", new_price, max_len, is_numeric);
    check_for_back(new_price);
    get_valid_input_for_product(14, "New Description ",new_description, max_len, NULL);
    check_for_back(new_description);

    const char* categ[7]= {"Books","Electronics","Fashion","Sports and Fitness","Games","Edibles","Home and Kitchen"};
    int selected = selectany1(7,categ);
    strncpy(new_category, categ[selected], max_len);
    for(int i=0;i<7;i++){
        move(15+i,10);
        clrtoeol();
    }

    attron(COLOR_PAIR(1));
    mvprintw(15,10, "Category: ");
    attroff(COLOR_PAIR(1));

    attron(COLOR_PAIR(2));
    mvprintw(15,20, "%s",new_category);
    attroff(COLOR_PAIR(2));
    refresh();
    get_valid_input_for_product(16, "Manufactured by ",new_manufactured_by, max_len, is_valid_manufacturedBy);
    check_for_back(new_manufactured_by);

    int sf = modify_product(name,new_name,atoi(new_price),new_description,new_category,new_manufactured_by);
    clear();
    if (sf==0){
    attron(COLOR_PAIR(1));
    mvprintw(5, 10, "Product modified successfully! Here's the data you entered:");
    mvprintw(6, 10, "Name:");
    mvprintw(7, 10, "Price:");
    mvprintw(8, 10, "Description:");
    mvprintw(9, 10, "Category:");
    mvprintw(10, 10, "Manufactured by:");
    attroff(COLOR_PAIR(1));
    attron(COLOR_PAIR(2));
    mvprintw(6, 30, "%s", new_name);
    mvprintw(7, 30, "%s", new_price);
    mvprintw(8, 30, "%s", new_description);
    mvprintw(9, 30, "%s", new_category);
    mvprintw(10, 30, "%s",new_manufactured_by);
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


int selectany1(int n,const char *a[]) {
    int choice = 0;
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
        mvprintw(15, 10, "Category: ");
        attroff(COLOR_PAIR(1));
        for(int i=0;i<sizea;i++){
            if(i==tco){
                attron(COLOR_PAIR(2));
                mvprintw(15+i,20,"> %s",a[i]);
                attroff(COLOR_PAIR(2));
                refresh();
            }
            else{
                attron(COLOR_PAIR(1));
                mvprintw(15+i,20,"  %s",a[i]);
                attroff(COLOR_PAIR(1));
                refresh();
            }
        }
        
        // attron(COLOR_PAIR(1));
        // mvprintw(n+4, 3, "Use arrow keys to navigate, Enter to select1.");
        // attroff(COLOR_PAIR(1));
        refresh();

        ch=getch();
        if(ch == '\n'){
            choice =tco;
            break;}
        
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
    }

    endwin();
    return 0;
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

        mvprintw(2,55, "        _____ _____ _____ __  __             _____ _______ ____  _____  ______ ");
        mvprintw(3, 60, "  / ____|_   _/ ____|  \\/  |   /\\      / ____|__   __/ __ \\|  __ \\|  ____|");
        mvprintw(4, 60, " | (___   | || |  __| \\  / |  /  \\    | (___    | | | |  | | |__) | |__   ");
        mvprintw(5, 60, "  \\___ \\  | || | |_ | |\\/| | / /\\ \\    \\___ \\   | | | |  | |  _  /|  __|  ");
        mvprintw(6, 60, "  ____) |_| || |__| | |  | |/ ____ \\   ____) |  | | | |__| | | \\ \\| |____ ");
        mvprintw(7, 60, " |_____/|_____\\_____|_|  |_/_/    \\_\\ |_____/   |_|  \\____/|_|  \\_\\______|");

        refresh();
        // Display categories
        for (int i = 0; i < category_count; i++) {
            if (i == category_choice) {
                attron(COLOR_PAIR(2));
                mvprintw(12 + i, 10, "> %s", categories[i]);
                attroff(COLOR_PAIR(2));
            } else {
                attron(COLOR_PAIR(1));
                mvprintw(12 + i, 12, "%s", categories[i]);
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
                mvprintw(9, 10, "Select a product to delete from category: %s", categories[category_choice]);
                attroff(COLOR_PAIR(2));

                int filtered_indices[count];
                int filtered_count = 0;

                for (int i = 0; i < count; i++) {
                    if (strcmp(products[i].category, categories[category_choice]) == 0) {
                        filtered_indices[filtered_count++] = i;
                    }
                }

                if (filtered_count == 0) {
                    mvprintw(2,55, "        _____ _____ _____ __  __             _____ _______ ____  _____  ______ ");
                    mvprintw(3, 60, "  / ____|_   _/ ____|  \\/  |   /\\      / ____|__   __/ __ \\|  __ \\|  ____|");
                    mvprintw(4, 60, " | (___   | || |  __| \\  / |  /  \\    | (___    | | | |  | | |__) | |__   ");
                    mvprintw(5, 60, "  \\___ \\  | || | |_ | |\\/| | / /\\ \\    \\___ \\   | | | |  | |  _  /|  __|  ");
                    mvprintw(6, 60, "  ____) |_| || |__| | |  | |/ ____ \\   ____) |  | | | |__| | | \\ \\| |____ ");
                    mvprintw(7, 60, " |_____/|_____\\_____|_|  |_/_/    \\_\\ |_____/   |_|  \\____/|_|  \\_\\______|");
                    mvprintw(15, 10, "No products available in this category.");
                    mvprintw(LINES - 2, 3, "Use arrow keys to navigate, Enter to delete, b to go back.");
                    refresh();
                    getch();
                    break;
                }

                int product_choice = 0;

                while (true) {
                    clear();
                    attron(COLOR_PAIR(2));
                    mvprintw(9, 10, "Select a product to delete from category: %s", categories[category_choice]);
                    attroff(COLOR_PAIR(2));

                    mvprintw(2,55, "        _____ _____ _____ __  __             _____ _______ ____  _____  ______ ");
                    mvprintw(3, 60, "  / ____|_   _/ ____|  \\/  |   /\\      / ____|__   __/ __ \\|  __ \\|  ____|");
                    mvprintw(4, 60, " | (___   | || |  __| \\  / |  /  \\    | (___    | | | |  | | |__) | |__   ");
                    mvprintw(5, 60, "  \\___ \\  | || | |_ | |\\/| | / /\\ \\    \\___ \\   | | | |  | |  _  /|  __|  ");
                    mvprintw(6, 60, "  ____) |_| || |__| | |  | |/ ____ \\   ____) |  | | | |__| | | \\ \\| |____ ");
                    mvprintw(7, 60, " |_____/|_____\\_____|_|  |_/_/    \\_\\ |_____/   |_|  \\____/|_|  \\_\\______|");

                    refresh();

                    for (int i = 0; i < filtered_count; i++) {
                        int index = filtered_indices[i];
                        if (i == product_choice) {
                            attron(COLOR_PAIR(2));
                            mvprintw(12 + i, 10, "> %s", products[index].name);
                            attroff(COLOR_PAIR(2));
                        } else {
                            attron(COLOR_PAIR(1));
                            mvprintw(12 + i, 12, "%s", products[index].name);
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
                            if (ch == 'y' || ch == 'Y') {
                                delete_product(products[delete_index].name);
                                move(LINES-4,10);
                                clrtoeol();
                                attron(COLOR_PAIR(2));
                                mvprintw(LINES - 4, 10, "'%s' deleted successfully!", products[delete_index].name);
                                attroff(COLOR_PAIR(2));
                                getch();
                                clear();
                                admin_home();
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


void complete_order1(){
    clear();
    initscr();
    raw();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    start_color();

    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_YELLOW, COLOR_BLACK);

    int count;
    Order *orders = get_all_pending_orders(&count);
    if (count == 0) {
        attron(COLOR_PAIR(2));
        mvprintw(5, 10, "No pending orders :)");
        attroff(COLOR_PAIR(2));
        refresh();
        getch();
        endwin();
        return;
    }

    if (orders == NULL) {
        endwin();
        fprintf(stderr, "Failed to retrieve orders.\n");
        return;
    }

    int choice;
    int ch;

    while (true) {
        clear();
        attron(COLOR_PAIR(2));
        mvprintw(10, 55, "Select the order and press Enter to view order details.");
        attroff(COLOR_PAIR(2));

        mvprintw(2,55, "        _____ _____ _____ __  __             _____ _______ ____  _____  ______ ");
        mvprintw(3, 60, "  / ____|_   _/ ____|  \\/  |   /\\      / ____|__   __/ __ \\|  __ \\|  ____|");
        mvprintw(4, 60, " | (___   | || |  __| \\  / |  /  \\    | (___    | | | |  | | |__) | |__   ");
        mvprintw(5, 60, "  \\___ \\  | || | |_ | |\\/| | / /\\ \\    \\___ \\   | | | |  | |  _  /|  __|  ");
        mvprintw(6, 60, "  ____) |_| || |__| | |  | |/ ____ \\   ____) |  | | | |__| | | \\ \\| |____ ");
        mvprintw(7, 60, " |_____/|_____\\_____|_|  |_/_/    \\_\\ |_____/   |_|  \\____/|_|  \\_\\______|");
        attron(COLOR_PAIR(1));
        mvprintw(9, 55, "Order ID");
        mvprintw(10, 70, "User ID");
        attroff(COLOR_PAIR(1));
        refresh();
        // Display categories
        for (int i = 0; i < count; i++) {
            if (i == choice) {
                attron(COLOR_PAIR(2));
                mvprintw(12 + i, 55, "> %d", orders[i].id);
                mvprintw(12 + i, 70, "%d", orders[i].userId);
                attroff(COLOR_PAIR(2));
            } else {
                attron(COLOR_PAIR(1));
                mvprintw(12 + i, 57, "%d", orders[i].id);
                mvprintw(12 + i, 70, "%d", orders[i].userId);
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
                choice = (choice == 0) ? count - 1 : choice - 1;
                break;
            case KEY_DOWN:
                choice = (choice == count - 1) ? 0 : choice + 1;
                break;
            case '\n': {
                // Display order details
                while (true) {
                    clear();
                    attron(COLOR_PAIR(2));
                    mvprintw(9, 10, "Do you want to approve the order of '%d'? (y/n)", orders[choice].userId);
                    attroff(COLOR_PAIR(2));

                    mvprintw(2,55, "        _____ _____ _____ __  __             _____ _______ ____  _____  ______ ");
                    mvprintw(3, 60, "  / ____|_   _/ ____|  \\/  |   /\\      / ____|__   __/ __ \\|  __ \\|  ____|");
                    mvprintw(4, 60, " | (___   | || |  __| \\  / |  /  \\    | (___    | | | |  | | |__) | |__   ");
                    mvprintw(5, 60, "  \\___ \\  | || | |_ | |\\/| | / /\\ \\    \\___ \\   | | | |  | |  _  /|  __|  ");
                    mvprintw(6, 60, "  ____) |_| || |__| | |  | |/ ____ \\   ____) |  | | | |__| | | \\ \\| |____ ");
                    mvprintw(7, 60, " |_____/|_____\\_____|_|  |_/_/    \\_\\ |_____/   |_|  \\____/|_|  \\_\\______|");

                    refresh();

                    attron(COLOR_PAIR(1));
                    mvprintw(9, 55, "Order ID: '%d'",orders[choice].id);
                    mvprintw(9, 70, "User ID: '%d'",orders[choice].userId);
                    mvprintw(11,55,"Product ID");
                    mvprintw(11,70,"Quantity");
                    attroff(COLOR_PAIR(1));

                    for (int i=0; i<orders[choice].size; i++){
                        attron(COLOR_PAIR(2));
                        mvprintw(13+i,55,"%d. %d",i+1,orders[choice].items->productId);
                        mvprintw(13+i,70,"%d. %d",i+1,orders[choice].items->quantity);
                        attroff(COLOR_PAIR(2));
                    }

                    mvprintw(LINES - 2, 3, "Press b to go back.");
                    refresh();

                    ch = getch();
                    if (ch == 'b') break;

                    if (ch == 'y' || ch == 'Y') {
                        clear();
                        mvprintw(2,55, "        _____ _____ _____ __  __             _____ _______ ____  _____  ______ ");
                        mvprintw(3, 60, "  / ____|_   _/ ____|  \\/  |   /\\      / ____|__   __/ __ \\|  __ \\|  ____|");
                        mvprintw(4, 60, " | (___   | || |  __| \\  / |  /  \\    | (___    | | | |  | | |__) | |__   ");
                        mvprintw(5, 60, "  \\___ \\  | || | |_ | |\\/| | / /\\ \\    \\___ \\   | | | |  | |  _  /|  __|  ");
                        mvprintw(6, 60, "  ____) |_| || |__| | |  | |/ ____ \\   ____) |  | | | |__| | | \\ \\| |____ ");
                        mvprintw(7, 60, " |_____/|_____\\_____|_|  |_/_/    \\_\\ |_____/   |_|  \\____/|_|  \\_\\______|");
                        
                        mvprintw(18,55,"Order approved successfully.");
                        mark_order_as_delivered(orders[choice].id);
                        move(LINES-4,10);
                        clrtoeol();
                        mvprintw(LINES - 2, 9, "Enter b to go back.");
                        getch();
                        clear();
                        admin_home();
                        break;
                    }
                    refresh();
                    break;   
                }
            }
            break;
        }
    }
    // Clean up
    endwin();
    free(orders);    
    return;
}


void order_history1(){
    clear();
    endwin();
    initscr();
    mvprintw(5, 10, "modify_product function called");
    
    create_tables();
    raw();
    clear();
    start_color();
    cbreak();
    noecho();
    curs_set(0); 
    keypad(stdscr,TRUE);

    mvprintw(1,55, "        _____ _____ _____ __  __             _____ _______ ____  _____  ______ ");
    mvprintw(2, 60, "  / ____|_   _/ ____|  \\/  |   /\\      / ____|__   __/ __ \\|  __ \\|  ____|");
    mvprintw(3, 60, " | (___   | || |  __| \\  / |  /  \\    | (___    | | | |  | | |__) | |__   ");
    mvprintw(4, 60, "  \\___ \\  | || | |_ | |\\/| | / /\\ \\    \\___ \\   | | | |  | |  _  /|  __|  ");
    mvprintw(5, 60, "  ____) |_| || |__| | |  | |/ ____ \\   ____) |  | | | |__| | | \\ \\| |____ ");
    mvprintw(6, 60, " |_____/|_____\\_____|_|  |_/_/    \\_\\ |_____/   |_|  \\____/|_|  \\_\\______|");

    refresh();
    init_pair(1, COLOR_GREEN, COLOR_BLACK);  
    init_pair(2, COLOR_YELLOW, COLOR_BLACK);

    attron(COLOR_PAIR(1));
    mvprintw(8,70,"-----------------");
    mvprintw(9,70,"| ORDER HISTORY |");
    mvprintw(10,70,"-----------------");
    attroff(COLOR_PAIR(1));
    int size;
    Order *comp_orders=get_all_completed_orders(&size);
    attron(COLOR_PAIR(1));
    mvprintw(30,10,"Enter 'b' to return to the main menu");
    attroff(COLOR_PAIR(1));
    
    char ch12=getch();
    check_for_back(&ch12);
    mvprintw(11,10,"%d",size);
    
    if (size==0)
    {
        attron(COLOR_PAIR(1));
        mvprintw(12,10,"Your History Is Empty");
        attroff(COLOR_PAIR(1));
    }
    else{
        for (int i=0;i<size;i++)
        {
            attron(COLOR_PAIR(1));
            
            mvprintw(11+i,10,"Quantity: ");

            mvprintw(11+i,20,"%d",comp_orders[i].items->quantity);
            attroff(COLOR_PAIR(1));
        }
    }
    










    
    
}
