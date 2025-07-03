#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../include/io_handling.h"

char *
read_input(void)
{
  char *raw_input = NULL;
  size_t n        = 0;

  /* Read a line from commandline (returns -1 on error) */
  ssize_t line_len = getline(&raw_input, &n, stdin);

  if (line_len == -1 || (line_len == 1 && raw_input[0] == '\n'))
    {
      /*
       * line_len == -1: error
       * line_len ==  1: pressing enter without any input
       */
      free(raw_input); /* `getline` uses `malloc` to allocate buffer */
      return NULL;
    }

  /* Terminate the input with null byte, replacing newline char */
  raw_input[line_len - 1] = '\0';

  return raw_input;
}

#define FALLBACK_USERNAME "<username>"
#define FALLBACK_HOSTNAME "<hostname>"
#define FALLBACK_CWD      "<current working directory>"

#define HOST_NAME_LEN     4096
void
display_prompt(void)
{
  /* Get username (returns NULL if error) */
  char *username = getlogin();

  if (!username)
    {
      perror("shell: failed to get username");
      username = FALLBACK_USERNAME; /* placeholder, in case of error */
    }

  char hostname[HOST_NAME_LEN];

  /* Get hostname (returns -1 on error) */
  int return_val = gethostname(hostname, HOST_NAME_LEN);

  if (return_val == -1)
    {
      perror("shell: failed to get hostname");
      snprintf(hostname, HOST_NAME_LEN, FALLBACK_HOSTNAME); /* placeholder */
    }

  /* Get current working directory (returns NULL if error) */
  char *working_dir = getcwd(NULL, 0);

  if (!working_dir)
    {
      perror("shell: failed to get current working directory");
      working_dir = FALLBACK_CWD;
    }

  /* Display the prompt */
  printf("\033[1;32m{%s@%s}\033[0m-[%s]\n", username, hostname, working_dir);
  printf("$ ");

  /* free memory allocated via `getcwd` */
  free(working_dir);
}
