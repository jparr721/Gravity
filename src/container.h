#ifndef CONTAINER_H
#define CONTAINER_H
#define _GNU_SOURCE

#include "opts.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sched.h>
#include <sys/wait.h>

int intialize_container(struct opts args) {
  return EXIT_SUCCESS;
}

static void subprocess(void* args) {
  struct opts options = (struct opts)args;
}

#endif
