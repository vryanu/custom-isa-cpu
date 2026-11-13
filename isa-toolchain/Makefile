CC = clang
CFLAGS = -Wall -Wextra -std=c11

main: main.c asmtobin.c bintoasm.c
	$(CC) $(CFLAGS) main.c asmtobin.c bintoasm.c -o main

clean:
	rm -f main

.PHONY: clean
