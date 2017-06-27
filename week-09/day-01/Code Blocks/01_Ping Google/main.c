#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <winsock2.h>

//Create a client app that pings google.com to get the latency, and print it out.

int main()
{
    WSADATA wsa_data;
    int ret_code;

    // Initialize Winsock version 2.2
    if ((ret_code = WSAStartup(MAKEWORD(2,2), &wsa_data)) != 0)
    {
        printf("WSAStartup failed with error %d\n", WSAGetLastError());
        return 1;
    }

    // Setup Winsock communication code here
    char *command = "ping google.com";
    if (system(command) != 0)
        printf("Bad command\n");

    // When your application is finished call WSACleanup
    if (WSACleanup() == SOCKET_ERROR)
    {
        printf("WSACleanup failed with error %d\n", WSAGetLastError());
    }

    return 0;
}
