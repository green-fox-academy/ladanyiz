#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED
#include <stdint.h>

typedef struct {
    char name[30];
    char ip[20];
    uint16_t port;
} user_t;

user_t user_list[50];
uint8_t index;  // Index of array element to write

void handle_error(const char *error_string);

void wsa_init();

void start_screen();

#endif // FUNCTIONS_H_INCLUDED