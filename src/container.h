#ifndef CONTAINER_H
#define CONTAINER_H
#define _GNU_SOURCE

#include "opts.h"

int intialize_container(struct opts args);
int get_pid_max();

static int subprocess(void* args);

#endif
