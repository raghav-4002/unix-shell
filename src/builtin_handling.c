#include "../include/builtin_handling.h"

/* all supported builtins; some are under construction... */
const char *builtins[] = {
  "cd", "exit", "history", "help", "exec",
};

size_t builtins_count = sizeof (builtins) / sizeof (builtins[0]);

void
change_dir (char **tokens)
{
  if (tokens[2] != NULL)
    {
      fprintf (stderr, "Too many arguments for cd...\n");
      return;
    }

  char *directory = tokens[1];

  int return_value = chdir (directory);

  /* handle directory changing errors */
  if (return_value == -1)
    {
      switch (errno)
        {
        case ENONET: // directory or file doesn't exist
          fprintf (stderr, "cd: %s: No such file or directory\n", tokens[1]);
          break;

        case EACCES: // permission for accessing directory denied
          fprintf (stderr, "cd: %s: Permission denied\n", tokens[1]);
          break;
        }
    }
}

void
execute_and_exit (char **tokens)
{
  /* make a copy of tokens, ignoring 'exec' */
  char **executable = &tokens[1];
  execvp (executable[0], executable);
}

void
display_help (void)
{
  printf ("Available builtins:\n");
  printf ("-------------------\n");

  for (size_t i = 0; i < builtins_count; i++)
    {
      printf (" %s\n", builtins[i]);
    }
}

void
handle_builtin (char **tokens)
{
  if (!strcmp (tokens[0], "cd"))
    {
      change_dir (tokens);
    }
  else if (!strcmp (tokens[0], "exit"))
    {
      printf ("exited\n");
      exit (EXIT_SUCCESS); /* simply exit the program */
    }
  else if (!strcmp (tokens[0], "exec"))
    {
      execute_and_exit (tokens);
    }
  else if (!strcmp (tokens[0], "help"))
    {
      display_help ();
    }
}

bool
is_builtin (char *token)
{
  for (size_t i = 0; i < builtins_count; i++)
    {
      if (!strcmp (builtins[i], token))
        return true;
    }

  return false;
}
