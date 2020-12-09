#include "Server.h"
#include "PeerClient.h"
#include <iostream>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <vector>
#include <unistd.h>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
//TODO: clean up imports above

//TODO: Look at changing these
#define ALLOWED_SOCKET_CONNECTIONS 3
#define BUFFER_SIZE 1024

using namespace TorrentialBits;

std::thread Server::SpawnThread() {
    return std::thread( [this] { this->Start(); } );
}

void Server::Start() {
    size_t portNumber = peer.GetListeningPort();

    int serverFileDescriptor = socket(AF_INET, SOCK_STREAM, 0);
    if (serverFileDescriptor == -1)
        throw "Socket File Descriptor Failed";

    int option = 1;
    if (setsockopt(serverFileDescriptor, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &option, sizeof(option)) == -1)
        throw "Socket Set Options Failed";

    struct sockaddr_in address = {};
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(portNumber);
    if (bind(serverFileDescriptor, (struct sockaddr*) &address, sizeof(address)) == -1)
        throw "Socket Binding Failed";
    if (listen(serverFileDescriptor, ALLOWED_SOCKET_CONNECTIONS) == -1)
        throw "Socket Listen Failed";

    while(true) {
        int addressLength = sizeof(address);
        remotePeer = accept(serverFileDescriptor, (struct sockaddr*) &address, (socklen_t*) &addressLength);

        if (remotePeer == -1)
            throw "Socket Connection Acceptance Failed";
        std::cout << "Socket Accepted Connection" << std::endl;


        //TODO: PeerToPeerController thread

        //TODO: Send handshake
    }

}