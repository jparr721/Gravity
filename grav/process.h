#ifndef PROCESS_H_
#define PROCESS_H_

#include <sys/types.h>

int kill_process_by_pid(pid_t pid);
int find_process_by_name(char* name);
int start_process(int soft, int max, char* process, char** flags);

#endif // PROCESS_H_
