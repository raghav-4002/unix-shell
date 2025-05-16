#include <stdlib.h>
#include <stdio.h>


void
accept_line(void)
{
    char *line = NULL;
    size_t n = 0;
    ssize_t line_len;

    /* input line */
    line_len = getline(&line, &n, stdin);

    /* add null byte at the end */
    line[line_len - 1] = '\0';
}


int
main(void)
{
    while(1) {
        printf("seash> ");
        accept_line();
    }

    return EXIT_SUCCESS;
}