
#include "ring_buffer.h"

void ring_buffer_init(ring_buffer_t *_buffer) {
  _buffer->_head = _buffer->_tail =  0;
}

void ring_buffer_enqueue(ring_buffer_t* _buffer, char _data) {
  if(ring_buffer_is_full(_buffer)) {
    // Is going to overwrite the oldest byte.
    // Increase _tail index.
    _buffer->_tail = ((_buffer->_tail + 1) & RING_BUFFER_MASK);
  }
  _buffer->_buffer[_buffer->_head] = _data;
  _buffer->_head = ((_buffer->_head + 1) & RING_BUFFER_MASK);
}

ring_buffer_bool_t ring_buffer_dequeue(ring_buffer_t* _buffer, char *_data) {
  if(ring_buffer_is_empty(_buffer)) {
    // No items.
    return 0;
  }

  *_data = _buffer->_buffer[_buffer->_tail];
  _buffer->_tail = ((_buffer->_tail + 1) & RING_BUFFER_MASK);
  return 1;
}

ring_buffer_bool_t ring_buffer_peek(ring_buffer_t *_buffer, char *_data, ring_buffer_size_t _index) {
  if (_index >= ring_buffer_items_num(_buffer)) {
    // No items.
    return 0;
  }

  ring_buffer_size_t _data_index = ((_buffer->_tail + _index) & RING_BUFFER_MASK);
  *_data = _buffer->_buffer[_data_index];
  return 1;
}

// extern ring_buffer_bool_t ring_buffer_is_empty(ring_buffer_t *_buffer);
//
// extern ring_buffer_bool_t ring_buffer_is_full(ring_buffer_t *_buffer);
//
// extern ring_buffer_size_t ring_buffer_items_num(ring_buffer_t *_buffer);

void ring_buffer_test(void) {
  // ring_buffer_t test;
  // ring_buffer_init(&test);
  //
  // char str[] = "Hello world.";
  //
  //
  // for(int i = 0; i < strlen(str); i++) {
  //   ring_buffer_enqueue(&test, );
  // }
}

