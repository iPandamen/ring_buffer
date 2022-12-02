#include <stdio.h>
#include <string.h>

#include "ring_buffer.h"

int main(int argc, char *argv[])
{
  ring_buffer_t test;
  if(ring_buffer_init(&test, RING_BUFFER_MODE_NORMAL, 512) == 0) {
    exit(-1);
  }

  ring_buffer_set_mode(&test, RING_BUFFER_MODE_COVER);

  char str[] = "Hello world.";

  ring_buffer_printf(&test);

  for(int j = 0; j < 12; j++) {
    ring_buffer_enqueue_array(&test, str, strlen(str));
  }
  ring_buffer_printf(&test);

  char buf[512] = {0};
  ring_buffer_dequeue_array(&test, buf, 512);
  printf(" -------- buf: %s\n", buf);

  ring_buffer_printf(&test);

  ring_buffer_exit(&test);
  return 0;
}





