//
// By Penguin, 2014.7
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sched.h>

char* arg_list[] = {
  "ls",
  "-l",
  NULL
};
 
void process(void)
{
  pid_t child_pid;

  printf("Current pid %d\n", getpid());
  printf("Parent pid %d\n", getppid());

  printf("Current process's prority %d\n", sched_getscheduler(0));

  child_pid = fork();
  if (child_pid == 0)
  {
    printf("CHILD, Current pid %d\n", getpid());
    printf("CHILD, Current process's prority %d\n", sched_getscheduler(0));
    execvp("ls", arg_list);
    //execvp only return if error occur
    fprintf(stderr, "run ls failed\n");
    abort();
  }
  else
  {
    printf("This is parent process, return child pid %d\n", child_pid);
  }
}

