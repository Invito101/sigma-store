#include <sqlite3.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "structs/structs.c"
#include <string.h>

#ifndef HEADERS_H   // Prevents multiple inclusion
#define HEADERS_H

// utils.c
void clrscr(void);
time_t parseDateToTimeT(const char *dateStr);
int countCallback(void *count, int argc, char **argv, char **azColName);

// encryption.c
char* encrypt(char *text);
char* decrypt(char *text);

// db/db-utils.c
sqlite3* open_db(void);
int create_tables(void);

// db/users/users-utils.c
void cast_row_to_struct(User *userObject, char **values);

// db/users/users.c
int create_customer(char *name, char *email, char *password, char *phoneNumber, char *address, int pincode, char *state);
int create_seller(char *name, char *email, char *password, char *phoneNumber, char *address, int pincode, char *state);
int create_admin(char *name, char *email, char *password, char *phoneNumber, char *address, int pincode, char *state);
User* get_all_users(int *size);



#endif
