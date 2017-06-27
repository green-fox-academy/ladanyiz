#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include "file_IO.h"


//---------------FILE I/O FUNCTIONS-------------------

int file_write_single_line(char *path, char *mode, char *line)
{
    if (strlen(line) > ROW_LENGTH) {
        printf("Line is bigger than the max readable line (%d).", ROW_LENGTH);
        return 1;
    }

    char path_for_test[PATH_LENGTH];
    strcpy(path_for_test, path);

    if(path_test(path_for_test))
    return 1;

    if (is_file_empty(path)) {
        char ok[1];
        int while_ok = 1;

        printf("Would you like to make a new file? y/n: ");
        scanf("%s", &ok);

        while(while_ok) {
            if (strcmp(ok, "n") == 0)
                return 1;
            else if (strcmp(ok, "y") == 0)
                while_ok = 0;
            else
                printf("Wrong command! y/n:\n");
                scanf("%s", &ok);
        }
    }

    if (strcmp(mode, "w") == 0 || strcmp(mode, "a") == 0) {

        FILE *fw;
        fw = fopen(path, mode);
        fprintf(fw, line);
        fclose(fw);
    }

    return 0;
}

int file_write_line_logging_mode(char *path, char *line)
{
    if (strlen(line) > ROW_LENGTH) {
        printf("Line is bigger than the max readable line (%d).", ROW_LENGTH);
        return 1;
    }

    char path_for_test[PATH_LENGTH];
    strcpy(path_for_test, path);

    if(path_test(path_for_test))
    return 1;

    FILE *fw;
    fw = fopen(path, "a");
    time_t curtime;
    struct tm *lt;
    curtime = time(NULL);
    lt = localtime(&curtime);

    fprintf(fw, "%d-%d-%d %d:%d:%d\t%s\n", lt -> tm_year + 1900, lt -> tm_mon, lt -> tm_mday,
            lt ->tm_hour, lt ->tm_min, lt->tm_sec, line);

    fclose(fw);

    return 0;
}

int opened_file_write_line_logging_mode(char *line, FILE *fw)
{
    if (strlen(line) > ROW_LENGTH) {
        printf("Line is bigger than the max readable line (%d).", ROW_LENGTH);
        return 1;
    }

    time_t curtime;
    struct tm *lt;
    curtime = time(NULL);
    lt = localtime(&curtime);
    fprintf(fw, "%d-%d-%d %d:%d:%d\t%s\n", lt -> tm_year + 1900, lt -> tm_mon, lt -> tm_mday,
            lt ->tm_hour, lt ->tm_min, lt->tm_sec, line);

    return 0;
}


int file_write_multiple_lines(char *path, char *mode, char **str_arr, int len)
{
    char path_for_test[PATH_LENGTH];
    strcpy(path_for_test, path);

    if(path_test(path_for_test))
    return 1;

    if (is_file_empty(path)) {
        char ok[1];
        int while_ok = 1;

        printf("Would you like to make a new file? y/n: ");
        scanf("%s", &ok);

        while(while_ok) {
            if (strcmp(ok, "n") == 0)
                return 1;
            else if (strcmp(ok, "y") == 0)
                while_ok = 0;
            else
                printf("Wrong command! y/n:\n");
                scanf("%s", &ok);
        }
    }

    if (strcmp(mode, "w") == 0 || strcmp(mode, "a") == 0) {

        FILE *fw;
        fw = fopen(path, mode);

        for (int i = 0; i < len; i++) {
           fprintf(fw, str_arr[i]);
           fprintf(fw, "\n");
        }

        fclose(fw);
    }

    return 0;
}

int file_read_single_line(char *path, int number, char *line)
{
    char path_for_test[PATH_LENGTH];
    strcpy(path_for_test, path);

    if(path_test(path_for_test))
        return 1;

    if (is_file_empty(path))
        return 1;

    char row[ROW_LENGTH];
    FILE *fr;
    fr = fopen(path, "r");

    for (int i = 0; i < number; i++) {

        if (fgets(row, sizeof(row), fr) == NULL) {
            printf("Error: Given number is bigger than the total number of rows in file!\n");
            return 1;
        }
    }

    fclose(fr);
    strcpy(line, row);

    return 0;
}

char** file_read_multiple_lines(char *path, int from, int how_many)
{

    char path_for_test[PATH_LENGTH];
    strcpy(path_for_test, path);

    if(path_test(path_for_test))
        return;

    if (is_file_empty(path))
        return;

    char row[ROW_LENGTH];

    // Allocate memory for the result array
    char **str_arr = (char**)malloc(how_many * sizeof(char*));

    for (int i = 0; i < how_many; i++) {
        str_arr[i] = (char*)malloc(ROW_LENGTH * sizeof(char));
    }

    FILE *fr;
    fr = fopen(path, "r");

    int to = from + how_many -1;
    int j = 0;
    char *row_mod;

    for (int i = 0; i < to; i++) {
        if (fgets(row, sizeof(row), fr) != NULL) {
            row_mod = strtok(row, "\n");
            if (i >= from - 1) {
                strcpy(str_arr[j], row_mod);
                j++;
            }
        } else {
            printf("There were not enough lines with the given conditions.\n");
            return 0;
        }
    }

    return str_arr;
}

int file_print(char *path)
{

    char path_for_test[PATH_LENGTH];
    strcpy(path_for_test, path);

    if(path_test(path_for_test))
        return 1;

    if (is_file_empty(path))
        return 1;

    FILE *fr;
    char row[ROW_LENGTH];

    fr = fopen(path, "r");

    while (fgets(row, sizeof(row), fr) != NULL) {
        printf("%s", row);
    }

    fclose(fr);

    return 0;
}

int file_print_delay(char *path, int delay)
{

    char path_for_test[PATH_LENGTH];
    strcpy(path_for_test, path);

    if(path_test(path_for_test))
        return 1;

    if (is_file_empty(path))
        return 1;

    FILE *fr;
    char row[ROW_LENGTH];

    fr = fopen(path, "r");

    while (fgets(row, sizeof(row), fr) != NULL) {
        printf("%s", row);
        Sleep(delay);
    }

    fclose(fr);

    return 0;
}

//---------------INSIDE FUNCTIONS TESTS-------------------

int path_test(char *path)
{
    char *ptr;

    ptr = strtok(path, ".");
    ptr = strtok(NULL, "\0");

    if (strcmp(ptr, "txt") != 0) {
        printf("Error_01: Wrong file extension, it must be .txt!\n");
        return 1;
    } else {
        return 0;
    }
}

int is_file_empty(char *path)
{
    FILE *f;
    f = fopen(path, "r");

    if (f == NULL) {
        fclose(f);
        printf("Error_02: File is empty!\n");
        return 1;
    }

    fclose(f);
    return 0;
}























