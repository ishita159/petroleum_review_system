#include <iostream>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#define PORT 5001

bool createSocket();
bool connectServer();
bool sendData(const char *packet, int size);