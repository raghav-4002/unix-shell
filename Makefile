main: src/main.c
	$(CC) src/*.c -o seash

debug: src/main.c
	$(CC) -Iinclude -g src/*.c
