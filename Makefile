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

# Clean up build files - Requires WSL to run on windows
clean:
ifeq ($(OS),Windows_NT)
	C:\Windows\sysnative\wsl.exe rm *.o
else
	rm -f $(OBJS) $(TARGET)
endif
# wsl rm -f $(OBJS) $(TARGET)
#powershell Remove-Item *.o


# Custom target to clean up and execute
run:
	make start
	make clean

start:all
	./$(TARGET)

# Phony targets
.PHONY: all clean run start

# @del /Q $(OBJS)