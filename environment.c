//
// By Penguin, 2014.7
//

#include <stdio.h>

extern char** environ;

void environment(void)
{
  char** var;
  for (var = environ; *var != NULL; ++var)
  {
    printf("%s\n", *var);
  }
}
