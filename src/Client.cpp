#include "Client.h"
#include "PeerMessageController.h"
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
#include <netinet/in.h>
#include <netdb.h>

//TODO: clean up imports above

using namespace TorrentialBits;

void Client::Connect() {
    std::cout << "Trying to connect to a client on port: " << remotePeer.GetListeningPort() << std::endl;
    fileDescriptor = socket(AF_INET, SOCK_STREAM, 0);
    if (fileDescriptor == -1)
        throw "Socket File Descriptor Failed Creating Client";

    struct hostent *server = gethostbyname("127.0.0.1");
    if (server == NULL)
        throw "Could Not Find Server";

    struct sockaddr_in serverAddress = {};
    serverAddress.sin_family = AF_INET;
    bcopy((char*)server->h_addr, (char*)&serverAddress.sin_addr.s_addr, server->h_length);
    serverAddress.sin_port = htons(remotePeer.GetListeningPort());
    if (connect(fileDescriptor, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1)
        throw "Failed to Connect";

    peer.SetRemoteFileDescriptor(fileDescriptor);

    std::cout << "Trying to send things" << std::endl;

    //TODO: PeerToPeerController thread
    PeerMessageController *controller = new PeerMessageController(peer, fileDescriptor);
    std::thread controllerThread = controller->SpawnThread();

    //TODO: Send Handshake
    std::string message = "This is a handshake from: " + peer.GetPeerId();
    if (send(fileDescriptor, message.c_str(), message.length() + 1, 0) == -1)
        throw "Socket Send Failed";
}

void Client::Disconnect() {
    close(fileDescriptor);
    fileDescriptor = -1;
}