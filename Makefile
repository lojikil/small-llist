# if you want to use mmap() instead of malloc()
# set OPT to LIB_USE_MMAP
#
OPT	= NULL
EXAMPLE = list_test

llist:	clean_llist

	gcc -c -D $(OPT) -I./include -o ./llist.o src/llist.c

example:

	make llist
	gcc -I./include -o list_test ./src/example/$(EXAMPLE).c llist.o

clean_llist:
	rm -rf *.o
	rm -rf $(EXAMPLE)
