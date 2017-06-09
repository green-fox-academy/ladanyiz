#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <time.h>
#include "rs232.h"
#include "functions.h"


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


void list_ports()
{
    uint8_t n = comEnumerate();

    for (uint8_t i = 0; i < n; i++) {
        strcpy(port_name, comGetPortName(i));
        printf("%d.  %s\n", i, port_name);
    }
}


int8_t set_port()
{
    printf("Enter port name: ");
    gets(port_name);
    if (comFindPort(port_name) == -1) {
        printf("Not a valid port name!\n");
        return -1;
    } else {
        index = comFindPort(port_name);
        printf("%s set.\n", port_name);
    }
    return 0;
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


void file_to_write()
{
    printf("Enter a file name: ");
    gets(file_name);
    if ((file_ok(file_name, "w")) != 1)
        printf("Cannot create file \"%s\"\n", file_name);
    else
        printf("File to write: \"%s\"\n", file_name);
}


int8_t open_port()
{
    printf("Trying to access port...\n");
    if (comOpen(comFindPort(port_name), 115200) == 0){
        printf("Unable to open port!\n");
        return -1;
    } else {
        printf("%s is open.\n", port_name);
    }
    return 0;
}


char *timestamp()
{
    time (&rawtime);
    timeinfo = localtime(&rawtime);
    strftime (time_buffer,30,"%Y.%m.%d.%H:%M:%S",timeinfo);
    return time_buffer;
}


int8_t write_file(const char *filename)
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


void close_port()
{
    printf("Trying to access port...\n");
    comClose(index);
    printf("%s is closed\n", port_name);
}


void file_to_read()
{
    printf("Enter file to read: ");
    gets(file_name);
    if ((file_ok(file_name, "r")) != 1)
        printf("Cannot find file \"%s\"\n", file_name);
    else
        printf("File to read: \"%s\"\n", file_name);
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


void calc_avg()
{
    char from[30];
    char to[30];
    int64_t sum = 0;

    printf("Enter \"from\" date (yyyy.mm.dd.hh:mm:ss): ");
    gets(from);
    printf("Enter \"to\" date (yyyy.mm.dd.hh:mm:ss): ");
    gets(to);
    read_file(file_name, from, to, &temp_list);
    for (uint8_t i = 0; i < temp_list.array_size; i++)
        sum += temp_list.temp_array[i];
    printf("The average temperature of this period is %.1f\n", (float)sum / temp_list.array_size);
}

