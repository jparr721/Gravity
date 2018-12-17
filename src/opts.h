#ifndef OPTS_H
#define OPTS_H

struct opts {
  char* executable;
  int memory;
  int processors;
};

int handle_args(char** argv, struct opts* arg_buffer);
#endif
