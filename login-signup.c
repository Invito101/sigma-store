#include <stdio.h>
#include <stdbool.h>
#include "headers.h"

void choices(void); // function to allow user to choose signup or login
void signup(void);

int main(void){
    clrscr();
    // printf("Welcome To Sigma Store\n");
    // printf("Enter 1 to signup\n");
    // printf("Enter 2 to login\n");
    // choices();

    create_tables();
    get_all_users();
}

void choices(void){
    int choice; // Chooses signup or login
    do{
        scanf("%d",&choice);
        if (choice==1)
        {
            signup();
        }
        else if (choice==2)
        {
            clrscr();
            printf("Welcome to login");
        }
        else
        {
            printf("Invalid Input! Try again!\n");
        }
    }while (choice != 1 && choice !=2);
}

void signup(void){ //Email password phonenumber name address state 
    clrscr();
    printf("Please enter your details below to signup");
}