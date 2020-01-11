#include "SensorData.h"

std::string readFile()
{
    std::ifstream sensorFile("petroleum.txt");

    if(!sensorFile.good())
    {
        std::cout<<"Bad File: Give correct File Name"<<std::endl;
    }

    std::string sensorData((std::istreambuf_iterator<char>(sensorFile)),
                 std::istreambuf_iterator<char>());


    return sensorData;

}
