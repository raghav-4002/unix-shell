#include "../include/lexer.h"

Element *elements;
size_t element_index;

/*
 * Reallocates space in `elements` array to
   include another element.
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
   returns an array of strings, where each item
   of array is either a command or the command's
   arguments
 */
char **
create_tokens (char **string)
{
  /*
   * `string` is passed as reference because changes must
      persist between both the functions
  */

  char **tokens = NULL;
  size_t token_index = 0;

  while (1)
    {
      /* Add space for one more token; added `1` as `tokens_index` starts from
       * `0` */
      tokens = realloc (tokens, sizeof (*tokens) * (token_index + 1));

      size_t token_length = find_token_length (*string);

      /* allocate memory for a single token; have added `1` to include
       * null-byte */
      tokens[token_index] = malloc (token_length + 1);

      /* copy the contents of input into `tokens` array */
      memcpy (tokens[token_index], *string, token_length);

      /* add null byte at the end of the token */
      tokens[token_index][token_length] = '\0';

      token_index++; // increment token count

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

  /* add `NULL` as the last token to signify no more arguments are present */
  tokens = realloc (tokens, sizeof (*tokens) * (token_index + 1));
  tokens[token_index] = NULL;

  return tokens;
}

void
handle_command (char **string)
{
  /* allocate space for one more element */
  allocate_and_define_elem (COMMAND);
  elements[element_index].tokens = create_tokens (string);

  element_index++;
}

void
handle_operand (int operand)
{
  allocate_and_define_elem (operand);
  element_index++;
}

/* Tokenizes a string and returns an array of `Element` */
Element *
tokenize (char *raw_input)
{
  /* initialize the global variables */
  elements = NULL;
  element_index = 0;

  char *string = raw_input;

  while (*string != '\0')
    {
      if (*string == '|' && string[1] == '|')
        {
          handle_operand (LOGIC_OR);
          string = string + 2;
          continue;
        }

      if (*string == '&' && string[1] == '&')
        {
          handle_operand (LOGIC_AND);
          string = string + 2;
          continue;
        }

      if (*string == ';')
        {
          handle_operand (NEXT);
          string++;
          continue;
        }

      if (isspace (*string))
        {
          /* skip space */
          string++;
          continue;
        }

      if (isalpha(*string))
        {
          handle_command (&string);
          continue;
        }

      else {
        fprintf(stderr, "Syntax error: Unrecognised token: %c\n", *string);
        return NULL;
      }
    }

  /* add a dummy element at the end to signify no more elements */
  allocate_and_define_elem (NIL);

  return elements;
}