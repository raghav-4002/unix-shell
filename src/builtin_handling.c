#include "../include/builtin_handling.h"
#include <stdio.h>

/* all supported builtins; some are under construction... */
const char *builtins[] = {
  "cd", "exit", "history", "help", "exec",
};

size_t builtins_count = sizeof (builtins) / sizeof (builtins[0]);

Return_value
change_dir (char **tokens)
{
  if (tokens[2] != NULL)
    {
      fprintf (stderr, "cd: too many arguments\n");
      return RETURN_FAILURE;
    }

  int return_val;

  /* if no argument is provided */
  if (tokens[1] == NULL)
    {
      __uid_t uid = getuid (); /* user id */

      /* Change to home directory of user with id `uid` */
      return_val = chdir (getpwuid (uid)->pw_dir);
    }
  else
    {
      return_val = chdir (tokens[1]);
    }

  if (return_val == -1)
    {
      perror ("cd");
      return RETURN_FAILURE;
    }

  return RETURN_SUCCESS;
}

Return_value
execute_and_exit (char **tokens)
{
  if (tokens[1] == NULL)
    {
      /* If no args is provided to `exec`, just return */
      return RETURN_SUCCESS;
    }

  /* make a copy of tokens, ignoring 'exec' */
  char **executable = &tokens[1];

  int return_val = execvp (executable[0], executable);

  /* error occurs */
  if (return_val == -1)
    {
      if (errno == ENOENT)
        {
          fprintf (stderr, "%s: not found\n", executable[0]);
        }
      else
        {
          perror (tokens[0]);
        }

      return RETURN_FAILURE;
    }

  /* This line is never reached if execvp succeeds */
  return RETURN_SUCCESS;
}

Return_value
display_help (void)
{
  printf ("Available builtins:\n");
  printf ("-------------------\n");

  for (size_t i = 0; i < builtins_count; i++)
    {
      printf (" %s\n", builtins[i]);
    }

  return RETURN_SUCCESS;
}

bool
handle_builtin (Element *node)
{
  char **tokens = node->tokens;
  Return_value return_value;

  if (!strcmp (tokens[0], "cd"))
    {
      return_value = change_dir (tokens);
    }
  else if (!strcmp (tokens[0], "exit"))
    {
      printf ("exited\n");
      exit (EXIT_SUCCESS); /* simply exit the program */
    }
  else if (!strcmp (tokens[0], "exec"))
    {
      return_value = execute_and_exit (tokens);
    }
  else if (!strcmp (tokens[0], "help"))
    {
      return_value = display_help ();
    }
  else
    {
      return false;
    }

  node->return_value = return_value;
  return true;
}
