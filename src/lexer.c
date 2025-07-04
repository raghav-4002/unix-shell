#include <stdio.h>  /* provides `perror` */
#include <stdlib.h> /* provides `realloc`, `size_t` */
#include <unistd.h> /* provides `NULL` */

#include "../include/lexer.h"

/* `free`s memory allocated to tokens in case of error */
void
clean_memory (Token **tokens, int token_index)
{
  for (size_t i = 0; i < token_index; i++)
    {
      if ((*tokens)[i].type == COMMAND)
        {
          // logic to free args of command
        }
    }
  free (tokens);
}

Token
init_token (Token_type token_type)
{
  Token token;

  token.type = token_type;
  token.argv = NULL;
  token.argc = 0;
  token.left = NULL;
  token.right = NULL;
  token.return_status = NOT_DEFINED;

  return token;
}

int
create_and_add_token (Token **tokens, size_t *token_index,
                      Token_type token_type)
{
  *token_index = *token_index + 1;

  /*
   * Reallocate memory to add a token.
   * Is `*token_index + 1` because `token_index`
   * starts from `0`.
   */
  *tokens = realloc (*tokens, (*token_index + 1) * sizeof (**tokens));

  /* if `realloc` fails */
  if (*tokens == NULL)
    {
      perror ("realloc failed in `add_token`");
      return -1;
    }

  (*tokens)[*token_index] = init_token (token_type);

  /* function succeeds */
  return 0;
}

void
handle_command(char *string, size_t *advance, Token **tokens, size_t *token_index)
{
  *advance = 0;   

  while (string[*advance] != '&'
      && string[*advance] != '|'
      && string[*advance] != ';'
      && string[*advance] != '\0')
  {
    *advance += 1;


  }
}

void
find_token_type (char *string, size_t *advance, Token_type *token_type)
{
  switch (*string)
    {
    /* For `LOGIC_OR` and `PIPE` */
    case '|':
      if (string[1] == '|')
        {
          *token_type = LOGIC_OR;
          *advance = 2;
        }

      else
        {
          *token_type = PIPE;
          *advance = 1;
        }

      break;

    /* For `LOGIC_AND` and `BG_OPERATOR` */
    case '&':
      if (string[1] == '&')
        {
          *token_type = LOGIC_AND;
          *advance = 2;
        }

      else
        {
          *token_type = BG_OPERATOR;
          *advance = 1;
        }

      break;

    /* For `LEFT_PAREN` */
    case '(':
      *token_type = LEFT_PAREN;
      *advance = 1;

      break;

    /* For `RIGHT_PAREN` */
    case ')':
      *token_type = RIGHT_PAREN;
      *advance = 1;

      break;

    /* For `NEXT` */
    case ';':
      *token_type = NEXT;
      *advance = 1;

      break;

    case '\0':
      *token_type = NIL;
      *advance = 0;

    /* For `COMMANDS` */
    default:
      *token_type = COMMAND;
      *advance = 0;

      break;
    }
}

Token *
tokenize (char *string)
{
  Token *tokens = NULL;
  size_t token_index = 0;

  while (*string != '\0')
    {
      size_t advance = 0; /* move the pointer by this */
      Token_type token_type;

      find_token_type (string, &advance, &token_type);

      int return_val
          = create_and_add_token (&tokens, &token_index, token_type);

      /* in case of error, delete already created tokens */
      if (return_val == -1)
        {
          clean_memory (&tokens, token_index);
          return NULL;
        }

      /* last token */
      if (token_type == NIL)
        break;

      if (token_type == COMMAND)
        {
          
        }

      string += advance;
    }

  return tokens;
}
