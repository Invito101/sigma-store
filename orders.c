#include "structs/structs.c"
#include <string.h>
#include <stdlib.h>

static Order order = {"", NULL};

void CreateNewOrder(char useremail[]) {
    strncpy(order.useremail, useremail, sizeof(order.useremail) - 1);
    order.nextitem = NULL;  
}

int AddItemToOrder(int id) {
    OrderItem* current = order.nextitem;
    while (current != NULL) {
        if (current->id == id) {
            current->quantity += quantity;
            return 0;
        }
        current = current->next;
    }
    OrderItem* NewItem = (OrderItem*)malloc(sizeof(OrderItem));
    if (NewItem == NULL) {
        return 1;
    }
    NewItem->id = id;
    NewItem->quantity = 1; // Quantity starts at 1 by default
    NewItem->next = order.nextitem; 
    order.nextitem = NewItem;       
    return 0;
}

int DecreaseItemQuantity(int id) { // returns 0 if successful, returns 1 if item not found 
    OrderItem* current = order.nextitem;
    OrderItem* prev = NULL;

    while (current != NULL) {
        if (current->id == id) {
            current->quantity--;

            if (current->quantity == 0) { // removing item if quantity becomes 0
                if (prev == NULL) {
                    order.nextitem = current->next;
                } else {
                    prev->next = current->next;
                }
                free(current); 
            }
            return 0;
        }

        prev = current;
        current = current->next;
    }
    return 1;
}
