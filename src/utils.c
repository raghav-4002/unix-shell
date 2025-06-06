#include "../include/utils.h"


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
free_elements(Element *elements, size_t total_elements)
{
    size_t i;

    for(i = 0; elements[i].element_type != NIL; i++) {
        if(elements[i].element_type == COMMAND) {
            size_t j = 0;

            while(elements[i].tokens[j] != NULL) {
                free(elements[i].tokens[j]);
                j++;
            }
            free(elements[i].tokens);
        }
    }

    free(elements);
}