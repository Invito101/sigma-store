#include <time.h>

typedef struct User{
    int id;
    char name[301];
    char email[301];
    char role[10];
    char password[111];
    char phoneNumber[11];
    char address[1001];
    int pincode;
    char state[101];
    int money;
    time_t createdAt;
} User;

typedef struct{
    User *users;
    int currentIndex;
} UserArrayWrapper;

typedef struct Product{
    int id;
    char name[301];
    int price;
    char description[1001];
    char category[301];
    char manufacturedBy[301];
    double rating;
    int noOfRatings;
    int amountBought;
    time_t createdAt;
} Product;

typedef struct{
    Product *products;
    int currentIndex;
} ProductArrayWrapper;

//Order structs
typedef struct OrderItem{ //productid, quantity, users email
    int id; //product id.
    int quantity; //quantity of item.
    struct OrderItem* nextitem;
} OrderItem;

typedef struct OrderLL{
    int userId;
    OrderItem* nextitem;
} OrderLL;

typedef struct Cart{
    int id;
    int quantity;
    int productId;
    int userId;
    int orderId;
} Cart;

typedef struct CartArrayWrapper{
    Cart *items;
    int currentIndex;
} CartArrayWrapper;

typedef struct Order{
    int id;
    int userId;
    time_t createdAt;

    Cart *items;
    int size;
} Order;