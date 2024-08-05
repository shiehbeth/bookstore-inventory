
# Compiler
CC = gcc

# Compiler flags
CFLAGS = -I./include -Wall -Wextra -std=c99 -pedantic -fsanitize=address -g

# Linker flags
LDFLAGS = -lmysqlclient -fsanitize=address

# Source and object files
SRCDIR = src
OBJDIR = obj

# Source files
SRC = $(wildcard $(SRCDIR)/*.c)
OBJ = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRC))

# Executable
EXEC = Book

# Default target
all: $(EXEC)

# Linking
$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $@ $(LDFLAGS)

# Ensure the object directory exists
$(ODIR):
	@mkdir -p $(ODIR)

# Compile each source file to an object file
$(OBJDIR)/%.o: $(SRCDIR)/%.c
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
