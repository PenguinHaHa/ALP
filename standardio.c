//
// By Penguin, 2014.7
//

#include <stdio.h>
#include <unistd.h>

#include "testcase.h"

void stdintest(void)
{
  printf("This is stdin test\n");
}

void stderrtest(void)
{
  int count;

  printf("This is stderr test\n");

  count = 8;
  while(count)
  {
    fprintf(stderr, ".");
    sleep(1);
    count--;
  }
  fprintf(stderr, "\n");

}

void stdouttest(void)
{
  int count;

  printf("This is stdout test\n");

  count = 8;
  printf("fprintf, stdout:");
  while(count)
  {
    fprintf(stdout, ".");
    count--;
    sleep(1);
  }
  printf("\n");

  count = 8;
  printf("printf:");
  while(count)
  {
    printf(".");
    count--;
    sleep(1);
  }
  printf("\n");
}

void standardio(void)
{
  // stdin
  stdintest();

  // stdout
  stdouttest();
  
  // stderr
  stderrtest();
}
