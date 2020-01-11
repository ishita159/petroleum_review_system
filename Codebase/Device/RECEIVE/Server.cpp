#include "Server.h"

struct sockaddr_in address;
int server_fd, new_socket;

std::queue<char> preProcessDataQueue;

bool setupSocket()
{
    int opt = 1;
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        return false;
    }

    // Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                   &opt, sizeof(opt)))
    {
        return false;
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
    if (bind(server_fd, (struct sockaddr *)&address,
             sizeof(address)) < 0)
    {
        return false;
    }
    if (listen(server_fd, 3) < 0)
    {
        return false;
    }
    return true;
}

bool Accept()
{
    int addrlen = sizeof(address);
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
                             (socklen_t *)&addrlen)) < 0)
    {
        return false;
    }
    std::cout << "Connection established with client" << std::endl;
    return true;
}

std::string convertIntoString(char buffer[], int size)
{
    std::string packet = "";
    for (int i = 0; i < size; i++)
    {
        packet += buffer[i];
    }
    return packet;
}

void getSensorData()
{
    char buffer[256];
    int rc;
    // std::cout << "In getsensor data " << std::endl;

    while ((rc = read(new_socket, buffer, sizeof(buffer))) > 0)
    {
        //std::cout <<"Received: " <<convertIntoString(buffer, rc) <<"  RC: "<<rc << std::endl;
        preprocessData(buffer, rc);
        bzero(buffer, sizeof(buffer));
    }
}
