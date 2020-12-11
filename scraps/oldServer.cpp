//
// Created by renne_000 on 10/26/2020.
//

#include <thread>
#include <pthread.h>
#include <vector>
#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include <iostream>
#define PORT 6008
#define ALLOWED_SOCKET_CONNECTIONS 3
#define BUFFER_SIZE 1024

// DO NOT LINK THIS FILE. USE AS GUIDE FOR ACTUAL CONSTRUCTS.

void handleConnection(struct sockaddr_in address, int serverFileDescriptor) {
    while (true) {
        int addressLength = sizeof(address);
        int newSocket = accept(serverFileDescriptor, (struct sockaddr*) &address, (socklen_t*) &addressLength);
        if (newSocket == -1)
            throw "Socket Connection Acceptance Failed";
        std::cout << "Socket Accepted Connection" << std::endl;

        char buffer[BUFFER_SIZE] = {};
        if (read(newSocket, buffer, BUFFER_SIZE) == -1)
            throw "Socket Read Failed";
        std::cout << "Message: " << buffer << std::endl;

        std::string message = "Hello Client!";
        if (send(newSocket, message.c_str(), message.length() + 1, 0) == -1)
            throw "Socket Send Failed";
        std::cout << "Message Sent: " << message << std::endl;
        close(newSocket);
    }       
}

int main() {
    std::cout << "Initializing" << std::endl;

    try {
        int serverFileDescriptor = socket(AF_INET, SOCK_STREAM, 0);
        if (serverFileDescriptor == -1)
            throw "Socket File Descriptor Failed";

        int option = 1;
        if (setsockopt(serverFileDescriptor, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &option, sizeof(option)) == -1)
            throw "Socket Set Options Failed";

        struct sockaddr_in address = {};
        address.sin_family = AF_INET;
        address.sin_addr.s_addr = INADDR_ANY;
        address.sin_port = htons(PORT);
        if (bind(serverFileDescriptor, (struct sockaddr*) &address, sizeof(address)) == -1)
            throw "Socket Binding Failed";

        if (listen(serverFileDescriptor, ALLOWED_SOCKET_CONNECTIONS) == -1)
            throw "Socket Listen Failed";
        
        auto threads = std::vector<std::thread>();
        for (size_t i = 0; i < ALLOWED_SOCKET_CONNECTIONS; i++) {
            threads.push_back(std::thread(handleConnection, address, serverFileDescriptor));
        }
        
        for (size_t i = 0; i < ALLOWED_SOCKET_CONNECTIONS; i++) {
            threads[i].join();
        }

        close(serverFileDescriptor);
    }
    catch(std::string excepetionMessage) {
        std::cout << excepetionMessage << std::endl;
    }

    return 0;
}