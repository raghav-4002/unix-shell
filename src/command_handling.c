#include "command_handling.h"


void
handle_command(char **tokens)
{
    /* create a child process */
    pid_t pid = fork();

    if(pid == 0) {
        /* execute the command in the child process */
        execute_command(tokens);
    } else {
        /* make the parent process (shell) wait for child to complete the command */
        wait(NULL);
    }
}


void
execute_command(char **tokens)
{
    int return_value = execvp(tokens[0], tokens);
    if (return_value == -1 && errno == ENOENT) {
        fprintf(stderr, "%s: command not found...\n", tokens[0]);
        exit(1);
    }
}