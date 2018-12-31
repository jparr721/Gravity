#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <signal.h>
#include <sys/time.h>

struct process {
  pid_t pid;
  char* name;
  struct timeval last_update;
};

// Process locators
int find_process_by_pid(pid_t pid);
int find_process_by_name(char* name);

// Process managers
struct process* init_process(char* name);
int start_process(struct process* proc, char** argv);
void update_process(struct process* proc);
int destroy_process(struct process* proc);
int stop_process(struct process* proc);

#endif
