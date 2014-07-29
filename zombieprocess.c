#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
  pid_t child_pid;

  child_pid = fork();
  if(child_pid == 0)
  {
    printf("This is child process\n");
    exit(0);
  }
  else{
    printf("This is the parent process\n");
    sleep(30);
    printf("parent end\n");
  }

  return 0;
}
