# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g

# Target executable name
TARGET = opportunity_tracker

# Source files
SRCS = main.c

# Object files
OBJS = $(SRCS:.c=.o)

# Default rule: build the executable
all: $(TARGET)

# Rule to link the object files into the final executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Rule to compile a .c file into a .o file
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to run the application
run: all
	./$(TARGET)

# Rule to clean up build files
clean:
	rm -f $(OBJS) $(TARGET) opportunities.dat

# Phony targets are not files
.PHONY: all run clean
