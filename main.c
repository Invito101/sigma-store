#include "headers.h"

User* userdetails;

int main(){

    
    // for (int hh=0;hh<20;hh++)
    // {
    //     add_item_to_cart(1,10,10);
    // }
    // place_order(1);
    // mark_order_as_delivered(2);

    int file = open("stderr_output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (file == -1) {
        perror("Error opening file");
        return 1;
    }

    if (dup2(file, STDERR_FILENO) == -1) {
        perror("Error redirecting stderr");
        close(file);
        return 1;
    }

    fprintf(stderr, "Errors:\n");

    create_tables();
    init_db();

    initscr();
    clear();

    authpage();

    endwin();
    return 0;
}