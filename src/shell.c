#include <stdlib.h>

#include "io_handling/input.h"


int
start_shell()
{
    /* Main shell loop */
    while (1) {
        char *line = read_from_stdin();
        Token *tokens = tokenize();
        parse_and_execute(tokens);
    }

    return EXIT_SUCCESS;
}
