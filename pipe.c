#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
  int fds[2];
  pid_t pid;

  /* create a pipe */
  pipe(fds);

  /* fork a child process */
  pid = fork();
  if (pid == (pid_t)0)
  {
    /* This is the child process */
    /* Close the copy of the write end of the file descriptor*/
    close(fds[1]);
    dup2(fds[0], STDIN_FILENO);
    /* Replcae the child process with the "sort" program*/
    execlp("sort", "sort", (char*)0);
  }
  else
  {
    /* This is the parent process */
    FILE* stream;
    /* Close the copy of the read end of the file descriptor*/
    close(fds[0]);
    /* Convert the write file descriptor to a FILE objecg, and write to it */
    stream = fdopen(fds[1], "w");
    fprintf(stream,"That's fine.\n");
    fprintf(stream,"You know it.\n");
    fprintf(stream,"Good day.\n");
    fprintf(stream,"That's fine.\n");
    fprintf(stream,"Hello, child.\n");
    fflush(stream);
    close(fds[1]);
    waitpid(pid, NULL, 0);
  }

  return 0;
}
