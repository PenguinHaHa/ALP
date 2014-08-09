//
// By Penguin, 2014.7
//

#include <pthread.h>
#include <stdio.h>

#include "testcase.h"

int num;

void *thread_func(void *threadnum)
{
  int i;
  pthread_t tid;

  for(i = 0; i < 5; i++)
  {
    tid = pthread_self();
    printf("This is thread %d, thread id %lu\n", *(int *)threadnum, tid);
    sleep(1);
  }
}

void thread(void)
{
  pthread_t thread1_id;
  pthread_t thread2_id;

  num = 1;
  pthread_create(&thread1_id, NULL, &thread_func, &num);

  sleep(3);

  num = 2;
  pthread_create(&thread1_id, NULL, &thread_func, &num);

  pthread_join(thread1_id, NULL);
  pthread_join(thread2_id, NULL);
}
