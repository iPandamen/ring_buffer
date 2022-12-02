
#include "ring_buffer.h"

ring_buffer_bool_t ring_buffer_init(ring_buffer_t *_buffer, ring_buffer_mode_t _mode, ring_buffer_size_t _size) {

  if(_buffer == NULL) { 
    printf("-------- %s, Error: _buffer is nullptr!\n", __FUNCTION__);
    return 0;
  }

  if(_size & (_size - 1)) {
    printf(" -------- %s, Error: _size must be a power of two!\n", __FUNCTION__);
    return 0;
  }

  _buffer->_size = _size;
  _buffer->_mask = _buffer->_size - 1;

  _buffer->_buffer = malloc(_buffer->_size);
  if(_buffer->_buffer == NULL) {
    printf(" -------- %s, Error: malloc failed!\n", __FUNCTION__);
    return 0;
  }
  _buffer->_mode = _mode;
  _buffer->_head = _buffer->_tail =  0;
  return 1;
}

ring_buffer_bool_t ring_buffer_exit(ring_buffer_t *_buffer) {

  if(_buffer == NULL) {
    return 0;
  }

  if(_buffer->_buffer) {
    free(_buffer->_buffer);
  }

  _buffer->_size = _buffer->_mask = 0;
  _buffer->_mode = RING_BUFFER_MODE_NORMAL;
  _buffer->_head = _buffer->_tail = 0;

  return 1;
}


/**
 * @brief change the mode of ring_buffer
 *
 */
ring_buffer_bool_t ring_buffer_set_mode(ring_buffer_t* _buffer,  ring_buffer_mode_t _mode) { 

  if(_buffer == NULL) {
    return 0;
  }

  _buffer->_mode = _mode;
  return 1;
}

ring_buffer_bool_t ring_buffer_enqueue(ring_buffer_t* _buffer, char _data) {

  if(ring_buffer_is_full(_buffer)) {

    if(_buffer->_mode == RING_BUFFER_MODE_COVER) {
      // Is going to overwrite the oldest byte.
      // Increase _tail index.
      _buffer->_tail = ((_buffer->_tail + 1) & _buffer->_mask);
    } else {
      return 0; 
    }
  } 

  _buffer->_buffer[_buffer->_head] = _data;
  _buffer->_head = ((_buffer->_head + 1) & _buffer->_mask);
  return 1;
}

ring_buffer_bool_t ring_buffer_enqueue_array(ring_buffer_t *_buffer, char *_data, ring_buffer_size_t _len) {

  if(_buffer == NULL) {
    return 0;
  }

  ring_buffer_size_t i;
  for(i = 0; i <_len; i++) {
    ring_buffer_enqueue(_buffer, _data[i]);
  }
  return 1;
}


ring_buffer_bool_t ring_buffer_dequeue(ring_buffer_t* _buffer, char *_data) {

  if(ring_buffer_is_empty(_buffer)) {
    // No items.
    return 0;
  }

  *_data = _buffer->_buffer[_buffer->_tail];
  _buffer->_tail = ((_buffer->_tail + 1) & _buffer->_mask);
  return 1;
}

ring_buffer_bool_t ring_buffer_dequeue_array(ring_buffer_t* _buffer, char *_data, ring_buffer_size_t _len) {
  if(ring_buffer_is_empty(_buffer)){
    // No items.
    return 0;
  }

  char *data_ptr = _data;
  ring_buffer_size_t cnt = 0;
  while((cnt < _len) && ring_buffer_dequeue(_buffer, data_ptr)) {
    cnt ++;
    data_ptr++;
  }
  return cnt;
}

ring_buffer_bool_t ring_buffer_peek(ring_buffer_t *_buffer, char *_data, ring_buffer_size_t _index) {

  if (_index >= ring_buffer_nums(_buffer)) {
    // No items.
    return 0;
  }

  ring_buffer_size_t _data_index = ((_buffer->_tail + _index) & _buffer->_mask);
  *_data = _buffer->_buffer[_data_index];
  return 1;
}

ring_buffer_bool_t ring_buffer_printf(ring_buffer_t *_buffer) {
  if(_buffer == NULL) {
    return 0;
  }

  ring_buffer_size_t i = 0;
  ring_buffer_size_t length = ring_buffer_nums(_buffer);
  if(ring_buffer_is_full(_buffer)) {
    printf(" -------- %s, _buffer is full!\n", __FUNCTION__);
  } else if(ring_buffer_is_empty(_buffer)){
    printf(" -------- %s, _buffer is empty!\n", __FUNCTION__);
  }
  printf(" -------- %s, head: %ld, tail: %ld, legth: %ld:\n", __FUNCTION__, _buffer->_head, _buffer->_tail, length);
  for(i = 0; i < length; i++) {
    char _tmp = '\0';
    ring_buffer_peek(_buffer, &_tmp, i);
    printf("%c", _tmp);
  }
  printf("\n"); 

  return 1;
}




