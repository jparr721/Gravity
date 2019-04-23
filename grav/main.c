#include "cli.h"
#include "process.h"
#include <stdio.h>

int main(int argc, char** argv) {
  struct program *p, rp;
  rp.name = "";
  rp.soft_limit = 10;
  rp.hard_limit = 11;
  p = &rp;

  parse_args(argc, argv, p);

  printf("Running program: %s", p->name);
  return start_process(p->soft_limit, p->hard_limit, p->name, p->flags);
}
