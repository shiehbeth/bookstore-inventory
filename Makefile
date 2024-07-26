# Compiler and flags
CC = gcc
CFLAGS = -I./include -Wall -g

# Source files
SRC = src/book.c src/bookQueue.c src/DLL.c src/inventory.c src/search.c src/user.c
OBJ = $(SRC:.c=.o)

# Executable
EXEC = main

# Default target
all: $(EXEC)

# Linking
$(EXEC): $(OBJ) main.o
	$(CC) -o $@ $^

# Compiling source files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean target
clean:
	rm -f $(OBJ) main.o $(EXEC)

# Dependencies
main.o: main.c $(wildcard include/*.h)
src/book.o: src/book.c include/book.h
src/bookQueue.o: src/bookQueue.c include/bookQueue.h include/book.h
src/DLL.o: src/DLL.c include/DLL.h include/book.h
src/inventory.o: src/inventory.c include/inventory.h include/book.h
src/search.o: src/search.c
