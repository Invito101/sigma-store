#include "../headers.h"
#include <stdio.h>
#include <stdbool.h>
#include <ncurses.h> // Ensure this file exists and is in the correct path
#include <wchar.h> // This is temporary as I'm trying to put in unicode characters
#define max_len 100

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
    getnstr(name, max_len);
    noecho();
    attroff(COLOR_PAIR(2));

    move(2 + 1, 10); // makes sure it doesnt clash with any error message
    clrtoeol();


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

    
    char name[max_len],price[max_len];
    char description[max_len], category[max_len], manufacturedBy[max_len];


    init_pair(1, COLOR_GREEN, COLOR_BLACK); 
    init_pair(2, COLOR_YELLOW, COLOR_BLACK); 

    attron(COLOR_PAIR(1));
    mvprintw(2, 10, "Create a new product:");
    mvprintw(3, 10, "Press Enter to submit each field, and type carefully:");
    attroff(COLOR_PAIR(1));
    refresh();

    get_valid_input_for_product(5, "Name of the product: ", name, max_len, is_valid_name);
    get_valid_input_for_product(6, "Price: ", price, max_len, is_valid_price);
    get_valid_input_for_product(7, "Description: ",description, max_len, NULL);

    const char* categ[7]= {"Books","Electronics","Fashion","Sports and Fitness","Games","Edibles","Home and Kitchen"};
    int selected = selectany1(7,categ);
    strncpy(category, categ[selected], max_len);

    attron(COLOR_PAIR(1));
    mvprintw(8,10, "Category: ");
    attroff(COLOR_PAIR(1));

    attron(COLOR_PAIR(2));
    mvprintw(8,20, "%s",category);
    attroff(COLOR_PAIR(2));
    refresh();
    get_valid_input_for_product(9, "Manufactured by: ",manufacturedBy, max_len, is_valid_manufacturedBy);

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
    
    
    char name[max_len];
    char new_name[max_len],new_price[max_len];
    char new_description[max_len], new_category[max_len], new_manufactured_by[max_len];
    init_pair(1, COLOR_GREEN, COLOR_BLACK); 
    init_pair(2, COLOR_YELLOW, COLOR_BLACK); 
    attron(COLOR_PAIR(1));
    mvprintw(1, 10, "Modify The Product :");
    mvprintw(2, 10, "Press Enter To Submit Each Field, And Type Carefully:");
    
    attroff(COLOR_PAIR(1));
    refresh();
    get_valid_input_for_existing_product(4, "Name Of The Product Do You Wanna Modify: ", name, max_len, is_valid_name);
    
    


    get_valid_input_for_product(5, "New Name: ", new_name, max_len, is_valid_name);

    get_valid_input_for_product(6, "New Price: ", new_price, max_len, is_numeric);
    get_valid_input_for_product(7, "New Description: ",new_description, max_len, NULL);

    char* categ[7]= {"Books","Electronics","Fashion","Sports and Fitness","Games","Edibles","Home and Kitchen"};
    int selected = selectany1(7,categ);
    strncpy(new_category, categ[selected], max_len);

    attron(COLOR_PAIR(1));
    mvprintw(8,10, "Category: ");
    attroff(COLOR_PAIR(1));

    attron(COLOR_PAIR(2));
    mvprintw(8,20, "%s",new_category);
    attroff(COLOR_PAIR(2));
    refresh();
    get_valid_input_for_product(9, "Manufactured by: ",new_manufactured_by, max_len, is_valid_manufacturedBy);

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

