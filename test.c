#include <stdio.h>
#include <string.h>

#include "ring_buffer.h"


int main(int argc, char *argv[])
{
  ring_buffer_t test;
  if(ring_buffer_init(&test, RING_BUFFER_MODE_NORMAL, 128) == 0) {
    exit(-1);
  }

  ring_buffer_set_mode(&test, RING_BUFFER_MODE_COVER);

  char str[] = "Hello world.";

  printf("_head: %ld, _tail: %ld\n", test._head, test._tail);
  for(int j = 0; j < 12; j++) {
    for(int i = 0; i < strlen(str); i++) {
      ring_buffer_enqueue(&test, str[i]);
    }
  }

  printf("%s\n", test._buffer);

  if(ring_buffer_is_empty(&test)) {
    printf(" -------- ring_buffer is empty!\n");
  } else {
    printf(" -------- ring_buffer is not empty!\n");
  }

  if(ring_buffer_is_full(&test)) {
    printf(" -------- ring_buffer is full!\n");
  } else {
    printf(" -------- ring_buffer is not full!\n");
  }

  printf(" -------- ring_buffer nums: %ld!\n", ring_buffer_nums(&test));
  printf(" -------- _head: %ld, _tail: %ld\n", test._head, test._tail);

  char data;
  while(ring_buffer_dequeue(&test, &data)) {
    putchar(data);
  }

  printf("\n");
  if(ring_buffer_is_empty(&test)) {
    printf(" -------- ring_buffer is empty!\n");
  } else {
    printf(" -------- ring_buffer is not empty!\n");
  }

  if(ring_buffer_is_full(&test)) {
    printf(" -------- ring_buffer is full!\n");
  } else {
    printf(" -------- ring_buffer is not full!\n");
  }

  printf(" -------- ring_buffer nums: %ld!\n", ring_buffer_nums(&test));
  printf(" -------- _head: %ld, _tail: %ld\n", test._head, test._tail);

  ring_buffer_exit(&test);
  return 0;
}





