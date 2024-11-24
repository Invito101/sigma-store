#include "../headers.h"
#include <stdio.h>
#include <stdbool.h>
#include <ncurses.h> // Ensure this file exists and is in the correct path
#include <wchar.h> // This is temporary as I'm trying to put in unicode characters

int view_category_wise()
{

    return 0;
}

void create_product1()
{   
    clear();
    endwin();
    // delwin(pad);
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
    char description[max_len], category[max_len], manufactured_by[max_len];

    init_pair(1, COLOR_GREEN, COLOR_BLACK); 
    init_pair(2, COLOR_YELLOW, COLOR_BLACK); 

    attron(COLOR_PAIR(1));
    mvprintw(2, 10, "Create a new product:");
    mvprintw(3, 10, "Press Enter to submit each field, and type carefully:");
    attroff(COLOR_PAIR(1));
    refresh();

    get_valid_input_for_product(5, "Name of the product: ", name, max_len, is_valid_name);
    get_valid_input_for_product(6, "Price: ", price, max_len, is_valid_email);
    get_valid_input_for_product(7, "Description: ",description, max_len, NULL);

    char* categ[7]= {"Books","Electronics","Fashion","Sports and Fitness","Games","Edibles","Home and Kitchen"};
    int selected = selectany1(7,categ);
    // category = categ[selected];
    strcpy(category, categ[selected]);
    attron(COLOR_PAIR(1));
    mvprintw(8,10, "Category: ");
    attroff(COLOR_PAIR(1));

    attron(COLOR_PAIR(2));
    mvprintw(8,20, "%s",category);
    attroff(COLOR_PAIR(2));
    refresh();
    get_valid_input_for_product(9, "Manufactured by: ",manufactured_by, max_len, is_valid_manufactured_by);

    create_product(name,atoi(price),description,category, manufactured_by);

    clear();

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
    mvprintw(10, 30, "%s", manufactured_by);
    attroff(COLOR_PAIR(2));
    refresh();

    attron(COLOR_PAIR(1));
    mvprintw(15, 10, "Press any key to return to the menu.");
    attroff(COLOR_PAIR(1));
    getch();
    endwin();
    new();
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

