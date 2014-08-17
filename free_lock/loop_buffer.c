//
// By penguin, 2014.8.17
// This is a free lock algorithms used for one writer & one reader situation
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _LOOP_BUFFER {
  unsigned int in;
  unsigned int out;
  unsigned int size;
  void         *buffer;
} LOOP_BUFFER;

void print_loop_buffer(LOOP_BUFFER *loop_buffer);
void init_loop_buffer(LOOP_BUFFER *loop_buffer,unsigned int size);
void free_loop_buffer(LOOP_BUFFER *loop_buffer);
unsigned int write_loop_buffer(LOOP_BUFFER *loop_buffer, void *buffer, unsigned int size);
unsigned int read_loop_buffer(LOOP_BUFFER *loop_buffer, void *buffer, unsigned int size);
void* read_func(void *arg);

int main(int argc, char *argv[])
{
  LOOP_BUFFER loop_buffer;
  unsigned int buffer_size;

  // init loop buffer
  buffer_size = 10;
  init_loop_buffer(&loop_buffer, buffer_size);

  pthread_t read_thread;
  pthread_create(&read_thread, NULL, &read_func, &loop_buffer);

  // write to loop buffer
  char context = 0;
  while(context < 30)
  {
    unsigned int write_len;
    write_len = write_loop_buffer(&loop_buffer, &context, sizeof(char));
    while(write_len == 0)
    {
      write_len = write_loop_buffer(&loop_buffer, &context, sizeof(char));
    }
    printf("write_len %d , context %d| ", write_len, context);
    print_loop_buffer(&loop_buffer);
    context++;
    sleep(1);
  }

  pthread_cancel(read_thread);
  pthread_join(read_thread, NULL);

  free_loop_buffer(&loop_buffer);
}

void* read_func(void *arg)
{
  sleep(1);
  LOOP_BUFFER *ploop_buffer = (LOOP_BUFFER *)arg;
  char context = 0;
  while(1)
  {
    unsigned int read_len;
    read_len = read_loop_buffer(ploop_buffer, &context, sizeof(char));
    printf("read_len %d , context %d| ", read_len, context);
    print_loop_buffer(ploop_buffer);
    sleep(2);
  }
}

void print_loop_buffer(LOOP_BUFFER *loop_buffer)
{
  int i;
  char *p = loop_buffer->buffer;
  
  printf("size %d, in %d, out %d : ", loop_buffer->size, loop_buffer->in, loop_buffer->out);
  for(i = 0; i < loop_buffer->size; i++)
  {
    printf("%d ", p[i]);
  }
  printf("\n");
}

void init_loop_buffer(LOOP_BUFFER *loop_buffer,unsigned int size)
{
  loop_buffer->size = size;
  loop_buffer->buffer = malloc(sizeof(char) * size);
  memset(loop_buffer->buffer, 0, size);
  loop_buffer->in = 0;
  loop_buffer->out = 0;
}

void free_loop_buffer(LOOP_BUFFER *loop_buffer)
{
  free(loop_buffer->buffer);
}

unsigned int write_loop_buffer(LOOP_BUFFER *loop_buffer, void *buffer, unsigned int size)
{
  unsigned int unused_buffer_size;
  unsigned int write_len;
  unsigned int remain_len;

  unused_buffer_size = loop_buffer->size - (loop_buffer->in - loop_buffer->out);
  write_len = (size < unused_buffer_size) ? size : unused_buffer_size;

  remain_len = loop_buffer->size - loop_buffer->in % loop_buffer->size;

  // write to loop buffer
  if(remain_len > write_len)
  {
    memcpy((char *)loop_buffer->buffer + loop_buffer->in % loop_buffer->size, buffer, write_len);
  }
  else
  {
    memcpy((char *)loop_buffer->buffer + loop_buffer->in % loop_buffer->size, buffer, remain_len);
    memcpy(loop_buffer->buffer, (char *)buffer + remain_len, write_len - remain_len);
  }

  // update loop buffer's write pointer
  loop_buffer->in += write_len;

  return write_len;
}

unsigned int read_loop_buffer(LOOP_BUFFER *loop_buffer, void *buffer, unsigned int size)
{
  unsigned int used_buffer_size;
  unsigned int read_len;
  unsigned int remain_len;

  used_buffer_size = loop_buffer->in - loop_buffer->out;
  read_len = (size < used_buffer_size) ? size : used_buffer_size;

  remain_len = loop_buffer->size - loop_buffer->out % loop_buffer->size;

  // Read from loop buffer
  if (remain_len > read_len)
  {
    memcpy(buffer, (char *)loop_buffer->buffer + loop_buffer->out % loop_buffer->size, read_len);
  }
  else{
    memcpy(buffer, (char *)loop_buffer->buffer + loop_buffer->out % loop_buffer->size, remain_len);
    memcpy((char *)buffer + remain_len, loop_buffer->buffer, read_len - remain_len);
  }

  // update loop buffer's read pointer
  loop_buffer->out += read_len;

  return read_len;
}
