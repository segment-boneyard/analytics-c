SRC := analytics.c
DEPS := $(wildcard deps/*/*.c)
OBJS := $(SRC:.c=.o) $(DEPS:.c=.o)

CFLAGS := -std=c99 -Wall -Wextra -Ideps

test: test.o $(OBJS)

deps/list/list.o: deps/list/list.c deps/list/list_node.c deps/list/list_iterator.c

clean:
	rm -f test test.o $(OBJS)

valgrind: test
	valgrind --leak-check=full ./$<

.PHONY: clean valgrind
