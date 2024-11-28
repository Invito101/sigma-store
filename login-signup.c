#include "headers.h"

void authpage(void){
    initscr();
        start_color();

    clear();

    mvprintw(5, 62, "        _____ _____ _____ __  __             _____ _______ ____  _____  ______ ");
mvprintw(6, 67, "  / ____|_   _/ ____|  \\/  |   /\\      / ____|__   __/ __ \\|  __ \\|  ____|");
mvprintw(7, 67, " | (___   | || |  __| \\  / |  /  \\    | (___    | | | |  | | |__) | |__   ");
mvprintw(8, 67, "  \\___ \\  | || | |_ | |\\/| | / /\\ \\    \\___ \\   | | | |  | |  _  /|  __|  ");
mvprintw(9, 67, "  ____) |_| || |__| | |  | |/ ____ \\   ____) |  | | | |__| | | \\ \\| |____ ");
mvprintw(10, 67, " |_____/|_____\\_____|_|  |_/_/    \\_\\ |_____/   |_|  \\____/|_|  \\_\\______|");

refresh();

    const char *a[3][2] = {
        {"SIGNUP", ""},
        {"LOGIN",""},
        {"QUIT", ""}
    };
    void (*b[3][2])() = {
        {signup, signup},
        {login1, login1},
        {quit, quit}
    };

    // Clear the screen and show options
    buttonselect2d(3, 2, a, b,-10,92);
    // Cleanup ncurses

refresh();
endwin();

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
    mvprintw(2, 10, "Signup Form (Press Escape To Exit)");
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
    if (password[0]==27 && password[1]=='\0'){//escape case
    main();
    }
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
    mvprintw(2, 10, "Login (Press Escape To Exit)");
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
        if(password[0]==27 && password[1]=='\0'){// escape case
            main();
        }
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
}

void quit(){
    initscr();
    clear();
    endwin();
    exit(0);
}