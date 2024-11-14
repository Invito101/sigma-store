CC = gcc
CFLAGS = -Wall -g
LDFLAGS = -lsqlite3
OBJ = login-signup.o utils.o db/db-utils.o db/users/users.o db/users/users-utils.o encryption.o
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