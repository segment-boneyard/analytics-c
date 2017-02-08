test: test.c analytics.c
	$(CC) $^ -o $@ -Wall -Wextra

clean:
	rm -f test

valgrind: test
	valgrind --leak-check=full ./$<

.PHONY: clean valgrind
