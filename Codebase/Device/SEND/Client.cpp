#include "Client.h"
int sock = 0;
const char *IP = "192.168.0.92";
bool createSocket()
{

    char buffer[1024] = {0};
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        return false;
    }
    return true;
}

bool connectServer()
{
    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, IP, &serv_addr.sin_addr) <= 0)
    {
        //printf("\nInvalid address/ Address not supported \n");
        return false;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        //printf("\nConnection Failed \n");
        return false;
    }
    return true;
}

bool sendData(const char *packet, int size)
{

    if (send(sock, packet, size, MSG_NOSIGNAL) == -1)
    {
        return false;
    }

    return true;
}

