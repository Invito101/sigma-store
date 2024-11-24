#include "structs/structs.c"
#include <string.h>
#include <stdlib.h>
#include "headers.h"
#include <ncurses.h>

static OrderLL order = {"", NULL};

void CreateNewOrder(int userId) { //Called whenever a new user has to be connected to order.
    order.userId=userId;
    order.nextitem = NULL;  
}

int AddItemToOrder(int id, int userId) { // id is product id
    OrderItem* current = order.nextitem;
    while (current != NULL) {
        if (current->id == id) {
            current->quantity += quantity;
            modify_item_in_cart(userId, 1, id)//increment q by 1
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
    add_item_to_cart(userId, 1, id)// new item
    order.nextitem = NewItem;       
    return 0;
}

int DecreaseItemQuantity(int id, int userId) { // returns 0 if successful, returns 1 if item not found 
    OrderItem* current = order.nextitem;
    OrderItem* prev = NULL;

    while (current != NULL) {
        if (current->id == id) {
            current->quantity--;

            if (current->quantity == 0) { // removing item if quantity becomes 0
                delete_cart_item(userId, id);
                if (prev == NULL) {
                    order.nextitem = current->next;
                } else {
                    prev->next = current->next;
                }
                free(current); 
                return 0;
            }
            modify_item_in_cart(userId,-1,id); // incase q isnt 0 but has to be decreased
            return 0;
        }

        prev = current;
        current = current->next;
    }
    return 1; // if item not found
}

void PlaceOrder(int userId) {
    OrderItem* current = order.nextitem;
    OrderItem* temp;
    place_order(userId);
    while (current != NULL) {
        temp = current;
        current = current->next;
        free(temp);
    }
    order.nextitem = NULL;
}

void DisplayCart(int userId) {
    int size;
    int totalamt = 0;
    Cart* cartitems = get_cart_items(userId, &size);
    initscr();
    raw();
    clear();
    start_color();
    cbreak();
    noecho();
    curs_set(0);

    init_pair(1, COLOR_GREEN, COLOR_BLACK);  // Header color
    init_pair(2, COLOR_YELLOW, COLOR_BLACK); // Item details color
    init_pair(3, COLOR_RED, COLOR_BLACK);    // Total amount color

    attron(COLOR_PAIR(1));
    mvprintw(1, 5, "Your Shopping Cart");
    mvprintw(2, 5, "-------------------");
    attroff(COLOR_PAIR(1));

    for (int i = 0; i < size; i++) {
        Product* product = get_product_by_id(cartitems[i].productId);
        char* name = product->name;
        int price = product->price;
        int quantity = cartitems[i].quantity;
        int subtotal = price * quantity;
        totalamt += subtotal;

        attron(COLOR_PAIR(2));
        mvprintw(4 + i, 5, "%d. %s", i + 1, name);
        mvprintw(4 + i, 30, "Price: %d", price);
        mvprintw(4 + i, 45, "Qty: %d", quantity);
        mvprintw(4 + i, 60, "Subtotal: %d", subtotal);
        attroff(COLOR_PAIR(2));
    }

    attron(COLOR_PAIR(3));
    mvprintw(6 + size, 5, "Total Amount: %d", totalamt);
    attroff(COLOR_PAIR(3));

    refresh();
}
