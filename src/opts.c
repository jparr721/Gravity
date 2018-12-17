#include "opts.h"

#include <stdio.h>
#include <stdlib.h>

int handle_args(char** argv, struct opts* arg_buffer) {
  char* catch = NULL;
  arg_buffer->executable = argv[1];
  arg_buffer->memory = strtol(argv[2], &catch, 10);
  arg_buffer->processors = strtol(argv[3], &catch, 10);
  if (catch != NULL) {
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
