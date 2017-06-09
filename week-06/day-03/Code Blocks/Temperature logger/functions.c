#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <time.h>
#include "rs232.h"
#include "functions.h"

time_t rawtime;
struct tm *timeinfo;
char time_buffer[30];

/*
void init_list(list_type *t_list)
{
    t_list->temp_array = NULL;
    t_list->array_size = 0;
}
 */

void start_screen()
{
	printf("\n");
	printf("                   Temperature logger\n");
	printf("==========================================================\n");
	printf("Commands:\n");
	printf("h\tShow the command list\n");
	printf("e\tExit from the program\n");
	printf("l\tList available ports\n");
	printf("p\tSet port name\n");
	printf("w\tSet name of file to write\n");
	printf("o\tOpen port\n");
	printf("s\tStart logging / Stop logging\n");
	printf("c\tClose port\n");
	printf("r\tSet name of file to read\n");
	printf("a\tCalculate average in given period\n");
	printf("==========================================================\n\n");
}


int8_t file_ok(const char *filename, const char *op)
{
    FILE *file = fopen(filename, op);
    if (file == NULL) {
        return -1;
    } else {
        fclose(file);
        return 1;
    }
}


char *timestamp()
{
    time (&rawtime);
    timeinfo = localtime(&rawtime);
    strftime (time_buffer,30,"%Y.%m.%d.%H:%M:%S",timeinfo);
    return time_buffer;
}


int8_t write_file(char *filename)
{
    int8_t i = 0;
    char buffer[1];
    char temp_str[5];
    int8_t temp;

    if (!file_ok(filename, "w")) {
        printf("No valid file name provided\n");
        return -1;
    } else {
        printf("Logging started\n");

        FILE *file = fopen(filename, "w");

        while (1) {
            if (comRead(0, buffer, 1) == 1) {
                if (buffer[0] != '\n') {
                    temp_str[i] = buffer[0];
                    i++;
                } else {
                    temp_str[i] = '\0';
                    i = 0;
                    temp = atoi(temp_str);
                    fprintf(file, "%s\t%d\n", timestamp(), temp);
                    if (kbhit()) {
                        char ch = getch();
                        if (ch == 's') {
                            fclose(file);
                            printf("Logging stopped\n");
                            return 0;
                        }
                    }
                }
            }
        }
    }
}


int8_t read_file(const char *filename, const char *from, const char *to, list_type *t_list)
{
    char date[30];
    int temp;
    uint8_t i = 0;

    FILE *file = fopen(filename, "r");

    while (fscanf(file, "%s\t%d\n", date, &temp) == 2) {
        if ((strcmp(date, from) > -1) && (strcmp(date, to) < 1))  {
            t_list->temp_array[i] = temp;
            i++;
            t_list->array_size = i;
        }
    }

    fclose(file);

    return 0;
}

