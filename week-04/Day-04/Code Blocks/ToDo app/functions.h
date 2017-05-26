#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

#define MAX_COMMAND_LENGTH 35
#define MAX_TODO_LENGTH 50

typedef struct {
    char todo[MAX_TODO_LENGTH];
    int checked;
    int priority;
} task_t;

typedef struct {
    task_t *array;
    int size;
} list_t;

void clrscr();

void start_screen();

void init_list(list_t *list);

void add_task(list_t *list, char *todo, int chk, int pri);

int list_tasks(list_t *list);

int write_list(list_t *list, char *path);

int read_list(list_t *list, char *path);

void empty_list(list_t *list);

int remove_task(list_t *list, int index);

int check_task(list_t *list, int index);

#endif // FUNCTIONS_H_INCLUDED
