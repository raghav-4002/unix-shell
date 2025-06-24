#include "../include/input_handling.h"
#include "../include/lexer.h"
#include "../include/parser.h"
#include "../include/utils.h"

void
display_prompt (void)
{
  char *username;
  username = getlogin ();

  char hostname[256];
  gethostname (hostname, sizeof (hostname));

  char working_dir[256];
  getcwd (working_dir, sizeof (working_dir));

  printf ("\n{%s@%s}-[%s]\n", username, hostname, working_dir);
  printf ("$ ");
}

int
main (void)
{
  /* Stores the user input string */
  char *raw_input = NULL;

  Element *elements = NULL;

  while (1)
    {
      display_prompt ();

      raw_input = read_input ();
      if (raw_input == NULL)
        {
          /* in case of error or user just pressing enter, continue the
           * loop */
          continue;
        }

      elements = tokenize (raw_input); // Will return `NULL` if error happens
      if (elements)
        {
          parse_and_evaluate (elements);
          free_elements (elements);
        }

      free (raw_input); /* free memory allocated via getline */
    }

  exit (EXIT_SUCCESS);
}
