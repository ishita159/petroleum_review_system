#include<iostream>
#include "Server.h"

int main()
{
    if (!setupSocket())
    {
        std::cout << "Socket creation failed" << std::endl;
        return -1;
    }
    bool loop_ctrl = true;
    //the server here will not terminate until we close the pragram 
    //when the client will get disconnected, the server will wait for a new connection and pop up a message that the previous connection was disconnected
    while (loop_ctrl)
    {
        std::cout << "Waiting for connection ..." << std::endl;
        if (!Accept())
        {
            std::cout << "Could not establish connection with client" << std::endl;
            return -1;
        }
        getSensorData();
        std::cout << "Client Disconnected " << std::endl;
    }
    return 0;
}