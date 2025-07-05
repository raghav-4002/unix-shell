#include <stdio.h>  /* provides `perror` */
#include <stdlib.h> /* provides `realloc`, `size_t` */
#include <unistd.h> /* provides `NULL` */
#include <string.h> /* provides `strncpy` */

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

int
allocate_mem_for_arg_array(Token *token)
{
  char **argv = token->argv;
  size_t argc = token->argc;

  /* `argc` starts from `0` */
  argc++;

  argv = realloc(argv, argc * sizeof(*argv));
  if(argv == NULL)
  {
    perror("allocate_mem_for_arg_array");
    return -1;
  }

  token->argv = argv;
  token->argc = argc;

  return 0;
}

int
allocate_mem_for_string(size_t upper_lim, Token *token)
{
  char **argv = token->argv;  /* `argv` can never be `NULL` */
  size_t argc = token->argc;

  /* `upper_lim + 1`: `1` extra byte for null-character */
  argv[argc - 1] = realloc(argv[argc - 1], upper_lim + 1);
  if(argv[argc - 1] == NULL)
  {
    perror("allocate_mem_for_string");
    return -1;
  }

  return 0;
}

int
add_arg(char *string, size_t upper_lim, Token *token)
{
  int return_val = allocate_mem_for_string(upper_lim, token);
  if(return_val == -1)
  {
    return -1;
  }

  char **argv = token->argv;
  size_t argc = token->argc;

  /* Copy the contents from `string` to argv array */ 
  strncpy(argv[argc - 1], string, upper_lim);

  return 0;
}

int
tokenize_command(char *string, size_t *advance, Token *token)
{
  *advance = 0;  /* will hold the length of a single argument */

  while (string[*advance] != '&' && string[*advance] != '|'
         && string[*advance] != ';' && string[*advance] != '\0')
    {
      *advance += 1;

      /*
       * If space is encountered, meaning that an argument from
       * position of pointer `string` to `string + advance` is
       * found.
       * Thus, allocate memory in argv array member of struct `tokens`
       * and add that argument into the array.
       */
      if (string[*advance] == ' ')
        {
          int return_val;

          return_val = allocate_mem_for_arg_array(token);
          if(return_val == -1)
          {
            return -1;
          }
          
          return_val = add_arg(string, *advance, token);
          if(return_val == -1)
          {
            return -1;
          }
      
          while (string[*advance] != ' ')
            (*advance)++;

          string += *advance;
          *advance = 0;
        }
    }

  int return_val;

  return_val = allocate_mem_for_arg_array(token);
  if(return_val == -1)
  {
   return -1;
  }

  return_val = add_arg(string, *advance, token);
  if(return_val == -1)
  {
    return -1;
  }

  return 0;
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
          return_val = tokenize_command(string, &advance, &tokens[token_index]);
          if(return_val == -1)
          {
            clean_memory(&tokens, token_index);
            return NULL;
          }
        }

      string += advance;
    }

  return tokens;
}
