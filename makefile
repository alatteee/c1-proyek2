CC = gcc
CFLAGS = -Wall -Wextra -Iinclude -I/mingw64/include
LDFLAGS = -L/mingw64/lib -lraylib -lopengl32 -lm -lpthread -lwinpthread
SRC = src/jalur.c src/menu.c src/mobil.c src/rintangan.c src/skor.c src/lives.c src/ADT.c src/finish_line.c
OBJ = $(SRC:.c=.o)
EXEC = racing_game

all: $(EXEC)

# Link semua file objek, termasuk main.o
$(EXEC): main.o $(OBJ)
	$(CC) $(CFLAGS) -o $(EXEC) main.o $(OBJ) $(LDFLAGS)

# Kompilasi file C menjadi file objek
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Bersihkan file objek dan executable
clean:
	rm -f $(OBJ) main.o $(EXEC)

# Jalankan program setelah kompilasi
run: all
	./$(EXEC)