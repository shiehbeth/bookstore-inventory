# Compiler and flags
CC = gcc
CFLAGS = -I./include -Wall -g

# Directories
SDIR = src
ODIR = obj

# Source files
SRC = main.c book.c bookQueue.c DLL.c inventory.c search.c user.c
OBJ = $(addprefix $(ODIR)/, $(SRC:.c=.o))

# Executable
EXEC = main

# Default target
all: $(EXEC)

# Linking
$(EXEC): $(OBJ)
	$(CC) -o $@ $^

# Ensure the object directory exists
$(ODIR):
	@mkdir -p $(ODIR)

# Compiling source files
$(ODIR)/%.o: $(SDIR)/%.c | $(ODIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Cleaning objects and executable
clean:
	@rm -rf $(ODIR) $(EXEC)
	@echo "Object files deleted."
	@echo "Executable deleted."

fclean: clean
	@rm -rf $(EXEC)
	@echo "Executable deleted."

re: fclean all

.PHONY: all clean fclean re
