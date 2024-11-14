CC = gcc
CFLAGS = -Wall -g
LDFLAGS = -lsqlite3  # Linker flag for SQLite
OBJ = login-signup.o utils.o db/db-utils.o db/users/users.c encryption.o  # Add your object files here
TARGET = sigma-store  # Name of your output executable

# Check for macOS
ifeq ($(shell uname -s), Darwin)
	CFLAGS += -I/opt/homebrew/opt/ncurses/include
	LDFLAGS += -lncurses -L/opt/homebrew/opt/ncurses/lib
else
	$(info Not)
	LDFLAGS += -lncurses
endif

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ) $(LDFLAGS)  # Include LDFLAGS here

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)