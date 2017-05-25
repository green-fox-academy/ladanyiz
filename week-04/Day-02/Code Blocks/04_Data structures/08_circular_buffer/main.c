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
struct CircularBuffer {
    int *head;
    int *tail;
    int *read;
    int *write;
    int size;
};

// TODO:
// Create a function that returns a dynamically allocated CircularBuffer (the buffer itself should be allocated as well, not just the array inside)
// It should take a normal array and it's length as argument, and it should fill all the buffer values from the array
struct CircularBuffer *create_circ_buffer(int *source, int size)
{
    struct CircularBuffer *c_b = malloc(sizeof(struct CircularBuffer));
    int *buffer = calloc(size, sizeof(int));

    memcpy(buffer, source, size*sizeof(int));

    c_b->head = buffer; // or &buffer[0]
    c_b->tail = &buffer[size - 1];
    c_b->read = buffer;
    c_b->write = buffer;
    c_b->size = size;

    return c_b;
};

// TODO:
// Create a function that resizes a CircularBuffer, it should take a CircularBuffer as a pointer and change that buffer's length and reallocate its array as well. (copying its values)
void resize(struct CircularBuffer *source, int new_size)
{
    // test
    printf("head\t\tread\t\twrite\t\ttail\t\tsize\n");
    printf("%p\t%p\t%p\t%p\t%d\n\n", source->head, source->read, source->write, source->tail, source->size);

    int rd = source->read - source->head;
    int wt = source->write - source->head;
/*
    // test
    printf("rd: %d\n", rd);

    // test
    printf("wt: %d\n\n", wt);
*/
    source->head = realloc(source->head, new_size * sizeof(int));
    source->tail = &source->head[new_size - 1];
    source->read = source->head + rd;
    source->write = source->head + wt;
    source->size = new_size;
}

// TODO:
// Create a function that takes a CircularBuffer and returns a new CircularBuffer that only contains the even numbers from the old CircularBuffer
struct CircularBuffer *even_buffer(struct CircularBuffer *source)
{
    int count = 0;

    source->read = source->head;

    while (source->read <= source->tail) {
        if ((*source->read > 0) && (*source->read % 2 == 0)) {
            count++;
        }
        source->read++;
    }

    struct CircularBuffer *result2 = malloc(sizeof(struct CircularBuffer));
    result2->head = calloc(count, sizeof(int));
    result2->size = sizeof(result2->head) / sizeof(result2->head[0]);
    result2->tail = result2->head + (count - 1);
    result2->read = result2->head;
    result2->write = result2->head;

    source->read = source->head;

    while (source->read <= source->tail) {
        if (*source->read % 2 == 0) {
            *result2->write = *source->read;
            result2->write++;
        }
        source->read++;
    }

    return result2;
};


// TODO:
// Try all the functions in the main function, please deallocate any buffer and the array inside it after using them
int main()
{
    int array[] = {3, 6, 9, 12, 15, 18, 21, 24, 27, 30};

    struct CircularBuffer *test = create_circ_buffer(array, 10);
/*
    printf("head\t\tread\t\twrite\t\ttail\n");
    printf("%p\t%p\t%p\t%p\n\n", test->head, test->read, test->write, test->tail);
*/
    while (test->read <= test->tail) {
        printf("%d\t", *test->read);
        test->read++;
    }

    printf("\n\n");

    resize(test, 15);

    printf("head\t\tread\t\twrite\t\ttail\t\tsize\n%p\t%p\t%p\t%p\t%d\n\n", test->head, test->read, test->write, test->tail, test->size);

    for (int i = 0; i < 15; i++)
        test->head[10 + i] = 0;

    test->read = test->head;

    while (test->read <= test->tail) {
        printf("%d\t", *test->read);
        test->read++;
    }

    printf("\n");

    struct CircularBuffer *evens = even_buffer(test);

    while (evens->read <= evens->tail) {
        printf("%d\t", *evens->read);
        evens->read++;
    }

    printf("\n\n");

    free(evens->head);
    free(evens);

    free(test->head);
    free(test);

    return 0;
}
