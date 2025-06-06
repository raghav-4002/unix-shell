#include "../include/input_handling.h"
#include "../include/lexer.h"
#include "../include/utils.h"


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

    while(1) {
        display_prompt();

        raw_input = read_input();

        if(raw_input == NULL) {
            /* in case of error or user pressing enter, just continue the loop */
            continue;
        }

        elements = tokenize(raw_input);

        for(size_t i = 0; elements[i].element_type != NIL; i++) {
            if(elements[i].element_type == COMMAND) {
                for(size_t j = 0; elements[i].tokens[j] != NULL; j++) {
                    printf("%s ", elements[i].tokens[j]);
                }
            }
        }

        free_elements(&elements);

        free(raw_input);    // because memory is allocated via getline
    }

    exit(EXIT_SUCCESS);
}