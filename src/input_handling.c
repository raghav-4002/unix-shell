#include "../include/input_handling.h"

char *
read_input (void)
{
  char *raw_input = NULL;
  size_t n = 0;
  ssize_t line_len;

  /* read raw input from the commandline */
  line_len = getline (&raw_input, &n, stdin);

  if (line_len == -1 || line_len == 1)
    {
      /* in case of error, or if user just presses enter */
      free(raw_input);
      return NULL;
    }

  /* terminate the input with null byte, replacing newline char */
  raw_input[line_len - 1] = '\0';

  return raw_input;
}
