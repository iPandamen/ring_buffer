#include <stdio.h>
#include <string.h>

#include "ring_buffer.h"

int main(int argc, char *argv[])
{
  ring_buffer_t test;
  ring_buffer_init(&test);

  char str[] = "Hello world.";

  for(int j = 0; j < 12; j++) {
    for(int i = 0; i < strlen(str); i++) {
      ring_buffer_enqueue(&test, str[i]);
    }
  }

  printf("%s\n", test._buffer);

  printf("empty: %d\n", ring_buffer_is_empty(&test));
  printf("full: %d\n", ring_buffer_is_full(&test));
  printf("num: %d\n", ring_buffer_items_num(&test));

  char data;
  while(ring_buffer_dequeue(&test, &data)) {
    putchar(data);
  }

  printf("\n");
  printf("empty: %d\n", ring_buffer_is_empty(&test));
  printf("full: %d\n", ring_buffer_is_full(&test));
  printf("num: %d\n", ring_buffer_items_num(&test));


  return 0;
}





