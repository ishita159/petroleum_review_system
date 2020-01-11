#include "Parser.h"
#include <string.h>

//postProcessing data packet format QN12QL2.9
void setValue(std::string postProcessData)
{
    float quantity = 0, quality = 0;
    int len = postProcessData.length();
    std::string val = "0";
    //if the string two charatcers are Q and N
    if (postProcessData[0] == 'Q' && postProcessData[1] == 'N')
    {
        int i = 2;
        //take all the digits after second index including decimal
        //encountering a character will be the breaking point 
        while ((isdigit(postProcessData[i]) || postProcessData[i] == '.') && i < len)
        {
            val += postProcessData[i++];
        }
        //convert the string storing quantity to float
        quantity = std::stof(val);
        val = "0";
        //check condition for quality delimeter

        if (postProcessData[i++] == 'Q' && postProcessData[i++] == 'L')
        {
            while ((isdigit(postProcessData[i]) || postProcessData[i] == '.') && i < len)
            {
                val += postProcessData[i++];
            }
            quality = std::stof(val);
        }
    }
    std::cout << "Quantity: " << quantity << std::endl;
    std::cout << "Quality: " << quality << std::endl;
}

void postProcess()
{
    // std::cout << "In PostprocessData " << std::endl;

    std::string postProcessData = "";
    char front_char = preProcessDataQueue.front();

    if (front_char != '$')
    {
        return;
    }
    preProcessDataQueue.pop();
    while (preProcessDataQueue.front() != '$')
    {
        postProcessData += preProcessDataQueue.front();
        preProcessDataQueue.pop();
    }
    setValue(postProcessData);
}

/*Format of post process data packet 
$QN13QL8.9
*/
void preprocessData(char buffer[], int size)
{
    for (int i = 0; i < size; i++)
    {
        preProcessDataQueue.push(buffer[i]);
        //if size of the queue is less than the required formate of the string dont process the data
        if (buffer[i] == '$' && preProcessDataQueue.size() > 10)
        {
            postProcess();
        }
    }
}