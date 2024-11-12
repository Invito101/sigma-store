CC = gcc
CFLAGS = -Wall -g
LDFLAGS = -lsqlite3  # Linker flag for SQLite
OBJ = login-signup.o helper-functions.o db/db-utils.o encryption.o  # Add your object files here
TARGET = sigma-store  # Name of your output executable

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ) $(LDFLAGS)  # Include LDFLAGS here

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)
 