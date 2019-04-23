#include "cli.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define APP_NAME "grv"

void show_usage() {
  printf (("Usage: %s [PROGRAM] [SOFT LIMIT] [HARD LIMIT] [FLAGS]\n"), APP_NAME);
      fputs (("\
Run program in a memory constrained environment\n\
\n\
"), stdout);
      fputs (("\
Mandatory arguments to long options are mandatory for short options too.\n\
"), stdout);
      fputs (("\
  [SOFT LIMIT]                Set the soft limit for the designated program\n\
  [HARD LIMIT]                Set the hard limit for the desginated program\n\
  [FLAGS]                     Set the flags or positional arguments for the program\n\
"), stdout);
      fputs (("\
\n\
Exit status:\n\
 0  if OK,\n\
 1  if problem running program\n\
"), stdout);
}

void parse_args(int argc, char** argv, struct program* p) {
  if (argc < 2) {
    fprintf(stderr, "Error, invalid number of arguments");
    show_usage();
    exit(EXIT_FAILURE);
  }

  if (strcmp(argv[1], "--help") == 0) {
    show_usage();
    exit(EXIT_SUCCESS);
  }

  char* flags[argc - 3];
  p->name = argv[1];
  p->soft_limit = atoi(argv[2]);
  p->hard_limit = atoi(argv[3]);

  if (argc > 3) {
    for (int i = 3; i < argc - 3; i++) {
      flags[i - 3] = argv[i];
    }
  }

  p->flags = flags;
}
