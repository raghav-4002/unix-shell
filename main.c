#include <stdlib.h>
#include <stdio.h>


char *
read_input(void)
{
    char *line = NULL;
    size_t n = 0;
    ssize_t line_len;

    /* input line */
    line_len = getline(&line, &n, stdin);

    /* add null byte at the end */
    line[line_len - 1] = '\0';

    return line;
}


int
main(void)
{
    char *line;

    while(1) {
        line = NULL;

        printf("seash> ");
        line = read_input();

        /* free the memory allocated by read_input function */
        free(line);
    }

    return EXIT_SUCCESS;
}