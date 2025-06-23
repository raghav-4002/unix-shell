#include "../include/lexer.h"
#include "../include/utils.h"

Element *elements;
size_t element_index;

/*
 * Reallocates space in `elements` array to
   include another element.
 *
 * Also sets the `element_type` of the element
*/
void
allocate_and_define_elem (int element_type)
{
  /* `element_index` starts with 0, thus need to add `1` */
  elements = realloc (elements, sizeof (*elements) * (element_index + 1));

  elements[element_index].element_type = element_type;
  elements[element_index].left = NULL;
  elements[element_index].right = NULL;

  elements[element_index].return_value
      = NOT_DEFINED_YET; /* same for every element */

  if (element_type != COMMAND)
    {
      /* `COMMAND` type will have an array of strings */
      elements[element_index].tokens = NULL;
    }
}

size_t
find_token_length (char *ptr)
{
  size_t token_length = 0;

  while (*ptr != '\0' && *ptr != '&' && *ptr != '|' && *ptr != ';'
         && *ptr != ' ')
    {
      token_length++;
      ptr++;
    }

  return token_length;
}

/*
 * Takes the pointer to the current character in `string`.
 * Returns an array of strings (`tokens`).
 * Each string in the array is a command and its arguments.
 * Last item of array is `NULL`.
 */

char **
create_tokens (char **string)
{
  /*
   * Reallocates `token_index` + 1 more memory to `tokens` as it finds
     more tokens.

   * Each memory block allocated is a pointer to string.
     Thus also allocates memory to hold the characters of the string.

   * Uses `memcpy` to copy the contents into the allocated block of string.

   * Skips whitespaces and only stops adding tokens if finds recognised
     character like `\0`, `|`, `&` or `;`
   */

  char **tokens = NULL;   /* Array of strings */
  size_t token_index = 0; /* Index of a token in `tokens` array */

  while (1)
    {
      tokens = realloc (tokens, sizeof (*tokens) * (token_index + 1));

      size_t token_length = find_token_length (*string);

      tokens[token_index]
          = malloc (token_length + 1); /* Added 1 for including null byte */

      memcpy (tokens[token_index], *string, token_length);
      tokens[token_index][token_length] = '\0';

      token_index++;

      /* move the pointer */
      *string = *string + token_length;

      if (**string == ' ')
        {
          /* skip spaces */
          while (**string == ' ')
            {
              (*string)++;
            }
        }

      if (**string == '\0' || **string == '&' || **string == '|'
          || **string == ';')
        break;
    }

  /* add `NULL` as the last token to signify no more tokens are present */
  tokens = realloc (tokens, sizeof (*tokens) * (token_index + 1));
  tokens[token_index] = NULL;

  return tokens;
}

void
handle_element (int element_type, char **string)
{
  allocate_and_define_elem (element_type);

  if (element_type == COMMAND)
    {
      /* Only elements of type `COMMAND` need `tokens`. */
      elements[element_index].tokens = create_tokens (string);
    }

  element_index++;
}

/* Tokenizes a string and returns an array of `Element` */
Element *
tokenize (char *raw_input)
{
  /* Set global variables */
  elements = NULL;
  element_index = 0;

  char *string = raw_input;

  /* Traverse through the string */
  while (*string != '\0')
    {
      if (*string == '|' && string[1] == '|')
        {
          handle_element (LOGIC_OR, &string);
          string = string + 2;
          continue;
        }

      if (*string == '&' && string[1] == '&')
        {
          handle_element (LOGIC_AND, &string);
          string = string + 2;
          continue;
        }

      if (*string == ';')
        {
          handle_element (NEXT, &string);
          string++;
          continue;
        }

      if (isspace (*string))
        {
          /* skip space */
          string++;
          continue;
        }

      if (isalpha (*string))
        {
          handle_element (COMMAND, &string);
          continue;
        }

      else
        {
          fprintf (stderr, "Syntax error: Unrecognised token: %c\n", *string);

          /* Add a dummy element at the end to help `free_elements` */
          allocate_and_define_elem (NIL);
          free_elements (elements);
          return NULL;
        }
    }

  /* add a dummy element at the end to signify no more elements */
  allocate_and_define_elem (NIL);

  return elements;
}
