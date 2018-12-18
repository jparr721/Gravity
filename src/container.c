#include "container.h"

#include <errno.h>
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int initialize_container(struct opts args) {
  int clone_flag = SIGCHLD;
  int stack_size = args.memory;
  static char* child_stack;
  child_stack = malloc(stack_size * sizeof(int));

  pid_t child_pid = clone(subprocess, child_stack + stack_size, clone_flag, &args);
  if (child_pid < 0) {
    fprintf(stderr, "Failed to clone process, error: %s", strerror(errno));
    return -1;
  }

  // Wait for the child process to finish
  if (waitpid(child_pid, NULL, 0) == -1) {
    fprintf(stderr, "Failed to wait on pid %d\n", child_pid);
    return -1;
  }

  return EXIT_SUCCESS;
}

int get_pid_max() {
#ifdef __linux__
  // Read proc/sys/kernel/pid_max
  static char buffer[1024];
  FILE *fd = fopen("/proc/sys/kernel/pid_max", "r");
  if (fd == NULL) return -1;
  if (fgets(buffer, sizeof(buffer), fd) == NULL) {
    fclose(fd);
    return -1;
  }

  fclose(fd);
  return atoi(buffer);
#elif defined __FreeBSD__
  return 99998;
#elif defined __APPLE__
  return 99998;
#endif
}

static int subprocess(void* args) {
  struct opts *options = (struct opts*)args;
  if (execvp(options->executable, args) == -1) {
    fprintf(stderr, "Failed to mount executable");
    return -1;
  }

  return EXIT_SUCCESS;
}
