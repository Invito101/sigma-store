CC = gcc
CFLAGS = -Wall -g
OBJ = login-signup.o  # Add your new object file here
TARGET = sigma-store  # Name of your output executable

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) -o $(TARGET) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)