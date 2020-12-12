#include "Client.h"
#include "ClientController.h"
#include "PeerInfo.h"
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
#include <thread>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

//TODO: clean up imports above

using namespace TorrentialBits;

void Client::Start() {
    primaryThread = std::thread(StartBackgroundClient);
}

void Client::End() {
    shutdownSignal = true;
    primaryThread.join();
}

void Client::StartBackgroundClient() {
    try{
        fileDescriptor = socket(AF_INET, SOCK_STREAM, 0);
        if (fileDescriptor == -1)
            throw "Socket File Descriptor Failed Creating Client";

        struct hostent *server = gethostbyname("127.0.0.1");
        if (server == NULL)
            throw "Could Not Find Server";

        struct sockaddr_in serverAddress = {};
        serverAddress.sin_family = AF_INET;
        bcopy((char*)server->h_addr, (char*)&serverAddress.sin_addr.s_addr, server->h_length);
        serverAddress.sin_port = htons(remotePeerPort);
        if (connect(fileDescriptor, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1)
            throw "Failed to Connect";

        //TODO: Send Handshake correctly
        std::string message = "This is a handshake from: " + clientId;
        if (send(fileDescriptor, message.c_str(), message.length() + 1, 0) == -1)
            throw "Socket Send Failed";

        //TODO: PeerToPeerController thread
        ClientController clientController = new ClientController(PeerInfo *peer);
        while(!shutdownSignal) {
            clientController.Startup();
        }

        close(fileDescriptor);
    } catch (const char* message) {
        std::cout << message;
    }


}

