# Compiler
CC = gcc

MAKEFLAGS+= --silent

# Compiler flags
CFLAGS = -Wall -Werror -g

# Target executable
TARGET = runnable.exe

# Source files
SRCS = $(wildcard *.c)

# Object files
OBJS = $(SRCS:.c=.o)

# Default target
all: $(TARGET)

# Rule to build the target executable
$(TARGET): $(OBJS)
	$(CC) -o $@ $^

# Rule to build object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up build files - ONLY WORKS ON WINDOWS
clean:
	@del /Q $(OBJS)

# Custom target to clean up and execute
run:all
	./$(TARGET)

# Phony targets
.PHONY: all clean run