#include "opts.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
  struct opts options;
  if (handle_args(argv, &options) != 0) {
    fprintf(stderr, "Error! Failed to perform integer conversion");
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
