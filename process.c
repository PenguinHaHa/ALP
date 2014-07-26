//
// By Penguin, 2014.7
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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

  child_pid = fork();
  if (child_pid == 0)
  {
    printf("This is child process, pid %d\n", child_pid);
    execvp("ls", arg_list);
    //execvp only return if error occur
    fprintf(stderr, "run ls failed\n");
    abort();
  }
  else
  {
    printf("This is parent process, pid %d\n", child_pid);
  }
}

