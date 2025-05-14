#include <stdio.h>


int
main(void)
{
    char *line = NULL;
    size_t n = 0;

    while(1) {
        printf("csh> ");
        getline(&line, &n, stdin);
        puts(line);
    }
}