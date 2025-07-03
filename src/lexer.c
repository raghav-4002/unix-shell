#include <stdio.h>  /* provides `perror` */
#include <stdlib.h> /* provides `realloc`, `size_t` */
#include <unistd.h> /* provides `NULL` */

#include "../include/lexer.h"

/* `free`s memory allocated to tokens in case of error */
void
clean_memory(Token **tokens, int token_index)
{
  for (size_t i = 0; i < token_index; i++)
    {
      if ((*tokens)[i].type == COMMAND)
        {
          // logic to free args of command
        }
    }
  free(tokens);
}

int
add_token(Token_type token_type, Token **tokens, int *token_index)
{
  *token_index = *token_index + 1;

  /*
   * Reallocate memory to add a token.
   * Is `*token_index + 1` because `token_index`
   * starts from `0`.
   */
  *tokens = realloc(*tokens, (*token_index + 1) * sizeof (**tokens));

  /* if `realloc` fails */
  if (*tokens == NULL)
    {
      perror("realloc failed in `add_token`");
      return -1;
    }

  (*tokens)[*token_index].type          = token_type;

  /* Set default fields */
  (*tokens)[*token_index].argv          = NULL;
  (*tokens)[*token_index].argc          = 0;
  (*tokens)[*token_index].left          = NULL;
  (*tokens)[*token_index].right         = NULL;
  (*tokens)[*token_index].return_status = NOT_DEFINED;

  /* function succeeds */
  return 0;
}

Token *
tokenize(char *string)
{
  Token *tokens = NULL;    /* array of tokens */
  int token_index = -1; /* index of the latest token to be added */

  int return_val;

  while (*string != '\0')
    {
      switch (*string)
        {

        /* For `LOGIC_OR` and `PIPE` */
        case '|':
          if (string[1] == '|')
            {
              return_val = add_token(LOGIC_OR, &tokens, &token_index);
              string = string + 2;
            }

          else
            {
              return_val = add_token(PIPE, &tokens, &token_index);
              string++;
            }

          break;

        /* For `LOGIC_AND` and `BG_OPERATOR` */
        case '&':
          if (string[1] == '&')
            {
              return_val = add_token(LOGIC_AND, &tokens, &token_index);
              string = string + 2;
            }

          else
            {
              return_val = add_token(BG_OPERATOR, &tokens, &token_index);
              string++;
            }

          break;

        /* For `LEFT_PAREN` */
        case '(':
          return_val = add_token(LEFT_PAREN, &tokens, &token_index);
          string++;

          break;

        /* For `RIGHT_PAREN` */
        case ')':
          return_val = add_token(RIGHT_PAREN, &tokens, &token_index);
          string++;

          break;

        /* For `NEXT` */
        case ';':
          return_val = add_token(NEXT, &tokens, &token_index);
          string++;

          break;

        /* For `COMMANDS` */
        default:
          

          break;
        }

      if (return_val == -1)
        {
          clean_memory(&tokens, token_index);
          return NULL;
        }
    }

  /* Add `NIL` as the last token, to signify that no more tokens are present */
  return_val = add_token(NIL, &tokens, &token_index);

  if (return_val == -1)
    {
      clean_memory(&tokens, token_index);
      return NULL;
    }

  return tokens;
}
