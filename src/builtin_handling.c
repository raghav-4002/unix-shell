#include "../include/builtin_handling.h"

/* all supported builtins; some are under construction... */
const char *builtins[] = {
  "cd", "exit", "history", "help", "exec",
};

size_t builtins_count = sizeof (builtins) / sizeof (builtins[0]);

Return_status
change_dir (char **argv)
{
  if (argv[2] != NULL)
    {
      fprintf (stderr, "cd: too many arguments\n");
      return RETURN_FAILURE;
    }

  int return_val;

  /* if no argument is provided */
  if (argv[1] == NULL)
    {
      __uid_t uid = getuid (); /* user id */

      /* Change to home directory of user with id `uid` */
      return_val = chdir (getpwuid (uid)->pw_dir);
    }
  else
    {
      return_val = chdir (argv[1]);
    }

  if (return_val == -1)
    {
      perror ("cd");
      return RETURN_FAILURE;
    }

  return RETURN_SUCCESS;
}

Return_status
execute_and_exit (char **argv)
{
  if (argv[1] == NULL)
    {
      /* If no argv is provided to `exec`, just return */
      return RETURN_SUCCESS;
    }

  /* make a copy of tokens, ignoring 'exec' */
  char **executable = &argv[1];

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
          perror (argv[0]);
        }

      return RETURN_FAILURE;
    }

  /* This line is never reached if execvp succeeds */
  return RETURN_SUCCESS;
}

Return_status
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
handle_builtin (Token *node)
{
  char **argv = node->argv;
  Return_status return_status;

  if (!strcmp (argv[0], "cd"))
    {
      return_status = change_dir (argv);
    }
  else if (!strcmp (argv[0], "exit"))
    {
      printf ("exited\n");
      exit (EXIT_SUCCESS); /* simply exit the program */
    }
  else if (!strcmp (argv[0], "exec"))
    {
      return_status = execute_and_exit (argv);
    }
  else if (!strcmp (argv[0], "help"))
    {
      return_status = display_help ();
    }
  else
    {
      return false;
    }

  node->return_status = return_status;
  return true;
}
