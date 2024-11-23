#include "../headers.h"
#include <time.h>
#include <ctype.h>

int max_length = 100;
int is_numeric(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isdigit((unsigned char)str[i]))
            return 0;
    }
    return 1;
}
int is_valid_name(char *name)
{
    if (strlen(name)==0) return 0;
    else 
    {   
        
        return 1;
    }
}

int is_valid_price(char *price)
{
    for (int i=0;i<max_length;i++)
    {
        if (isdigit((unsigned char)price[i]));

    }
}
