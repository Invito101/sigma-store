#include <stdio.h>
#include <stdbool.h>
#include <ncurses.h>
#include "headers.h"  // Ensure this file exists and is in the correct path
#include <wchar.h> // This is temporary as I'm trying to put in unicode characters
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

User* userdetails;

// Function declarations
void authpage(void);
void selector(int n,const char *a[],void (*b[])());  //Function allows user to input options    
//here n is the number of options, a is the array of label names, and b is the function pointer array  // Function to allow user to choose signup or login
void signup(void);
void login1(void);
void quit(void);


int main(void) {
    
    create_tables();
    // // Books
    //create_product("The Great Gatsby", 299, "A classic novel by F. Scott Fitzgerald", "Books", "Penguin Classics");
    //create_product("Introduction to Algorithms", 1500, "Comprehensive guide on algorithms", "Books", "MIT Press");
    //create_product("Harry Potter and the Philosopher's Stone", 499, "Fantasy novel by J.K. Rowling", "Books", "Bloomsbury");
    //create_product("Sapiens: A Brief History of Humankind", 799, "By Yuval Noah Harari", "Books", "Harper Perennial");
    //create_product("Atomic Habits", 599, "Practical guide to building good habits", "Books", "Penguin Random House");
    create_product("yoo hoo", 69, "skibidi", "Books", "among us");
    create_product("yoo loo", 69, "skibidi", "Books", "among us");
    create_product("yoo boo", 69, "skibidi", "Books", "among us");
    create_product("yoo zoo", 69, "skibidi", "Books", "among us");


    // // Electronics
    //create_product("Wireless Headphones", 1999, "Bluetooth over-ear headphones", "Electronics", "Sony");
    //create_product("Smartphone", 24999, "Android device with 128GB storage", "Electronics", "Samsung");
    // create_product("Laptop", 54999, "15-inch laptop with 8GB RAM", "Electronics", "Dell");
    // create_product("Smartwatch", 9999, "Fitness tracker with heart rate monitoring", "Electronics", "Apple");
     create_product("Bluetooth Speaker", 3499, "Portable speaker with deep bass", "Electronics", "JBL");

    // // Fashion
    // create_product("Leather Jacket", 3999, "Men's black leather jacket", "Fashion", "Zara");
    // create_product("Sneakers", 2499, "Comfortable running shoes", "Fashion", "Nike");
    // create_product("Wrist Watch", 1499, "Stylish analog watch", "Fashion", "Casio");
    // create_product("Sunglasses", 999, "UV-protective polarized lenses", "Fashion", "Ray-Ban");
    // create_product("Denim Jeans", 1999, "Blue slim-fit jeans", "Fashion", "Levi's");

    // // Sports and Fitness
    // create_product("Yoga Mat", 899, "Non-slip, lightweight yoga mat", "Sports and Fitness", "Reebok");
    // create_product("Treadmill", 24999, "Electric treadmill for cardio workouts", "Sports and Fitness", "PowerMax");
    // create_product("Dumbbell Set", 2999, "Adjustable weight dumbbell set", "Sports and Fitness", "Bowflex");
    // create_product("Football", 999, "FIFA approved match ball", "Sports and Fitness", "Adidas");
    // create_product("Resistance Bands", 499, "Set of 5 resistance bands", "Sports and Fitness", "Fit Simplify");

    // // Games
    // create_product("Chess Set", 999, "Wooden chess board with pieces", "Games", "Handcrafted Creations");
    // create_product("Playing Cards", 199, "Standard deck of 52 cards", "Games", "Bicycle");
    // create_product("Board Game - Monopoly", 1499, "Classic property trading game", "Games", "Hasbro");
    // create_product("Jigsaw Puzzle", 499, "1000-piece nature scenery puzzle", "Games", "Ravensburger");
    // create_product("Video Game - Elden Ring", 3999, "Action role-playing game", "Games", "Bandai Namco");

    // // Edibles
    // create_product("Dark Chocolate", 299, "Rich and creamy chocolate", "Edibles", "Lindt");
    // create_product("Organic Honey", 499, "Pure and natural honey", "Edibles", "Dabur");
    // create_product("Green Tea", 199, "20 sachets of premium green tea", "Edibles", "Lipton");
    // create_product("Trail Mix", 299, "Healthy nuts and dried fruits", "Edibles", "Happilo");
    // create_product("Instant Coffee", 349, "Premium freeze-dried coffee", "Edibles", "Nescafé");

    // // Home and Kitchen
    // create_product("Vacuum Cleaner", 6999, "Bagless upright vacuum cleaner", "Home and Kitchen", "Dyson");
    // create_product("Microwave Oven", 8499, "30L convection microwave", "Home and Kitchen", "LG");
    // create_product("Non-Stick Cookware Set", 2999, "5-piece cookware set", "Home and Kitchen", "Prestige");
    // create_product("Air Purifier", 12999, "HEPA filter air purifier", "Home and Kitchen", "Philips");
    // create_product("Electric Kettle", 1299, "1.5L stainless steel kettle", "Home and Kitchen", "Borosil");
    // Open a file to store stderr

    int file = open("stderr_output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (file == -1) {
        perror("Error opening file");
        return 1;
    }

    // Redirect stderr to the file
    if (dup2(file, STDERR_FILENO) == -1) {
        perror("Error redirecting stderr");
        close(file);
        return 1;
    }

    // Now any output to stderr will go to the file
    fprintf(stderr, "This error message will go to stderr_output.txt\n");

    // Initialize ncurses
    initscr();
    
    // Clear the screen and show options
    clear();

    authpage();

    // Cleanup ncurses
    endwin();
    return 0;
}

