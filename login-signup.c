#include <stdio.h>
#include <stdbool.h>
#include <ncurses.h>
#include "headers.h"  // Ensure this file exists and is in the correct path

// Function declarations
void choices(void);  // Function to allow user to choose signup or login
void signup(void);
void create_tables(void);  // Assuming this is defined elsewhere

int main(void) {
    // Initialize ncurses
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);  // Enable arrow keys and other extended keys

    // Clear the screen and show options
    clear();
    choices();

    // Cleanup ncurses
    endwin();
    return 0;
}

void choices(void) {
    int choice = 0;

    do {
        clear();  // Clear the screen
        mvprintw(5, 10, "Welcome! Please choose an option:");
        mvprintw(7, 12, "1. Signup");
        mvprintw(8, 12, "2. Login");
        mvprintw(10, 10, "Enter your choice (1 or 2):");
        refresh();

        choice = getch();  // Get user input

        switch (choice) {
            case '1':
                signup();
                break;
            case '2':
                clear();
                mvprintw(5, 10, "Welcome to login");
                refresh();
                getch();  // Wait for user input to continue
                break;
            default:
                mvprintw(12, 10, "Invalid Input! Try again!");
                refresh();
                getch();  // Wait for user input to continue
                break;
        }
    } while (choice != '1' && choice != '2');
}

void signup(void) {
    clear();
    mvprintw(5, 10, "Signup functionality is not yet implemented.");
    refresh();
    getch();  // Wait for user input to continue
}
