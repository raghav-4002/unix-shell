#include "../include/process.h"
#include "../include/tokenization.h"
#include "../include/utils.h"


void
process_and_execute(char *raw_input)
{
    // remove semicolons and create an array of strings
    char **string_array = NULL;
    size_t array_size = 0;

    string_array = remove_semicolons(raw_input, &array_size);

    
    /* 
       traverse thru. each element of `string_array`, 
       find tokenzie again, finding tokens separated by 
       space. Then find the logical relation between 
       each token.
     */

    size_t i = 0;
    char **token_array = NULL;
    size_t token_count = 0;

    while(string_array[i] != NULL) {
        // do something with string_array[i]
    }

    free_array_of_arrays(string_array, array_size);
}