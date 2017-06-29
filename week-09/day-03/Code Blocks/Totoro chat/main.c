#include <stdio.h>
#include <stdlib.h>
#include <process.h>
#include <winsock2.h>
#include <conio.h>
#include <stdint.h>
#include "tmp.h"

int main()
{
    list_size = 0;

    wsa_init();

    _beginthread(message_listen, 0, NULL);
    _beginthread(disco_listen, 0, NULL);
    _beginthread(broadcast_listen, 0, NULL);

    char command;

    start_screen();

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
                puts("Enter a name:");
                gets(my_name);
                printf("%s is set\n", my_name);
                break;
            case 'l':
                list_users();
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
