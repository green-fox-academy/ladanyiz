#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

typedef struct {
    int8_t temp_array[1000];
    uint8_t array_size;
} list_type;

void init_list(list_type *t_list);

void start_screen();

int8_t file_ok(const char *filename, const char *op);

char *timestamp();

int8_t write_file(char *filename);

int8_t read_file(const char *filename, const char *from, const char *to, list_type *t_list);

#endif // FUNCTIONS_H_INCLUDED
