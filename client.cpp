#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <iostream>
#define PORT 6008
#define ALLOWED_SOCKET_CONNECTIONS 3
#define BUFFER_SIZE 1024

// DO NOT LINK THIS FILE. USE AS GUIDE FOR ACTUAL CONSTRUCTS.

int main() {
    try {
        int clientFileDescriptor = socket(AF_INET, SOCK_STREAM, 0);
        if (clientFileDescriptor == -1)
            throw "Socket File Descriptor Failed";

        struct hostent *server = gethostbyname("127.0.0.1");
        if (server == NULL)
            throw "Could Not Find Server";

        struct sockaddr_in serverAddress = {};
        serverAddress.sin_family = AF_INET;
        bcopy((char*)server->h_addr, (char*)&serverAddress.sin_addr.s_addr, server->h_length);
        serverAddress.sin_port = htons(PORT);
        if (connect(clientFileDescriptor, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1)
            throw "Failed to Connect";

        std::string message = "Hi, I'm Client";
        if (write(clientFileDescriptor, message.c_str(), message.size() + 1) == -1)
            throw "Failed to Write Message";

        char buffer[BUFFER_SIZE];
        if (read(clientFileDescriptor, buffer, BUFFER_SIZE - 1) == -1)
            throw "Failed to Read Response";

        close(clientFileDescriptor);
    }
    catch(std::string excepetionMessage) {
        std::cout << excepetionMessage << std::endl;
    }
    return 0;
}