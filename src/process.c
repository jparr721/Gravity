#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

#include "process.h"

int find_process_by_pid(pid_t pid) {
  return (kill(pid, 0) == 0) ? pid : -1;
}

int find_process_by_name(char* name) {
  // The target process
  pid_t pid = -1;

  char line[20];
  char command[40];
  sprintf(command, "pidof %s", name);
  FILE *program = popen(command, "r");

  fgets(line, 20, program);
  pid = strtoul(line, NULL, 10);

  pclose(program);

  return pid;
}

struct process* init_process(char* name) {
  // Declare a new process in stack memory
  struct process* proc = (struct process*) malloc(sizeof(struct process));
  proc->name = name;

  return proc;
}

int start_process(struct process* proc, char** argv) {
  pid_t pid = fork();
  if (pid == 0) {
    // Exec the program with any args
    execv(proc->name, argv);
    // execv error code
    return 127;
  } else {
    waitpid(pid, 0, 0);
  }
  proc->pid = pid;
  update_process(proc);
  return 0;
}

void update_process(struct process* proc) {
  struct timeval now;
  gettimeofday(&now, NULL);

  proc->last_update = now;
}
