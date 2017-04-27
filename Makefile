SRC_DEPS := deps/asprintf/asprintf.o deps/list/list.o deps/list/list_node.o deps/list/list_iterator.o
TEST_DEPS := $(SRC_DEPS) deps/console-colors/console-colors.o deps/describe/describe.o

CFLAGS := -std=c99 -Wall -Wextra -Ideps

example: example.o analytics.o $(SRC_DEPS)
test: test.o analytics.o $(TEST_DEPS)

clean:
	rm -f example example.o analytics.o test test.o $(TEST_DEPS)

valgrind: test
	valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./$<

.PHONY: clean valgrind
