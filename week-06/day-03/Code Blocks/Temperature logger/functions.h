#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

typedef struct {
    int8_t temp_array[1000];
    uint8_t array_size;
} list_type;

list_type temp_list;

time_t rawtime;
struct tm *timeinfo;
char time_buffer[30];

char file_name[20];
char port_name[5];
uint8_t index;


void start_screen();

void list_ports();

int8_t set_port();

int8_t file_ok(const char *filename, const char *op);

void file_to_write();

int8_t open_port();

char *timestamp();

int8_t write_file(char *filename);

void close_port();

void file_to_read();

int8_t read_file(const char *filename, const char *from, const char *to, list_type *t_list);

void calc_avg();

#endif // FUNCTIONS_H_INCLUDED
