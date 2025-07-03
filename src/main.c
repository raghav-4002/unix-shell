#include <stdlib.h>

#include "../include/io_handling.h"
#include "../include/lexer.h"
#include "../include/parser.h"
#include "../include/utils.h"

int
main(void)
{
  char *raw_input = NULL;
  Token *tokens   = NULL;  /* an array of `Token` */

  while (1)
    {
      /* Display shell prompt */
      display_prompt();

      /* Read user input (NULL if empty line or error) */
      raw_input = read_input();

      if (raw_input == NULL)
        continue;

      /* Lexing: splitting into tokens (NULL on failure) */
      tokens = tokenize(raw_input);

      if (tokens)
        {
          parse_and_evaluate(tokens);
          free_tokens(tokens);
        }

      free(raw_input); /* free memory allocated via getline */
    }

  exit(EXIT_SUCCESS);
}
