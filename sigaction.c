#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

sig_atomic_t sigusr1_count = 0;
sig_atomic_t sigusr2_count = 0;

void handler1(int signal_number)
{
  ++sigusr1_count;
}

void handler2(int signal_number)
{
  ++sigusr2_count;
}

int main()
{
  struct sigaction sa1;
  struct sigaction sa2;
  int count = 0;

  printf("This is sigaction\n");
  memset(&sa1, 0, sizeof(sa1));
  memset(&sa2, 0, sizeof(sa2));
  sa1.sa_handler = &handler1;
  sa2.sa_handler = &handler2;
  sigaction(SIGUSR1, &sa1, NULL);
  sigaction(SIGUSR2, &sa2, NULL);

  while(count < 10)
  {
    sleep(1);
    count++;
  }

  printf("SIGUSR1 was raised %d times\n", sigusr1_count);
  printf("SIGUSR2 was raised %d times\n", sigusr2_count);

  return 0;
}
