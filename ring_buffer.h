#ifndef __RING_BUFFER_H__
#define __RING_BUFFER_H__

#include <stdio.h>
#include <stdint.h>


/**
 * @brief  The sizeof a ring buffer.
 *
 */

#define RING_BUFFER_SIZE 128

#if (RING_BUFFER_SIZE & (RING_BUFFER_SIZE - 1)) != 0
#error "RING_BUFFERSIZE must be a power of two"
#endif 


/**
 * @brief The type wich is used to hold the size and 
 *        the indicies of the buffer. 
 *        Must be able to fit \c RING_BUFFER_SIZE.
 */
typedef uint32_t ring_buffer_size_t;


typedef uint32_t ring_buffer_bool_t;

/**
 * @brief Used as a modulo operator as <tt> a % b = (a & (b - 1)) </tt>
 *        where a is a positive index in the buffer and 
 *        b is the (power of two) size of the buffer.
 *
 */
#define RING_BUFFER_MASK (RING_BUFFER_SIZE - 1)

/**
 *
 */
typedef struct __ring_buffer ring_buffer_t;

/**
 *
 */
struct __ring_buffer {
  uint8_t _buffer[RING_BUFFER_SIZE];
  ring_buffer_size_t _head, _tail;
};

extern void ring_buffer_init(ring_buffer_t *_buffer);

extern void ring_buffer_enqueue(ring_buffer_t* _buffer, char _data);

extern ring_buffer_bool_t ring_buffer_dequeue(ring_buffer_t* _buffer, char *_data);

extern ring_buffer_bool_t ring_buffer_peek(ring_buffer_t *_buffer, char *_data, ring_buffer_size_t _index);


inline ring_buffer_bool_t ring_buffer_is_empty(ring_buffer_t *_buffer) {
  return (_buffer->_head == _buffer->_tail);
}

inline ring_buffer_bool_t ring_buffer_is_full(ring_buffer_t *_buffer) {
  return ((_buffer->_head - _buffer->_tail) & RING_BUFFER_MASK) == RING_BUFFER_MASK;
}

inline ring_buffer_size_t ring_buffer_items_num(ring_buffer_t *_buffer) {
  return ((_buffer->_head - _buffer->_tail) & RING_BUFFER_MASK);
}


#endif /* __RING_BUFFER_H__ */

