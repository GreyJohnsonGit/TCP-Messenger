#include "Server.h"
#include "ServerController.h"
#include "HandshakeMessage.h"
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

using namespace TorrentialBits;

struct ServerDataPackage {
    int serverId;
    int serverFileDescriptor;
    bool *shutdownSignal;
    PeerInfo *peerInfo;
    Defines *defines;
    FragmentRepository *fragmentRepository;
    struct sockaddr_in address;   
};

void StartBackgroundServer(ServerDataPackage package);
void HandleConnection(ServerDataPackage package);

Server::Server(int _serverId, PeerInfo *_peerInfo, Defines *_defines, FragmentRepository *_fragmentRepository) {
    serverId = _serverId;
    peerInfo = _peerInfo;
    defines = _defines;
    fragmentRepository = _fragmentRepository;
    shutdownSignal = false;
}

void Server::Start() {
    ServerDataPackage package;
    package.serverId = serverId;
    package.shutdownSignal = &shutdownSignal;
    package.peerInfo = peerInfo;
    package.defines = defines;
    package.fragmentRepository = fragmentRepository;
    primaryThread = std::thread(StartBackgroundServer, package);
}

void Server::End() {
    shutdownSignal = true;
    primaryThread.join();
}

void StartBackgroundServer(ServerDataPackage package) {
    int serverFileDescriptor = socket(AF_INET, SOCK_STREAM, 0);
    if (serverFileDescriptor == -1)
        throw "Socket File Descriptor Failed";

    int option = 1;
    if (setsockopt(serverFileDescriptor, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &option, sizeof(option)) == -1)
        throw "Socket Set Options Failed";

    struct sockaddr_in address = {};
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(package.peerInfo->GetListeningPort(package.serverId));
    if (bind(serverFileDescriptor, (struct sockaddr*) &address, sizeof(address)) == -1)
        throw "Socket Binding Failed";

    if (listen(serverFileDescriptor, package.peerInfo->GetPeerNetworkSize()) == -1)
        throw "Socket Listen Failed";
    
    package.serverFileDescriptor = serverFileDescriptor;
    package.address = address;

    auto threads = std::vector<std::thread>();
    for (size_t i = 0; i < package.peerInfo->GetPeerNetworkSize(); i++) {
        threads.push_back(std::thread(HandleConnection, package));
    }
    
    for (size_t i = 0; i < package.peerInfo->GetPeerNetworkSize(); i++) {
        threads[i].join();
    }

    close(serverFileDescriptor);
}

void HandleConnection(ServerDataPackage package) {
    try {
        std::cout << "Starting" << std::endl;
        int addressLength = sizeof(package.address);
        int newSocket = accept(package.serverFileDescriptor, (struct sockaddr*) &package.address, (socklen_t*) &addressLength);
        if (newSocket == -1)
            throw "Socket Connection Acceptance Failed";

        std::vector<char> handshakeBuffer(32);
        if (read(newSocket, handshakeBuffer.data(), handshakeBuffer.size()) == -1)
                throw "Handshake Read Failed";

        HandshakeMessage handshake(handshakeBuffer);
        ServerController controller(package.serverId, handshake.GetPeerId(), package.peerInfo, package.defines, package.fragmentRepository);

        while (!*package.shutdownSignal || newSocket) {
            std::vector<char> buffer = std::vector<char>(package.defines->GetPieceSize() + package.defines->GetPieceCount());
            
            ssize_t errorCode = read(newSocket, buffer.data(), buffer.size()); 
            if (errorCode == -1)
                throw "Socket Read Failed";
            if (errorCode == 0)
                break;

            std::cout << "Message recieved" << std::endl;

            std::vector<char> response = controller.ProcessRequest(buffer);
            if (response.size() != 0 && send(newSocket, response.data(), response.size(), 0) == -1)
                throw "Socket Send Failed";
        }
        close(newSocket);
    }
    catch (const char* message) {
        std::cout << message;
    }       
}