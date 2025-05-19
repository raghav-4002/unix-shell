main: src/main.c
	$(CC) -Iinclude src/*.c

debug: src/main.c
	$(CC) -Iinclude -g src/*.c
