#include "../include/utils.h"
#include <stddef.h>


/*
 * This function frees the memory allocated to elements of an array
   and the array itself.
*/
void
free_array_of_arrays(char **array, size_t array_size)
{
    /* free individual element */
    for(size_t i = 0; i < array_size; i++) {
        free(array[i]);
    }

    /* free the array */
    free(array);
    array = NULL;
}


void
free_elements(Element *elements)
{
    for(size_t i = 0; (elements)[i].element_type != NIL; i++) {

        if((elements)[i].element_type == COMMAND) {

            for(size_t j = 0; (elements)[i].tokens[j] != NULL; j++) {
                free((elements)[i].tokens[j]);
            }
            free((elements)[i].tokens);
        }
    }

    free(elements);
}