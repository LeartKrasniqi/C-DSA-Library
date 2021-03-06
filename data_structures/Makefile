# Makefile for Data Structure Library
# Includes tests and examples

# Paths
INC = ./include
SRC = ./src
TST = ./test
EX = ./examples

# Compiler and flags
CC = gcc
CFLAGS = -Wall -I$(INC)


# Core data structure objects
ds_objects = $(patsubst %.c,%.o,$(shell find $(SRC) -name '*.c' | xargs basename))

# Tests
tests = $(patsubst %.c,%.out,$(shell find $(TST) -name '*.c' | xargs basename))

# Examples
examples = $(patsubst %.c,%.out,$(shell find $(EX) -name '*.c' | xargs basename))

# Rule to make the core data structure object files
$(ds_objects): %.o: $(SRC)/%.c $(INC)/%.h
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to make the data structure library
ds_lib.a: $(ds_objects)
	ar rcs $@ $^

# Rule to compile the test files
$(tests): %.out: $(TST)/%.c ds_lib.a
	$(CC) $(CFLAGS) -o $@ $^

tests: $(tests)

# Rule to compile the examples 
$(examples): %.out: $(EX)/%.c ds_lib.a
	$(CC) $(CFLAGS) -o $@ $^

examples: $(examples)

# Clean-up
clean:
	rm -rf *.out *.o *.a
