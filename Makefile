main: src/main.c
	$(CC) src/*.c -o shell

debug: src/main.c
	$(CC) -Iinclude -g src/*.c
