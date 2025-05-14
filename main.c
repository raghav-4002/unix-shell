#include <stdio.h>
#include <stdlib.h>


void
kill(const char *error_msg)
{
    perror(error_msg);
    exit(1);
}

int
main(void)
{
    char *line = NULL;
    size_t n = 0;

    /* repeatedly take input */
    while(1) {
        printf("csh> ");

        if(getline(&line, &n, stdin) == -1) kill("getline");

        fputs(line, stdout);
    }
}