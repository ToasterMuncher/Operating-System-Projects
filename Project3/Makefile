# Compiler and flags
CC	= gcc
CFLAGS	= -O3

# Targets
all: Project3.c

# Multi-threaded program
Project3.run: Project3.c
	$(CC) $(CFLAGS) -pthread Project3.c -o Project3.run

# Clean build artifacts
clean:
	rm -f Project3.run

# Phony targets
.PHONY: all clean
