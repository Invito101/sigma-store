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