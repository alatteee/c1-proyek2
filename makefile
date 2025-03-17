CC = gcc
CFLAGS = -Wall -Wextra -Iinclude -I/mingw64/include
LDFLAGS = -L/mingw64/lib -lraylib -lopengl32 -lm -lpthread -lwinpthread
SRC = main.c src/jalur.c src/menu.c src/mobil.c src/rintangan.c src/skor.c
OBJ = $(SRC:.c=.o)
EXEC = racing_game

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJ) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)

run: all
	./$(EXEC)
