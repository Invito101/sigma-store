#include <sqlite3.h>

#ifndef HEADERS_H   // Prevents multiple inclusion
#define HEADERS_H

void clrscr(void);

char* encrypt(char *text);

sqlite3* open_db(void);
int create_tables(void);
int create_customer(char *name, char *email, char *password, char *phoneNumber, char *address, int pincode, char *state);

#endif
