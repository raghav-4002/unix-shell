#include <stdio.h>  /* provides `perror`, `ssize_t`, `size_t` */
#include <stdlib.h> /* provides `realloc`, `free`, `malloc` */
#include <string.h> /* provides `strncpy` */

#include "../include/lexer.h"

/* `free`s memory allocated to tokens in case of error */
void
clean_memory (Token **tokens, ssize_t token_index)
{
  for (ssize_t i = 0; i < token_index; i++)
    {
      if ((*tokens)[i].type == COMMAND)
        {
          for (size_t i = 1; i <= (*tokens)->argc; i++)
            {
              free ((*tokens)->argv[i - 1]);
            }
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
add_token (Token **tokens, ssize_t *token_index, Token_type token_type)
{
  /* `*token_index` starts from `-1` */
  *token_index = *token_index + 1;
  *tokens = realloc (*tokens, (*token_index + 1) * sizeof (**tokens));

  /* `realloc` fails */
  if (*tokens == NULL)
    {
      perror ("realloc failed in `add_token`");
      return -1;
    }

  /* Initialize the token with default values */
  (*tokens)[*token_index] = init_token (token_type);

  return 0;
}

int
reallocate_arg_array (Token *token)
{
  char **argv = token->argv;
  size_t argc = token->argc;

  /* `argc` starts from `0` */
  argc++;

  argv = realloc (argv, argc * sizeof (*argv));

  if (argv == NULL)
    {
      perror ("reallocate_arg_array");
      return -1;
    }

  argv[argc - 1] = NULL;

  token->argv = argv;
  token->argc = argc;

  return 0;
}

int
allocate_mem_for_string (size_t upper_lim, Token *token)
{
  char **argv = token->argv;
  size_t argc = token->argc;

  /* `upper_lim + 1`: `1` extra byte for null-character */
  argv[argc - 1] = malloc (upper_lim + 1);

  if (argv[argc - 1] == NULL)
    {
      perror ("allocate_mem_for_string");
      return -1;
    }

  return 0;
}

int
add_arg (char *string, size_t upper_lim, Token *token)
{
  int return_val = allocate_mem_for_string (upper_lim, token);

  if (return_val == -1)
    {
      return -1;
    }

  char **argv = token->argv;
  size_t argc = token->argc;

  /* Copy the contents from `string` to argv array, including '\0' */
  snprintf (argv[argc - 1], upper_lim + 1, "%s", string);

  return 0;
}

int
tokenize_command (char *string, size_t *advance, Token *token)
{
  *advance = 0; /* holds the length of a single argument */
  int return_val = NOT_DEFINED;

  while (1)
    {
      if (string[*advance] == ' ' || string[*advance] == '&'
          || string[*advance] == '|' || string[*advance] == ';'
          || string[*advance] == '\0')
        {
          reallocate_arg_array (token);
          add_arg (string, *advance, token);

          if (string[*advance] != ' ')
            break;

          string += *advance;
          *advance = 0;
        }

      else
        (*advance)++;
    }

  reallocate_arg_array (token);
  char **argv = token->argv;
  size_t argc = token->argc;

  argv[argc - 1] = NULL;

  return 0;
}

void
find_token_type (char *string, size_t *advance, Token_type *token_type)
{
  switch (*string)
    {
    /* `LOGIC_OR` and `PIPE` */
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

    /* `LOGIC_AND` and `BG_OPERATOR` */
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

    /* `LEFT_PAREN` */
    case '(':
      *token_type = LEFT_PAREN;
      *advance = 1;

      break;

    /* `RIGHT_PAREN` */
    case ')':
      *token_type = RIGHT_PAREN;
      *advance = 1;

      break;

    /* `NEXT` */
    case ';':
      *token_type = NEXT;
      *advance = 1;

      break;

    /* No more characters in string are left */
    case '\0':
      *token_type = NIL;
      *advance = 0;

      break;

    /* `COMMANDS` */
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
  ssize_t token_index = -1;

  /* Analyse the string, character by character */
  while (1)
    {
      /* Skip space */
      if (*string == ' ')
        {
          string++;
          continue;
        }

      size_t advance = 0; /* move the string pointer by this */
      Token_type token_type = NIL;

      /* If `*string` is '\0', `token_type` will become `NIL` */
      find_token_type (string, &advance, &token_type);

      /* Add a new token in `tokens` array */
      int return_val = add_token (&tokens, &token_index, token_type);

      /* in case of error, delete already created tokens */
      if (return_val == -1)
        {
          clean_memory (&tokens, token_index);
          return NULL;
        }

      if (token_type == COMMAND)
        return_val = tokenize_command (string, &advance, &tokens[token_index]);

      if (return_val == -1)
        {
          clean_memory (&tokens, token_index);
          return NULL;
        }

      /* last token */
      if (token_type == NIL)
        break;

      /* Move the string pointer */
      string += advance;
    }

  return tokens;
}