void authpage(void){
    const char *a[3]={"Sign up","Login","Quit"};
    void (*b[])()={signup,login1,quit};
    selector(3,a,b);
}

void selector(int n,const char *a[],void (*b[])()) {
  
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
        mvprintw(5, 10, "Welcome! Please live:");
        attroff(COLOR_PAIR(1));
        for(int i=0;i<sizea;i++){
            if(i==tco){
                attron(COLOR_PAIR(2));
                mvprintw(7+i,12,"> %s",a[i]);
                attroff(COLOR_PAIR(2));
                refresh();
            }
            else{
                attron(COLOR_PAIR(1));
                mvprintw(7+i,12,"  %s",a[i]);
                attroff(COLOR_PAIR(1));
                refresh();
            }
        }
        
        attron(COLOR_PAIR(1));
        mvprintw(10, 10, "Use arrow keys to navigate, Enter to select.");
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


void signup() {
    clear();
    int max_length = 100;
    char name[max_length], email[max_length];
    char password[max_length], phoneNumber[max_length], address[max_length];
    char pincode[max_length], state[max_length];

    start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLACK); 
    init_pair(2, COLOR_YELLOW, COLOR_BLACK); 

    attron(COLOR_PAIR(1));
    mvprintw(2, 10, "Signup Form");
    mvprintw(3, 10, "Press Enter to submit each field, and type carefully:");
    attroff(COLOR_PAIR(1));
    refresh();

    get_valid_input(5, "Name", name, max_length, is_valid_name);
    get_valid_input(6, "Email", email, max_length, is_valid_email);
    attron(COLOR_PAIR(1));
    mvprintw(7, 10, "Password: ");
    attroff(COLOR_PAIR(1));
    refresh();
    attron(COLOR_PAIR(2));
    noecho();
    int ch, index = 0;
    while ((ch = getch()) != '\n') {
        if (ch == KEY_BACKSPACE || ch == 127) {
            if (index > 0) {
                index--;
                mvaddch(7, 20 + index, ' '); 
                move(7, 20 + index);
            }
        } else if (index < max_length - 1) {
            password[index++] = ch;
            mvaddch(7, 20 + index - 1, '*'); 
        }
    }
    password[index] = '\0';
    attroff(COLOR_PAIR(2));
    echo();

    get_valid_input(8, "Phone Number", phoneNumber, max_length, is_valid_phone);
    get_valid_input(9, "Address", address, max_length, NULL);
    get_valid_input(10, "Pincode", pincode, max_length, is_valid_pincode);
    get_valid_input(11, "State", state, max_length, NULL);
    clear();

    char *admin_domain = "@sigmastore.in";
    if (strlen(email) >= strlen(admin_domain) && strcmp(email + strlen(email) - strlen(admin_domain), admin_domain) == 0) {
        create_admin(name, email, password, phoneNumber, address, atoi(pincode), state);
    } else {
        create_customer(name, email, password, phoneNumber, address, atoi(pincode), state);
    }
    attron(COLOR_PAIR(1));
    mvprintw(5, 10, "Signup Successful! Here's the data you entered:");
    mvprintw(6, 10, "Name:");
    mvprintw(7, 10, "Email:");
    mvprintw(8, 10, "Password:");
    mvprintw(9, 10, "Phone Number:");
    mvprintw(10, 10, "Address:");
    mvprintw(11, 10, "Pincode:");
    mvprintw(12, 10, "State:");
    attroff(COLOR_PAIR(1));
    attron(COLOR_PAIR(2));
    mvprintw(6, 30, "%s", name);
    mvprintw(7, 30, "%s", email);
    mvprintw(8, 30, "%s (hidden during entry)", password);
    mvprintw(9, 30, "%s", phoneNumber);
    mvprintw(10, 30, "%s", address);
    mvprintw(11, 30, "%s", pincode);
    mvprintw(12, 30, "%s", state);
    attroff(COLOR_PAIR(2));
    refresh();

    attron(COLOR_PAIR(1));
    mvprintw(15, 10, "Press any key to return to the menu.");
    attroff(COLOR_PAIR(1));
    getch();
    main();
}

