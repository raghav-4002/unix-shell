#include "../include/parsing.h"
#include "../include/builtin_handling.h"
#include "../include/exec_handling.h"


char **
parse_semicolons(char **tokens)
{
    
}


void
parse_and_execute(char **tokens)
{
    char **command = NULL;

    while((command = parse_semicolons(tokens)) != NULL) {
        if(is_builtin(command[0])) {
            handle_builtin(command);
        } else{
            handle_exec(command);
        }
    }
}