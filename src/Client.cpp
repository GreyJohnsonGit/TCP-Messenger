#include "Client.h"
#include "ClientController.h"
#include "PeerInfo.h"
#include "Utility.h"
#include <iostream>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <vector>
#include <unistd.h>
#include <string.h>
#include <thread>
#include <chrono>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

//TODO: clean up imports above

using namespace TorrentialBits;

Client::Client(PeerInfo *_peer, Defines *_defines, FragmentRepository *_fragmentRepository, int _remotePeerPort, int peerId, int _remotePeerId) 
    : peer(_peer), defines(_defines), fragmentRepository(_fragmentRepository), remotePeerPort(_remotePeerPort), clientId(peerId), remotePeerId(_remotePeerId) {}


void Client::Start() {
    ClientDataPackage package;
    package.clientId = clientId;
    package.shutdownSignal = &shutdownSignal;
    package.peer = peer;
    package.defines = defines;
    package.remotePeerPort = remotePeerPort;
    package.fragmentRepository = fragmentRepository;
    primaryThread = std::thread(StartBackgroundClient, package);
}

void Client::End() {
    shutdownSignal = true;
    primaryThread.join();
}

std::vector<char> GenerateResponse(MessageType type, std::vector<char> payload) {
    std::vector<char> response;
    std::vector<char> messageLength = Utility::UintToCharVector(payload.size() + sizeof(type));
    response.insert(response.end(), messageLength.begin(), messageLength.end());
    response.push_back(type);
    response.insert(response.end(), payload.begin(), payload.end());
    return response;
}

void Client::StartBackgroundClient(ClientDataPackage package) {
    try{
        int clientFileDescriptor = socket(AF_INET, SOCK_STREAM, 0);
        if (clientFileDescriptor == -1)
            throw "Socket File Descriptor Failed Creating Client";

        struct hostent *server = gethostbyname("127.0.0.1");
        if (server == NULL)
            throw "Could Not Find Server";

        struct sockaddr_in serverAddress = {};
        serverAddress.sin_family = AF_INET;
        bcopy((char*)server->h_addr, (char*)&serverAddress.sin_addr.s_addr, server->h_length);
        serverAddress.sin_port = htons(package.remotePeerPort);
        if (connect(clientFileDescriptor, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1)
            throw "Failed to Connect";

        std::vector<char> handshakeMessage;
        std::string header = "P2PFILESHARINGPROJ";
        std::vector<char> zeros(10, 0);
        std::vector<char> peerIdVector = Utility::UintToCharVector(package.clientId);
        handshakeMessage.insert(handshakeMessage.end(), header.begin(), header.end());
        handshakeMessage.insert(handshakeMessage.end(), zeros.begin(), zeros.end());
        handshakeMessage.insert(handshakeMessage.end(), peerIdVector.begin(), peerIdVector.end());

        if (send(clientFileDescriptor, handshakeMessage.data(), handshakeMessage.size(), 0) == -1)
            throw "Socket Send Failed";


        std::vector<char> payload(package.peer->GetBitField(package.clientId).begin(), package.peer->GetBitField(package.clientId).end());
        std::vector<char> response = GenerateResponse(MessageType::bitfield, payload);
        if (send(clientFileDescriptor, response.data(), response.size(), 0) == -1)
            throw "Bitfield send failed";

        //TODO: PeerToPeerController thread
        ClientController clientController = ClientController(package.peer, package.defines, package.fragmentRepository, package.clientId, package.remotePeerId, clientFileDescriptor);
        while(!*package.shutdownSignal) {
            clientController.Startup();

            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }

        close(clientFileDescriptor);
    } catch (const char* message) {
        std::cout << message;
    }


}

