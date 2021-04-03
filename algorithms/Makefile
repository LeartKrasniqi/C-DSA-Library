# Makefile for Data Structure Library
# Includes tests and examples

# Paths
INC = ./include
SRC = ./src
TST = ./test
EX = ./examples
DS = ../data_structures
DS_INC = $(DS)/include

# Compiler and flags
CC = gcc
CFLAGS = -Wall -I$(INC) -I$(DS_INC)
 

# Core algorithm objects
alg_objects = $(patsubst %.c,%.o,$(shell find $(SRC) -name '*.c' | xargs -n1 basename))

# Tests
tests = $(patsubst %.c,%.out,$(shell find $(TST) -name '*.c' | xargs -n1 basename))

# Examples
examples = $(patsubst %.c,%.out,$(shell find $(EX) -name '*.c' | xargs -n1 basename))

# Rule to make the data structure library
.PHONY: ds_lib.a
ds_lib.a:
	$(MAKE) -C $(DS) $@
	cp $(DS)/$@ .

# Rule to make the core algorithm object files
$(alg_objects): %.o: $(SRC)/%.c $(INC)/%.h
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to make the algorithm library
alg_lib.a: $(alg_objects) 
	ar rcs $@ $^

# Rule to compile the test files
$(tests): %.out: $(TST)/%.c ds_lib.a alg_lib.a
	$(CC) $(CFLAGS) -o $@ $^

tests: $(tests)

# Rule to compile the examples 
$(examples): %.out: $(EX)/%.c ds_lib.a alg_lib.a
	$(CC) $(CFLAGS) -o $@ $^

examples: $(examples)

# Clean-up
clean:
	rm -rf *.out *.o *.a
