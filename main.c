#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>


void
die(const char *error_msg)
{
    perror(error_msg);
    exit(1);
}


void
execute_command(char *line)
{
    pid_t pid = fork();

    if(pid == 0) {
        char *args[] = {line, NULL};
        execvp(args[0], args);
    } else {
        wait(NULL);
    }
}


int
main(void)
{
    char *line = NULL;
    size_t n = 0;
    ssize_t line_len;

    /* repeatedly take input */
    while(1) {
        printf("seash> ");

        if((line_len = getline(&line, &n, stdin)) == -1)
            die("getline");

        // basic parsing
        line[line_len - 1] = '\0';

        execute_command(line);
    }

    return EXIT_SUCCESS;
}