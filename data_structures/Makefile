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
#ds_objects = pqueue.o heap.o bistree.o bitree.o chtbl.o ohtbl.o set.o queue.o stack.o clist.o dlist.o list.o 
ds_objects = pqueue.o heap.o bistree.o bitree.o ohtbl.o chtbl.o set.o queue.o stack.o clist.o dlist.o list.o 

# Tests
tests = pqueue_test.out heap_test.out bistree_test.out bitree_test.out ohtbl_test.out chtbl_test.out set_test.out queue_test.out stack_test.out clist_test.out dlist_test.out list_test.out 

# Examples
examples = events.out frames.out

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
