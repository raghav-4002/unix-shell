#include <stdio.h>

#include "input.h"


char *
read_from_stdin(void)
{
    char *line = NULL;
    size_t n = 0;

    ssize_t line_len = getline(&line, &n, stdin);

    if (line_len == -1) return NULL;

    return line;
}
