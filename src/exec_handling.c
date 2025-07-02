#include "../include/exec_handling.h"

int
execute (char **argv)
{
  int return_value = execvp (argv[0], argv);

  /* If error occurs */
  if (return_value == -1)
    {
      if (errno == ENOENT)
        {
          fprintf (stderr, "%s: command not found\n", argv[0]);
        }
      else
        {
          perror (argv[0]);
        }
      exit (EXIT_FAILURE);
    }

  /*
   * If execvp succeeds, this function will never return, instead
   * the program being executed will give a return return value.
   */
}

void
handle_exec (Token *node)
{
  /* create a child process */
  pid_t pid = fork ();

  int wstatus;
  int return_val;

  switch (pid)
    {
    case 0:
      /* execute the command in the child process */
      execute (node->argv);

      break;

    case -1:
      /* handle fork failing */
      perror (node->argv[0]);
      node->return_status = RETURN_FAILURE;

      break;

    default:
      /*
       * make the parent process (shell) wait for child to complete the
         command
       */
      return_val = wait (&wstatus);

      if (wstatus == EXIT_SUCCESS)
        {
          node->return_status = RETURN_SUCCESS;
        }
      else
        {
          node->return_status = RETURN_FAILURE;
        }

      break;
    }
}
