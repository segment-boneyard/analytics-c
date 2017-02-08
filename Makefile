test: test.c analytics.c
	$(CC) $^ -o $@ -Wall -Wextra

clean:
	rm -f test

.PHONY: clean
