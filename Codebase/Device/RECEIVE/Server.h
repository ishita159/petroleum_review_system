#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include "Parser.h"
#define PORT 5001

bool setupSocket();
bool Accept();
std::string convertIntoString(char buffer[], int size);
void getSensorData();
