#include <string.h>
#include <stdlib.h>
#include "../headers.h"
#include <ncurses.h>

static OrderLL order;
void LoadLL(int userId){ //first free anything if something is there, then extract from sql
    OrderItem* current = order.nextitem;
    OrderItem* temp;
    while (current != NULL) {
        temp = current;
        current = current->nextitem;
        free(temp);
    }
    order.nextitem = NULL;
    order.userId=userId;
    int size;
    Cart* cartitems = get_cart_items(userId, &size);
    for (int i = 0; i < size; i++) {
        OrderItem* newItem = (OrderItem*)malloc(sizeof(OrderItem));
        newItem->id = cartitems[i].productId;
        newItem->quantity = cartitems[i].quantity;
        newItem->nextitem = order.nextitem;
        order.nextitem = newItem;
    }
}
int AddItemToOrder(int id, int userId) { // id is product id
    LoadLL(userId);
    OrderItem* current = order.nextitem;
    while (current != NULL) {
        if (current->id == id) {
            current->quantity += 1;
            modify_item_in_cart(userId, current->quantity, id);//increment q by 1
            return 0;
        }
        current = current->nextitem;
    }
    OrderItem* NewItem = (OrderItem*)malloc(sizeof(OrderItem));
    if (NewItem == NULL) {
        return 1;
    }
    NewItem->id = id;
    NewItem->quantity = 1; // Quantity starts at 1 by default
    NewItem->nextitem = order.nextitem; 
    add_item_to_cart(userId, 1, id);// new item
    order.nextitem = NewItem;  
    return 0;
}

int DecreaseItemQuantity(int id, int userId) { // returns 0 if successful, returns 1 if item not found 
    LoadLL(userId);
    OrderItem* current = order.nextitem;
    OrderItem* prev = NULL;

    while (current != NULL) {
        if (current->id == id) {
            current->quantity--;

            if (current->quantity == 0) { // removing item if quantity becomes 0
                delete_cart_item(userId, id);
                if (prev == NULL) {
                    order.nextitem = current->nextitem;
                } else {
                    prev->nextitem = current->nextitem;
                }
                free(current); 
                return 0;
            }
            modify_item_in_cart(userId,current->quantity,id); // incase q isnt 0 but has to be decreased
            return 0;
        }

        prev = current;
        current = current->nextitem;
    }
    return 1; // if item not found
}

void PlaceOrder(int userId) {
    LoadLL(userId);
    OrderItem* current = order.nextitem;
    OrderItem* temp;
    place_order(userId);
    while (current != NULL) {
        temp = current;
        current = current->nextitem;
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
    if(size==0){
        attron(COLOR_PAIR(1));
        mvprintw(3,5, "No Items Currently!");
        attroff(COLOR_PAIR(1));
    }
    else{
    for (int i = 0; i < size; i++) {
        Product* product = get_product_by_id(cartitems[i].productId);
        if (product==NULL){
            attron(COLOR_PAIR(2));
            mvprintw(4,5,"ERROR: Product not found");
            attroff(COLOR_PAIR(2));
            break;
        }
        else{
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
    }

    attron(COLOR_PAIR(3));
    mvprintw(6 + size, 5, "Total Amount: %d", totalamt);
    attroff(COLOR_PAIR(3));
    }
    refresh();
}
