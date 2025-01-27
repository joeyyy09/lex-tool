# Compiler settings
CC = gcc                            # Specifies the C compiler to use
CFLAGS = -Wall -Wextra -I./include # Compiler flags: warnings and include path

# Directory structure
SRC_DIR = src                       # Source files directory
OBJ_DIR = obj                       # Object files directory
BIN = lexer                         # Output binary name

# Find source files and generate object file names
SRCS = $(wildcard $(SRC_DIR)/*.c)  # Gets all .c files in src/
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)  # Converts src/file.c to obj/file.o

# Link object files into final executable
$(BIN): $(OBJS)
	$(CC) $(OBJS) -o $@

# Compile source files into object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)           # Create obj directory if it doesn't exist
	$(CC) $(CFLAGS) -c $< -o $@    # Compile .c to .o

.PHONY: clean test                  # Declare targets that aren't files

test: $(BIN)                        # Run the lexer on input.c
	./$(BIN) input.c

clean:                              # Remove generated files
	rm -rf $(OBJ_DIR) $(BIN)