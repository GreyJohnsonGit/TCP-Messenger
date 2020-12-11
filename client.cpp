#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <iostream>
#include <vector>
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

        std::vector<char> hndshk(32, 0);
        hndshk[30] = 3;
        hndshk[30] = 234;
        if (write(clientFileDescriptor, hndshk.data(), hndshk.size()) == -1)
            throw "Failed to Write Message";

        for (char i = 0; i < 5; i++) {
            std::vector<char> msg {0, 0, 0, 5, 6, 0, 0, 0, i};
            if (write(clientFileDescriptor, msg.data(), msg.size()) == -1)
                throw "Failed to Write Message";

            std::vector<char> buffer(1024);
            if (read(clientFileDescriptor, buffer.data(), buffer.size()) == -1)
                throw "Failed to Read Response";

            std::cout << "Block[" << (int)i << "]: ";
            for (size_t j = 0; j < 12; j++) {
                std::cout << buffer[j];
            }
            std::cout << "\n";
        }
        close(clientFileDescriptor);
    }
    catch(const char* excepetionMessage) {
        std::cout << excepetionMessage << std::endl;
    }
    return 0;
}