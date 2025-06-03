#include "../include/input_handling.h"
#include "../include/lexer.h"
#include "../include/parser.h"


void
display_prompt(void)
{
    char *username;
    username = getlogin();

    char hostname[256];
    gethostname(hostname, sizeof(hostname));

    char working_dir[256];
    getcwd(working_dir, sizeof(working_dir));

    printf("\n{%s@%s}-[%s]\n", username, hostname, working_dir);
    printf("$ ");
}


int
main(void)
{
    char *raw_input = NULL;
    Element *elements = NULL;
    size_t total_elements = 0;

    while(1) {
        display_prompt();

        /* `commands_array` will have commands after semicolons have been separated */
        raw_input = read_input();
        if(raw_input == NULL) {
            /* in case of error or user pressing enter, just continue the loop */
            continue;
        }

        elements = tokenize(raw_input, &total_elements);
        parse_and_execute(elements);

        free(raw_input);    // because memory is allocated via getline
    }

    exit(EXIT_SUCCESS);
}