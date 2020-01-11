#include <iostream>
#include "Client.h"
#include "SensorData.h"
extern const char *IP;

int main()
{
    std::string sensorDataString = readFile();
    //std::cout<<sensorDataString<<std::endl;

    if (sensorDataString == "")
    {
        std::cout << "No Data in Sensor File" << std::endl;
        return -1;
    }

    if (createSocket())
    {
        std::cout << "Socket successfully created!" << std::endl;
    }
    //blocking function
    std::cout << "Waiting for Server ... " << std::endl;
    while (!connectServer())
    {
        usleep(1000);
    }
    std::cout << "Connected to Server: " << IP << std::endl;

    // Send Data
    std::string packet = "";

    int len = sensorDataString.length();
    for (int i = 0; i < len; i++)
    {
        //sending 5 characters of data at a time to the server
        packet += sensorDataString[i];
        if(i%5 == 0)
        {
            std::cout<<"Packet: "<<packet<<std::endl;
            if(!(sendData(packet.c_str(), 5)))
            {
                 std::cout << "Sent failed : " << packet << std::endl;
            }
            packet = "";
        }
        usleep(100000);
    }
}