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
time_t parseDateToTimeT(char *dateStr);
int countCallback(void *count, int argc, char **argv, char **azColName);

// encryption.c
char* encrypt(char *text);
char* decrypt(char *text);

// db/db-utils.c
sqlite3* open_db(void);
int create_tables(void);

// db/users/users-utils.c
void cast_row_to_user_struct(User *userObject, char **values);
int is_email_taken(char *email);
int count_all_users();

// db/users/users.c
int create_customer(char *name, char *email, char *password, char *phoneNumber, char *address, int pincode, char *state);
int create_admin(char *name, char *email, char *password, char *phoneNumber, char *address, int pincode, char *state);
User* get_all_users(int *size);
int get_money_of_user(char *email);
int modify_money_of_user(char *email, int new_money);

// db/products/products.c
int create_product(char *name, int price, char *description, char *category, char *manufacturedBy);
int delete_product(char *name);
int modify_product(char *name, char *new_name, int new_price, char *new_description, char *new_category, char *new_manufacturedBy);
int rate_product(char *name, int rating);
Product* get_all_products(int *size);

// db/products/products-utils.c
int is_product_name_taken(char *name);
int get_product_no_of_rating(char *name);
double get_product_rating(char *name);
int increase_amount_bought_by_one(char *name);
int increase_no_of_ratings_by_one(char *name);
void cast_row_to_product_struct(Product *productObject, char **values);
int count_all_products();

#endif
