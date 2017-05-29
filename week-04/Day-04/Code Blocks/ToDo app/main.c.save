#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "functions.h"

int main()
{
    // Create and initialize the list of task structures
    list_t my_list;
    init_list(&my_list);

    start_screen();

    char command[MAX_COMMAND_LENGTH];

    while (1) {
        gets(command);
/*
        test
        printf("\nMAX_COMMAND_LENGTH : \t\t\t%d\n", MAX_COMMAND_LENGTH);
        printf("length of command string : \t\t%d\n", strlen(command));
        printf("command string printed:\n");
        puts(command);
 */
/*
        Copy the input to another string so that it remains intact for possible future use,
        because using strtok() on the input string modifies it.
        strncpy() is better for error handling.
 */
        char com_to_parse[MAX_COMMAND_LENGTH];
        char com_to_parse2[MAX_COMMAND_LENGTH]; // to be used later

        //strcpy(com_to_parse, command); // not safe
        strncpy(com_to_parse, command, MAX_COMMAND_LENGTH-1);
        com_to_parse[MAX_COMMAND_LENGTH-1] = 0;
/*
        test
        printf("\nlength of com_to_parse after strncpy: \t%d\n", strlen(com_to_parse));
        printf("com_to_parse string printed:\n");
        puts(com_to_parse);
 */
        char *ptr;

        // Cut out the string until the first space, which gives you the command without parameters
        ptr = strtok(com_to_parse, " ");

        if (strncmp (ptr, "x", 1) == 0) {            // exit
            break;

        } else if (strncmp (ptr, "s", 1) == 0) {      // start screen
            clrscr();
            start_screen();

        } else if (strncmp (ptr, "-a", 2) == 0) {     // add

            // Copy the original command to yet another string so that it can be re-used
            //strcpy(com_to_parse2, command); // not safe
            strncpy(com_to_parse2, command, MAX_COMMAND_LENGTH-1);
            com_to_parse2[MAX_COMMAND_LENGTH-1] = 0;
/*
            test
            printf("\nlength of com_to_parse2 after strncpy: \t%d\n", strlen(com_to_parse));
            printf("com_to_parse2 string printed:\n");
            puts(com_to_parse);
 */
            // Cut the part until the parameter, then cut the parameter itself
            ptr = strtok(com_to_parse2, "\"");
            ptr = strtok(NULL, "\"");
/*
            test
            printf("\nlength of parameter after strncpy: \t%d\n", strlen(ptr));
            printf("parameter string printed:\n");
            puts(ptr);
 */
            // Handling no parameter error
            if (ptr == NULL) {
                printf("Unable to add, use \" \" to add a task.\n");

            } else {
                char todo[MAX_TODO_LENGTH];
                strcpy(todo, ptr);

                // check priority
                ptr = strtok(NULL, "");
                if (ptr != NULL) {
                    int num = atoi(ptr);
                    if (num == 0) {
                        printf("Unable to add, priority parameter not a number\n");
                    } else {
                        add_task(&my_list, todo, 0, num);
                    }
                } else {
                    add_task(&my_list, todo, 0, 0);
                }
            }

        } else if ((strncmp (ptr, "-l", 2) == 0) && (strncmp (ptr, "-lp", 3) != 0)) {     // list
            list_tasks(&my_list);

        } else if (strstr(ptr, "-wr")) {    // write
            // Copy the original command to yet another string so that it can be re-used
            strcpy(com_to_parse2, command);

            // Cut the part until the parameter, then cut the parameter itself
            ptr = strtok(com_to_parse2, "\"");
            ptr = strtok(NULL, "\"");

            // Handling no parameter error
            if (ptr == NULL) {
                printf("Unable to write to file, use \" \" to provide a path.\n");
            } else {
                char path[255];
                strcpy(path, ptr);
                write_list(&my_list, path);
            }

        } else if (strstr(ptr, "-rd")) {    // read
            // Copy the original command to yet another string so that it can be re-used
            strcpy(com_to_parse2, command);

            // Cut the part until the parameter, then cut the parameter itself
            ptr = strtok(com_to_parse2, "\"");
            ptr = strtok(NULL, "\"");

            // Handling no parameter error
            if (ptr == NULL) {
                printf("Unable to read from file, use \" \" to provide a path.\n");
            } else {
                char path[50];
                strcpy(path, ptr);
                read_list(&my_list, path);
            }

        } else if (strstr(ptr, "-e")) {     // empty
            empty_list(&my_list);

        } else if ((strncmp (ptr, "-r", 2) == 0) && (strncmp (ptr, "-rd", 3) != 0)) {     // remove
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

        } else if (strstr(ptr, "-p")) {     // priority
            ptr = strtok(NULL, " ");
            if (ptr == NULL) {
                printf("Unable to set, no index provided\n");
            } else {
                int ind = atoi(ptr);
                if (ind == 0) {
                    printf("Unable to set, index not a number\n");
                } else if (ind > my_list.size) {
                    printf("Unable to set, index out of bounds\n");
                } else {
                    ptr = strtok(NULL, " ");
                    if (ptr == NULL) {
                        printf("Unable to set, no priority provided\n");
                    } else {
                        int pri = atoi(ptr);
                        if (pri == 0) {
                            printf("Unable to set, priority not a number\n");
                        } else {
                            my_list.array[ind - 1].priority = pri;
                        }
                    }
                }
            }

        } else if (strstr(ptr, "-lp")) {     // list by priority
            arrange_list(&my_list);
            list_tasks(&my_list);

        // not working
        } else {                            // bad command
            printf("Unhandled command, use a command from this list:\n");
            start_screen();
        }
    }

    free(my_list.array);

    return 0;
}
