#include <sqlite3.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "structs/structs.c"
#include <string.h>
#include <ncurses.h>
#include <unistd.h>
#include <fcntl.h>

#ifndef HEADERS_H   // Prevents multiple inclusion
#define HEADERS_H

// utils.c
void clrscr(void);
time_t parseDateToTimeT(char *dateStr);
int countCallback(void *count, int argc, char **argv, char **azColName);
int getISTTime();
void get_valid_login(int row, char *label, char *buffer, int max_length, int (*validate)(char *),void page());
int is_valid_email_for_login(char *email);
char* get_date_from_time(time_t timestamp);
//login-signup.c
extern User* userdetails;
void authpage(void);

// encryption.c
char* encrypter(char *text);
char* decrypt(char *text);

// db/db-utils.c
sqlite3* open_db(void);
void close_db(sqlite3 *db);
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
Product* get_product_by_name(char *name);
Product* get_product_by_id(int productId);
Product* get_product_by_name(char* name);
Product* get_all_products(int *size);
Product* get_all_category_products(int *size, char *cName);
Product* get_all_category_products_top_sold(int *size, char *cName);
Product* get_all_category_products_top_rated(int *size, char *cName);
Product* get_all_category_products_price_desc(int *size, char *cName);
Product* get_all_category_products_price_asc(int *size, char *cName);

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
int modify_item_in_cart(int userId, int quantity, int productId);
int delete_cart_item(int userId, int productId);
Cart* get_cart_items(int userId, int* size);
Cart* get_order_items(int orderId, int* size);
int mark_cart_as_ordered(int userId, int orderId);

// db/cart/cart-utils.c
int count_cart_items_of_user(int userId);
int count_cart_order_of_user(int orderId);
void cast_row_to_cart_struct(Cart *cartObject, char **values);

// db/orders/orders.c
int place_order(int userId);
Order get_order(int orderId, int userId);
Order* get_all_orders_of_user(int userId, int *size);
Order* get_all_completed_orders(int *size);
Order* get_all_pending_orders(int *size);
int mark_order_as_delivered(int orderId);

// db/orders/order-utils.c
void cast_row_to_order_struct(Order *orderObject, char **values);

// customer/customer-home.c
void menu1(void);
void buttonselect2d(int m,int n,const char *a[m][n],void (*b[m][n])(),int row, int column);
extern char *selected_cat;

//customer-filters.c
extern int *numberofprods;
void filter1(void);

//customer-products.c
void filtertest(Product* prods,int* count);
void showproducts(int count,Product* b, int row, int col);

// admin/home.c
int admin_home();
int view_all();
void quit2();
void selectany1func(int n,const char *a[],void (*b[])());
void bestseller();



//signup helper functions
int is_numeric(char *str);
int is_valid_email(char *email);
int is_valid_name(char *name);
int is_valid_phone(char *phone);
int is_valid_pincode(char *pincode);
void get_valid_input(int row, char *label, char *buffer, int max_length, int (*validate)(char *));

// admin/View_products.c
int view_category_wise();
void quit3();
void view_particular();
void view_all_products();
void view_bestsellers();
void view_highest_rated();


//admin/pro_fun.c
void create_product1();
void modify_product1();
void delete_product1();
int selectany1(int n,const char *a[]);
void complete_order1();
void order_history1();
void check_for_back(const char *input);




// admin/utilities.c
int has_alphabet(char *str);
int is_valid_product_name(char *name);
int is_valid_price(char *price);
int is_valid_description(char* description);
int is_valid_manufacturedBy(char* manufacturedBy);
void get_valid_input_for_product(int row, char *label, char *buffer, int max_length, int (*validate)(char *));
void get_valid_input_for_existing_product(int row, char *label, char *buffer, int max_length, int (*validate)(char *));

// customer/orders.c
void CreateNewOrder(int userId);
int AddItemToOrder(int id, int userId);
int DecreaseItemQuantity(int id, int userId);
void PlaceOrder(int userId);
void DisplayCart(int userId);

#endif
