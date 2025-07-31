#include "../include/io_handling/input.h"


int
start_shell(int argc, char *argv[])
{
    char *line = read_from_stdin();       
    Token *tokens = tokenize(line);
    parse_and_evaluate(tokens);

    return 0;
}
