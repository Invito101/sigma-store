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

typedef struct {
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

typedef struct {
    Product *products;
    int currentIndex;
} ProductArrayWrapper;

//Order structs

typedef OrderItem{ //productid, quantity, users email
    int id; //product id.
    int quantity; //quantity of item.
    OrderItem* nextitem;
}OrderItem;

typedef struct Order{
    char useremail[301];
    OrderItem* nextitem;
}Order;