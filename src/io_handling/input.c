#include <stdio.h>

#include "input.h"


void
remove_newline(char *line, ssize_t line_len)
{
    line[line_len - 1] = '\0';
}


char *
read_from_stdin(void)
{
    char *line = NULL;
    size_t n = 0;

    ssize_t line_len = getline(&line, &n, stdin);
    remove_newline(line, line_len);

    return line;
}