void login1(){
    clear();
    int flag=1;
    //mvprintw(5, 10, "Login function called");
    #define max_length_const 100
    int max_length = max_length_const;

    char password[max_length_const], email[max_length_const];

    start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLACK); 
    init_pair(2, COLOR_YELLOW, COLOR_BLACK); 
    init_pair(3,COLOR_RED,COLOR_BLACK);

    attron(COLOR_PAIR(1));
    mvprintw(2, 10, "Login");
    mvprintw(3, 10, "Press Enter to submit each field:");
    attroff(COLOR_PAIR(1));

    refresh();
    get_valid_login(5, "Email", email, max_length, is_valid_email_for_login,authpage);
    attron(COLOR_PAIR(1));
    refresh();
    
    mvprintw(7, 10, "Password: ");
    refresh();
    attron(COLOR_PAIR(2));
    noecho();
    int ch, index = 0;

    while (1) {
        int ch, index = 0;

        
        attron(COLOR_PAIR(1));
        mvprintw(7, 10, "Password: ");
        attroff(COLOR_PAIR(1));
        refresh();

        
        attron(COLOR_PAIR(2));
        for (int i = 0; i < max_length; i++) {
            mvaddch(7, 20 + i, ' ');
        }
        move(7, 20);
        refresh();
        attroff(COLOR_PAIR(2));

        // Input password
        noecho();
        attron(COLOR_PAIR(2));
        index = 0; 
        while ((ch = getch()) != '\n') {
            if (ch == KEY_BACKSPACE || ch == 127) {
                if (index > 0) {
                    index--;
                    mvaddch(7, 20 + index, ' '); 
                    move(7, 20 + index);
                }
            } else if (index < max_length - 1) {
                password[index++] = ch;
                mvaddch(7, 20 + index - 1, '*'); 
            }
        }
        password[index] = '\0'; // adding null terminator
        attroff(COLOR_PAIR(2));
        echo();

        userdetails = login(email, password);
        if (userdetails == NULL) {
            // Wrong password
            attron(COLOR_PAIR(3));
            mvprintw(8, 10, "Wrong password, please try again.");
            attroff(COLOR_PAIR(3));
            refresh();
        } else {
            // Correct password
            move(8,10);
            clrtoeol();
            refresh();
            mvprintw(8, 10, "Login successful! Press any key to continue.");
            refresh();
            getch();
            break;
        }
    }
    attroff(COLOR_PAIR(2));
    echo();

    clear();
    if(strcmp(userdetails->role,"Admin")==0){
        admin_home();
    }
    else if(strcmp(userdetails->role,"Customer")==0){
        menu1();
    }
    flag=0;
    free(userdetails); // Clean up simulated user
}


void quit(){

    clear();
    admin_home();
}