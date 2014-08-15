// By Penguin, 2014.8
// This is a templete for sychronization machanism using in linux
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <getopt.h>

const char* const short_options = "hlsc";

const struct option long_options[] = {
  {"help", 0, NULL, 'h'},
  {"lock", 0, NULL, 'l'},
  {"semaphore", 0, NULL, 's'},
  {"condition", 0, NULL, 'c'},
  {NULL, 0, NULL , 0}
};

void semaphore_case(void);
void* sem_thread_fun(void* arg);
void lock_case(void);
void* lock_thread_fun(void *arg);
void condition_case(void);

void print_usage(void)
{
  printf("Sychronization machanism for race condition\n");
  printf(" -h  -help       Display usage information\n");
  printf(" -l  -lock       Mutex/spinlock/rwlock\n");
  printf(" -s  -semaphore  thread/process semaphore\n");
  printf(" -c  -condition  condition variables\n");
}

int main(int argc, char* argv[])
{
  int option;

  do {
    option = getopt_long(argc, argv, short_options, long_options, NULL);
    switch(option)
    {
      case 'h':
        print_usage();
        break;

      case 'l':
        lock_case();
        break;

      case 's':
        semaphore_case();
        break;

      case 'c':
        condition_case();
        break;

      case -1:
        break;

      default:
        print_usage();
        break;
    }
  } while (option != -1);
}

void semaphore_case(void)
{
  int ret;
  sem_t sem;

  printf("This is semaphore case\n");

  //int sem_init(sem_t *sem, int pshared, unsigned int value)
  // pshared: 0, shared in threads under the same process
  //          1, shared between processes
  // value: the initial value of this semaphore
  ret = sem_init(&sem, 0, 0);
  if(ret)
  {
    printf("Semaphore init failed\n");
    exit(EXIT_FAILURE);
  }

  pthread_t sem_thread;
  ret = pthread_create(&sem_thread, NULL, sem_thread_fun, &sem);
  if(ret)
  {
    printf("create semaphore test thread failed\n");
    exit(EXIT_FAILURE);
  }

  int count = 5;
  while(count > 0)
  {
    sem_post(&sem);
    sleep(3);
    count--;
  }

  ret = pthread_cancel(sem_thread);
  if(ret)
  {
    printf("cancel sem thread failed\n");
    exit(EXIT_FAILURE);
  }

  pthread_join(sem_thread, NULL);

  sem_destroy(&sem);
}

void* sem_thread_fun(void* arg)
{
  sem_t *sem = (sem_t*)arg;
  while(1)
  {
    sem_wait(sem);
    printf("This is sem_thread\n");
  }
}

void lock_case(void)
{
  int ret;
  pthread_t lock_thread;
  printf("This is lock case\n");
  
  //pthread_mutex_t mutex = PTHREAD_MUTEX_INITIZLIZER;
  pthread_mutex_t mutex;

  pthread_mutex_init(&mutex, NULL);

  ret = pthread_create(&lock_thread, NULL, lock_thread_fun, &mutex);
  if(ret)
  {
    printf("create lock thread failed\n");
    exit(EXIT_FAILURE);
  }

  sleep(1);
  int count = 5;
  while(count > 0)
  {
    pthread_mutex_lock(&mutex);
    sleep(3);
    pthread_mutex_unlock(&mutex);
    printf("unlock in main thread\n");
    count--;
  }

  ret = pthread_cancel(lock_thread);
  if(ret)
  {
    printf("cancel sem thread failed\n");
    exit(EXIT_FAILURE);
  }

  pthread_join(lock_thread, NULL);
}

void* lock_thread_fun(void *arg)
{
  pthread_mutex_t *mutex = (pthread_mutex_t *)arg;

  while(1)
  {
    pthread_mutex_lock(mutex);
    printf("This is lock_thread_fun\n");
    sleep(1);
    pthread_mutex_unlock(mutex);
    printf("unlocked in lock thread\n");
  }
}

void condition_case(void)
{
  printf("This is condition case\n");
}
