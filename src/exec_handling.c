#include "../include/exec_handling.h"

int
execute (char **tokens)
{
  int return_value = 0;
  return_value = execvp (tokens[0], tokens);

  /* in case, the executable doesn't exist */
  if (return_value == -1 && errno == ENOENT)
    {
      fprintf (stderr, "%s: command not found...\n", tokens[0]);
      return -1;
    }

  /* else return the return value of executed program */
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

      if (return_val == 0)
        {
          node->return_value = RETURN_SUCCESS;
        }
      else
        {
          node->return_value = RETURN_FAILURE;
        }
    }
}
