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

    temp_list.array_size=0;

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
            list_ports();
            break;
        case 'p':
            set_port();
            break;
        case 'w':
            file_to_write();
            break;
        case 'o':
            open_port();
            break;
        case 's':
            write_file(file_name);
            break;
        case 'c':
            close_port();
            break;
        case 'r':
            file_to_read();
            break;
        case 'a':
            calc_avg();
            break;
        default:
            start_screen();
            printf("Command not recognized, choose from the above list\n");
            break;
 		};
	}
    return 0;
}
