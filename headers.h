#include <sqlite3.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "structs/structs.c"
#include <string.h>
#include <ncurses.h>

#ifndef HEADERS_H   // Prevents multiple inclusion
#define HEADERS_H

// utils.c
void clrscr(void);
time_t parseDateToTimeT(char *dateStr);
int countCallback(void *count, int argc, char **argv, char **azColName);
int getISTTime();
void get_valid_login(int row, char *label, char *buffer, int max_length, int (*validate)(char *),void page());
int is_valid_email_for_login(char *email);


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
int get_id_of_user_by_email(char *email);
User* login(char *email, char *password);

// db/products/products.c
int create_product(char *name, int price, char *description, char *category, char *manufacturedBy);
int delete_product(char *name);
int modify_product(char *name, char *new_name, int new_price, char *new_description, char *new_category, char *new_manufacturedBy);
int rate_product(char *name, int rating);
Product* get_all_products(int *size);
Product* get_all_category_products(int *size, char *cName);

// db/products/products-utils.c
int is_product_name_taken(char *name);
int get_product_no_of_rating(char *name);
double get_product_rating(char *name);
int increase_amount_bought_by_one(char *name);
int increase_no_of_ratings_by_one(char *name);
void cast_row_to_product_struct(Product *productObject, char **values);
int count_all_products();
int count_all_category_products(char *cName);

// db/cart/cart.c
int add_item_to_cart(int userId, int quantity, int productId);
Cart* get_cart_items(int userId, int* size);
int mark_cart_as_ordered(int userId, int orderId);

// db/orders/orders.c
int place_order(int userId);
Order get_order(int orderId, int userId);
Order* get_all_orders_of_user(int userId, int *size);

// db/orders/order-utils.c
void cast_row_to_order_struct(Order *orderObject, char **values);

// db/cart/cart-utils.c
int count_cart_items_of_user(int userId);
void cast_row_to_cart_struct(Cart *cartObject, char **values);

// admin/home.c
int new();
int view_all();
void quit2();

//signup helper functions
int is_numeric(char *str);
int is_valid_email(char *email);
int is_valid_name(char *name);
int is_valid_phone(char *phone);
int is_valid_pincode(char *pincode);
void get_valid_input(int row, char *label, char *buffer, int max_length, int (*validate)(char *));

// admin/View_all_products.c
int view_category_wise();
void create_product1();
void modify_product1();
void delete_product1();
void quit3();
int selectany1(int n,const char *a[]);


// admin/utilities.c
int has_alphabet(char *str);
int is_valid__product_name(char *name);
int is_valid_price(char *price);
int is_valid_description(char* description);
int is_valid_manufactured_by(char* manufactured_by);
void get_valid_input_for_product(int row, char *label, char *buffer, int max_length, int (*validate)(char *));

#endif
