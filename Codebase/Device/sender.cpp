#include<bits/stdc++.h>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#define PORT 8080

using namespace std;

char *read_string(char outbuff[], FILE *fp)
{
    int ch, i;
    while (EOF != (ch = fgetc(fp)))
        if (ch == '$')
            break;

    for (i = 0; EOF != (ch = fgetc(fp)); ++i)
    {
        if (ch == '$')
            break;
        outbuff[i] = ch;
    }
    outbuff[i] = '\0';
    return outbuff;
}

char *parser(char *buffer)
{
    int j = 0;
    char *parsed_str;
    for(int i = 0; buffer[i] != '\0'; i++)
    {
        if(buffer[i]=='Q' && buffer[i+1]=='N')
        {
            i = i + 2;
            while(buffer[i]!='Q')
            {
                parsed_str[j] = buffer[i];
                j++;
                i++;
            }
        }
        parsed_str[j] = ':';
        j++;
        if (buffer[i] == 'Q' && buffer[i + 1] == 'L')
        {
            i = i + 2;
            while (buffer[i] != '\0')
            {
                parsed_str[j] = buffer[i];
                j++;
                i++;
            }
        }
    }
    return parsed_str;
}

int main(int argc, char const *argv[])
{

    //reading data from the file to get the string of the from QN<value>QL<value> from large data set
    FILE *file = fopen("petroleum.txt", "r");
 
    char buff[1000];
    char *test;
    char *parsed_string;
    if (file != NULL)
    {
       
        test = read_string(buff, file);
        fclose(file);
    }
    //buff and test both store the string  of the from QN<value>QL<value>

    //parsing the string to make it of the from QN:QL
    parsed_string = parser(buff);
    //cout << parsed_string;

    //sending the parsed string to the receiver
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0)
    {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed \n");
        return -1;
    }
    send(sock, parsed_string, strlen(parsed_string), 0);
    printf("DATA SENT!\n");
    //valread = read(sock, buffer, 1024);
   // printf("%s\n", buffer);

    return 0;
}