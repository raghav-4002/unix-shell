#include "../include/exec_handling.h"

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

  int wstatus;
  int return_val;

  switch (pid)
    {
    case 0:
      /* execute the command in the child process */
      execute (node->tokens);

      break;

    case -1:
      /* handle fork failing */
      perror (node->tokens[0]);
      node->return_value = RETURN_FAILURE;

      break;

    default:
      /*
       * make the parent process (shell) wait for child to complete the
         command
       */
      return_val = wait (&wstatus);

      if (wstatus == EXIT_SUCCESS)
        {
          node->return_value = RETURN_SUCCESS;
        }
      else
        {
          node->return_value = RETURN_FAILURE;
        }

      break;
    }
}
