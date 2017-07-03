#include <stdio.h>
#include <stdlib.h>
#include <process.h>
#include <winsock2.h>
#include <conio.h>
#include <stdint.h>
#include <windows.h>
#include "header.h"

int main()
{
    char command;

    list_size = 0;

    file = fopen("log.txt", "w");

    wsa_init();

    start_screen();

    printf("Enter your name: ");
    gets(my_name);
    printf("%s is set", my_name);

    _beginthread(broadcast_listen, 0, NULL);
    _beginthread(disco_listen, 0, NULL);
    _beginthread(message_listen, 0, NULL);

    while(1) {
        if (kbhit()) {
            command = getch();
            switch (command) {
            case 'h':
                system("cls");
                start_screen();
                break;
            case 'e':
                return 0;
            case 'n':
                printf("\nEnter a name:");
                gets(my_name);
                printf("%s is set", my_name);
                break;
            case 'l':
                list_users();
                break;
            case 's':
                printf("\nEnter a file name (*.txt): ");
                char *file_name;
                gets(file_name);
                save_to_file(file_name);
                break;
            case 'r':
                printf("\nEnter the file name (*.txt): ");
                char *file_to_read;
                gets(file_to_read);
                read_from_file(file_to_read);
                break;
            case 'd':
                broadcast();
                break;
            case 'm':
                send_message();
                break;
            default:
                break;
            }
        }
    }

    WSACleanup();

    return 0;
}
