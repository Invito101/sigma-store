#include "headers.h"

void clrscr(void){
    #if defined(_WIN32) || defined(_WIN64)
        system("cls"); // For Windows
    #else
        system("clear"); // For UNIX-like systems (Linux, macOS)
    #endif
}

time_t parseDateToTimeT(const char *dateStr){
    struct tm tmStruct;
    memset(&tmStruct, 0, sizeof(struct tm));  // Initialize struct to zero

    // Parse the string into struct tm
    if (strptime(dateStr, "%Y-%m-%d %H:%M:%S", &tmStruct) == NULL) {
        fprintf(stderr, "Error parsing date string\n");
        return (time_t)(-1);
    }

    // Convert struct tm to time_t
    return mktime(&tmStruct);
}