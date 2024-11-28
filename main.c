#include "headers.h"

User* userdetails;

int main(){
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

    // create_tables();

    initscr();
    clear();

    authpage();

    endwin();
    return 0;
}