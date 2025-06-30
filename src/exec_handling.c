#include "../include/exec_handling.h"
#include <stdlib.h>

int
execute (char **tokens)
{
  int return_value = execvp (tokens[0], tokens);

  /* If error occurs */
  if (return_value == -1)
    {
      if (errno == ENOENT)
        {
          fprintf (stderr, "%s: command not found\n", tokens[0]);
        }
      else
        {
          perror (tokens[0]);
        }
      exit (EXIT_FAILURE);
    }

  /*
   * If execvp succeeds, this function will never return, instead
   * the program being executed will give a return return value.
   */
}

void
handle_exec (Element *node)
{
  /* create a child process */
  pid_t pid = fork ();

  if (pid == 0)
    {
      /* execute the command in the child process */
      execute (node->tokens);
    }
  else
    {
      /* make the parent process (shell) wait for child to complete the
      command
       */
      int return_val;
      wait (&return_val);

      if (return_val == EXIT_SUCCESS)
        {
          node->return_value = RETURN_SUCCESS;
        }
      else
        {
          node->return_value = RETURN_FAILURE;
        }
    }
}
