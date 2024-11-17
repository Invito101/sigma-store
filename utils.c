#include "headers.h"
#include <time.h>

void clrscr(void){
    #if defined(_WIN32) || defined(_WIN64)
        system("cls"); // For Windows
    #else
        system("clear"); // For UNIX-like systems (Linux, macOS)
    #endif
}

int getISTTime(){
    time_t rawtime;
    struct tm * timeinfo;

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    timeinfo->tm_hour += 5;
    timeinfo->tm_min += 30;

    mktime(timeinfo);

    return mktime(timeinfo);
}

// SQL stuff
int countCallback(void *count, int argc, char **argv, char **azColName){
    *(int *)count = atoi(argv[0]);
    return 0;
}