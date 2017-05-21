
// NOT FINISHED!!!

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// TODO:
// Create a struct called CircularBuffer
// It should store:
// A pointer that points to the start of a dynamically allocated array of ints (could be null) (head pointer)
// A pointer that points to the end of the dynamically allocated array of ints (could be null) (tail pointer)
// A pointer that points to the currently readable buffer item (could be null) (read pointer))
// A pointer that points to the currently writable buffer item (could be null) (write pointer)
// The lenght of the buffer
typedef struct {
    int* head_pointer;
    int* tail_pointer;
    int* read_pointer;
    int* write_pointer;
    int size;
} CircularBuffer;

// TODO:
// Create a function that returns a dynamically allocated CircularBuffer (the buffer itself should be allocated as well, not just the array inside)
// It should take a normal array and it's length as argument, and it should fill all the buffer values from the array
CircularBuffer* create_buffer(int* _array, int _size) {

    int* buffer = calloc(_size, sizeof(*buffer));
    memcpy(buffer, _array, sizeof(int)*_size);

    CircularBuffer* to_return = malloc(sizeof(CircularBuffer));
    to_return->head_pointer = buffer;
    to_return->tail_pointer = &buffer[_size - 1];
    to_return->read_pointer = buffer;
    to_return->write_pointer = buffer;
    to_return->size = _size;

    return to_return;
}

// TODO:
// Create a function that resizes a CircularBuffer, it should take a CircularBuffer as a pointer and change that buffers length and reallocate it's array as well. (copying it's values)
void resize_buffer(CircularBuffer* _circ, int _size) {


}

// TODO:
// Create a function that takes a CircularBuffer and returns a new CircularBuffer that only contains the even numbers from the old CircularBuffer

// TODO:
// Try all the functions in the main function, plase deallocate any buffer and the array inside it after using them

int main() {

  return 0;
}
