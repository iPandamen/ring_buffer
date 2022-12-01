#ifndef __RING_BUFFER_H__
#define __RING_BUFFER_H__

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>


/**
 * @brief The type wich is used to hold the size and 
 *        the indicies of the buffer. 
 */
typedef size_t ring_buffer_size_t;


enum {
  RING_BUFFER_MODE_NORMAL,
  RING_BUFFER_MODE_COVER,
  RING_BUFFER_MODE_NUM,
};

typedef uint32_t ring_buffer_mode_t;

typedef uint32_t ring_buffer_bool_t;

struct __ring_buffer;

/**
 *
 */
typedef struct __ring_buffer {
  char *_buffer;

  // _size must be a power of two.
  ring_buffer_size_t _size;
  ring_buffer_size_t _mask;
  ring_buffer_size_t _mode;

  ring_buffer_size_t _head, _tail;
} ring_buffer_t;

extern ring_buffer_bool_t ring_buffer_init(ring_buffer_t *_buffer, ring_buffer_mode_t _mode, ring_buffer_size_t _size);
extern ring_buffer_bool_t ring_buffer_exit(ring_buffer_t *_buffer);

ring_buffer_bool_t ring_buffer_set_mode(ring_buffer_t* _buffer,  ring_buffer_mode_t _mode);

extern ring_buffer_bool_t ring_buffer_enqueue(ring_buffer_t* _buffer, char _data);

extern ring_buffer_bool_t ring_buffer_dequeue(ring_buffer_t* _buffer, char *_data);

extern ring_buffer_bool_t ring_buffer_peek(ring_buffer_t *_buffer, char *_data, ring_buffer_size_t _index);


inline ring_buffer_bool_t ring_buffer_is_empty(ring_buffer_t *_buffer) {
  return (_buffer->_head == _buffer->_tail);
}

inline ring_buffer_bool_t ring_buffer_is_full(ring_buffer_t *_buffer) {
  return ((_buffer->_head - _buffer->_tail) & _buffer->_mask) == _buffer->_mask;
}

inline ring_buffer_size_t ring_buffer_nums(ring_buffer_t *_buffer) {
  return ((_buffer->_head - _buffer->_tail) & _buffer->_mask);
}


#endif /* __RING_BUFFER_H__ */

