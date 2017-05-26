#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
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
        char com_to_parse2[MAX_COMMAND_LENGTH];
        strcpy(com_to_parse, command);
        strcpy(com_to_parse2, command);

        char *ptr;
        ptr = strtok(com_to_parse, " ");

        if (strstr(ptr, "x")) {              // exit
            break;

        } else if (strstr(ptr, "s")) {
            clrscr();
            start_screen();

        } else if (strstr(ptr, "-a")) {     // add
            ptr = strtok(com_to_parse2, "\"");
            ptr = strtok(NULL, "\"");
            if (ptr == NULL) {
                printf("Unable to add, use \" \" to add a task.\n");
            } else {
                char todo[MAX_TODO_LENGTH];
                strcpy(todo, ptr);
                add_task(&my_list, todo, 0, 0);
            }

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

        } else if (strstr(ptr, "-e")) {     // empty
            empty_list(&my_list);

        } else if (strstr(ptr, "-r")) {     // remove
            ptr = strtok(NULL, " ");
            if (ptr == NULL) {
                printf("Unable to remove, no index provided\n");
            } else {
                int num = atoi(ptr);
                if (num == 0) {
                    printf("Unable to remove, index not a number\n");
                } else if (num > my_list.size) {
                    printf("Unable to remove, index out of bounds\n");
                } else {
                    remove_task(&my_list, num - 1);
                }
            }

        } else if (strstr(ptr, "-c")) {     // check
            ptr = strtok(NULL, " ");
            if (ptr == NULL) {
                printf("Unable to check, no index provided\n");
            } else {
                int num = atoi(ptr);
                if (num == 0) {
                    printf("Unable to check, index not a number\n");
                } else if (num > my_list.size) {
                    printf("Unable to check, index out of bounds\n");
                } else {
                    check_task(&my_list, num - 1);
                }
            }
        }
    }

    free(my_list.array);

    return 0;
}
