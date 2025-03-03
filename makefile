CC = gcc
CFLAGS = -Wall -Iinclude $(shell pkg-config --cflags SDL3)
LDFLAGS = $(shell pkg-config --libs SDL3)
SRC = main.c $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)
TARGET = game

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJ) $(TARGET)