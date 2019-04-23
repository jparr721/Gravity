#define _GNU_SOURCE
#define _FILE_OFFSET_BITS 64
#include "process.h"
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/wait.h>

int kill_process_by_pid(pid_t pid) {
  return kill(pid, 0) == 0 ? pid : -1;
}

int find_process_by_name(char* name) {
  pid_t pid = -1;

  char line[64];
  char command[40];
  sprintf(command, "pidof %s", name);
  FILE* pid_get = popen(command, "r");

  fgets(line, sizeof(line), pid_get);
  pid = strtoul(line, NULL, 10);

  pclose(pid_get);

  return pid;
}

int start_process(int soft, int max, char* process, char** flags) {
  struct rlimit old, new;
  struct rlimit *newp = NULL;
  pid_t pid;
  int status;
  long time_s;
  long time_ms;
  long last_context_switch;
  struct rusage ru;

  pid = fork();

  new.rlim_cur = soft;
  new.rlim_max = max;
  newp = &new;

  if (pid < 0) {
    perror("fork");
    exit(EXIT_FAILURE);
  } else if (!pid) {
    /* Retreive and display previous limit */
    if (prlimit(pid, RLIMIT_CPU, newp, &old) == -1) {
      perror("prlimit");
    }

    printf("Previously applied limit: soft=%lld, hard=%lld\n",
        (long long)old.rlim_cur, (long long)old.rlim_max);

    /* Retrevie and display updated limits */
    if (prlimit(pid, RLIMIT_CPU, NULL, &old) == -1) {
      perror("prlimit");
    }

    printf("New limits: soft=%lld, hard=%lld\n",
        (long long) old.rlim_cur, (long long) old.rlim_max);

    if (execvp(process, flags) < 0) {
      perror("execvp");
      exit(EXIT_FAILURE);
    } else {
      exit(EXIT_SUCCESS);
    }
  } else {
    wait(&status);

    if (getrusage(RUSAGE_CHILDREN, &ru) < 0) {
      perror("rusage");
    } else {
      time_s = ru.ru_utime.tv_sec;
      time_ms = ru.ru_utime.tv_usec;
      last_context_switch = ru.ru_nivcsw;

      printf("Total cpu time: %lds %ldms\n", time_s, time_ms);
      printf("Context switches: %ld\n", last_context_switch);
    }
  }

  return EXIT_SUCCESS;
}
