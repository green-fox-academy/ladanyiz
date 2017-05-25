#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

int main()
{
    list_t my_list;
    init_list(&my_list);

    start_screen();

    char command[MAX_COMMAND_LENGTH];

    while (1) {
        gets(command);
        char com_to_parse[MAX_COMMAND_LENGTH];
        strcpy(com_to_parse, command);

        char *ptr;
        ptr = strtok(com_to_parse, "\"");

        if(strstr(ptr, "x")) {              // exit
            break;

        } else if (strstr(ptr, "-a")) {     // add
            ptr = strtok(NULL, "\"");
            char todo[MAX_TODO_LENGTH];
            strcpy(todo, ptr);
            add_task(&my_list, todo, 0, 0);

        } else if (strstr(ptr, "-l")) {     // list
            list_tasks(&my_list);

        } else if (strstr(ptr, "-wr")) {    // write
            ptr = strtok(NULL, "\"");
            char path[50];
            strcpy(path, ptr);
            write_list(&my_list, path);

        } else if (strstr(ptr, "-rd")) {    // read
            ptr = strtok(NULL, "\"");
            char path[50];
            strcpy(path, ptr);
            read_list(&my_list, path);

        } else if (strstr(ptr, "-e")) {
            empty_list(&my_list);
        }
    }

    free(my_list.array);

    return 0;
}
