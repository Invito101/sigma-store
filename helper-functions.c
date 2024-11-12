#include <stdlib.h>
#include "headers.h"

void clrscr(void){
    #if defined(_WIN32) || defined(_WIN64)
        system("cls"); // For Windows
    #else
        system("clear"); // For UNIX-like systems (Linux, macOS)
    #endif
}