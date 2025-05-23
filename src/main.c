#include "../include/input_handling.h"
#include "../include/process.h"
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

    printf("{%s on %s}-[%s]: ", username, hostname, working_dir);
}


int
main(void)
{
    char **commands_array = NULL;
    size_t commands_count = 0;

    while(1) {
        display_prompt();

        commands_array = read_input(&commands_count);
        if(commands_array == NULL) {
            /* in case of error or user pressing enter, just continue the loop */
            continue;
        }

        process_and_execute(commands_array);

        free_array_of_arrays(commands_array, commands_count);
    }

    return EXIT_SUCCESS;
}