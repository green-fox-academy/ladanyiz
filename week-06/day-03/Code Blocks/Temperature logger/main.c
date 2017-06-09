#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <time.h>
#include "rs232.h"
#include "functions.h"

int main()
{
    char command;
    char port_name[5];
    char file_name[20];
    uint8_t index = 0;
    char from[30];
    char to[30];
    int64_t sum = 0;

    uint8_t n = comEnumerate();
    list_type temp_list;
    temp_list.array_size=0;

//    init_list(&temp_list);

	start_screen();

	while (1) {
		command = getch();
		switch (command) {
        case 'h':
            start_screen();
            break;
        case 'e':
            return 0;
        case 'l':
            for (uint8_t i = 0; i < n; i++) {
                strcpy(port_name, comGetPortName(i));
                printf("%d.  %s\n", i, port_name);
            }
            break;
        case 'p':
            printf("Enter port name: ");
            gets(port_name);
            if (comFindPort(port_name) == -1) {
                printf("Not a valid port name!\n");
                break;
            } else {
                index = comFindPort(port_name);
                printf("%s set.\n", port_name);
            }
            break;
        case 'w':
            printf("Enter a file name: ");
            gets(file_name);
            if ((file_ok(file_name, "w")) != 1)
                printf("Cannot create file \"%s\"\n", file_name);
            else
                printf("File to write: \"%s\"\n", file_name);
            break;
        case 'o':
            printf("Trying to access port...\n");
            if (comOpen(comFindPort(port_name), 115200) == 0){
                printf("Unable to open port!\n");
                break;
            } else {
                printf("%s is open.\n", port_name);
            }
            break;
        case 's':
            write_file(file_name);
            break;
        case 'c':
            printf("Trying to access port...\n");
            comClose(index);
            printf("%s is closed\n", port_name);
            break;
        case 'r':
            printf("Enter file to read: ");
            gets(file_name);
            if ((file_ok(file_name, "r")) != 1)
                printf("Cannot find file \"%s\"\n", file_name);
            else
                printf("File to read: \"%s\"\n", file_name);
            break;
        case 'a':
            printf("Enter \"from\" date (yyyy.mm.dd.hh:mm:ss): ");
            gets(from);
            printf("Enter \"to\" date (yyyy.mm.dd.hh:mm:ss): ");
            gets(to);
            read_file(file_name, from, to, &temp_list);
            for (uint8_t i = 0; i < temp_list.array_size; i++)
                sum += temp_list.temp_array[i];
            printf("The average temperature of this period is %.1f\n", (float)sum / temp_list.array_size);
            break;
        default:
            start_screen();
            printf("Command not recognized, choose from the above list\n");
            break;
 		};
	}

    comTerminate();

    return 0;
}
