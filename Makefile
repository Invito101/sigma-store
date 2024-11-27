CC = gcc
CFLAGS = -Wall -g
LDFLAGS = -lsqlite3
OBJ = customer/customer-filters.o customer/customer-home.o customer/orders.o login-signup.o utils.o db/db-utils.o db/users/users.o db/users/users-utils.o db/products/products.o db/products/products-utils.o structs/structs.o encryption.o admin/home.o db/cart/cart-utils.o db/cart/cart.o db/orders/orders.o admin/View_products.o admin/pro_fun.o db/orders/orders-utils.o admin/utilities.o
TARGET = sigma-store

ifeq ($(shell uname -s), Darwin)
	CFLAGS += -I/opt/homebrew/opt/ncurses/include
	LDFLAGS += -lncurses -L/opt/homebrew/opt/ncurses/lib
else
	LDFLAGS += -lncurses
endif

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)