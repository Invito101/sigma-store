#include "headers.h"
#include <time.h>

void clrscr(void){
    #if defined(_WIN32) || defined(_WIN64)
        system("cls"); // For Windows
    #else
        system("clear"); // For UNIX-like systems (Linux, macOS)
    #endif
}

time_t parseDateToTimeT(char *dateStr){
    struct tm tmStruct;
    memset(&tmStruct, 0, sizeof(struct tm));

    strftime(dateStr, sizeof(dateStr), "%Y-%m-%d %H:%M:%S", &tmStruct);

    return mktime(&tmStruct);
}

// SQL stuff
int countCallback(void *count, int argc, char **argv, char **azColName){
    *(int *)count = atoi(argv[0]);
    return 0;
}