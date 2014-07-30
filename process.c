//
// By Penguin, 2014.7
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sched.h>
#include <signal.h>

#include "testcase.h"

char* arg_list[] = {
  "./sigaction",
  NULL
};

sig_atomic_t child_status;
sig_atomic_t handler_in = 0;

void child_handler(int signal_number)
{
  int status;
  handler_in = 1;
  wait(&status);
  child_status = status;
}

void process(void)
{
  pid_t child_pid;
  struct sigaction sa;

  sa.sa_handler = child_handler;
  sigaction(SIGCHLD, &sa, NULL);

  printf("Current pid %d\n", getpid());
  printf("Parent pid %d\n", getppid());

  printf("Current process's prority %d\n", sched_getscheduler(0));

  child_pid = fork();
  if (child_pid == 0)
  {
    printf("CHILD, Current pid %d\n", getpid());
    printf("CHILD, Current process's prority %d\n", sched_getscheduler(0));
    execv("./sigaction", arg_list);
    //execvp only return if error occur
    printf("run sigaction failed\n");
    fprintf(stderr, "run sigaction failed\n");
    abort();
  }
  else
  {
    printf("This is parent process, return child pid %d\n", child_pid);
    sleep(1);
    kill(child_pid, SIGUSR1);
    kill(child_pid, SIGUSR2);
    sleep(1);
    kill(child_pid, SIGUSR2);

    sleep(18);
    printf("child status %d, handler_in %d\n", child_status, handler_in);
  }
}

