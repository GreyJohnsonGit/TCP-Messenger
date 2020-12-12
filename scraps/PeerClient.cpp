#include <PeerClient.h>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <iostream>

using namespace TorrentialBits;

std::vector<PeerClient> PeerClient::CreatePeersFromFile(std::string fileName, Defines* _defines) {
    std::ifstream file = std::ifstream(fileName);

    if (!file.is_open())
        throw "Peer Info File not found";

    std::vector<PeerClient> peers;
    std::string peerString;
    while (std::getline(file, peerString)) {
        peers.push_back(PeerClient(peerString, _defines));
    }

    file.close();
    return peers;
}

PeerClient PeerClient::GetPeer(int peerId, std::vector<PeerClient> peers) {
    for (auto &peer : peers) {
        if (peer.GetPeerId() == peerId)
            return peer;
    }

    std::cout << "This peerId is not in the allowed list, please try with a valid Id" << std::endl;
    exit(-1);
}

PeerClient::PeerClient(std::string peerString, Defines* _defines) {
    defines = _defines;
    fileDescriptor = -1;
    size_t startOfVar = 0;
    size_t lengthOfVar = peerString.find(' ');
    auto next = [&] () {
        startOfVar = startOfVar + lengthOfVar + 1;
        lengthOfVar = peerString.find(' ', startOfVar) - startOfVar;
    };

    peerId = stoi(peerString.substr(startOfVar, lengthOfVar));
    next();
    hostName = peerString.substr(startOfVar, lengthOfVar);
    next();
    listeningPort = stoi(peerString.substr(startOfVar, lengthOfVar));
    next();
    hasFile = peerString.at(startOfVar) == '1';
}

//void PeerClient::Connect() {
//    fileDescriptor = socket(AF_INET, SOCK_STREAM, 0);
//    if (fileDescriptor == -1)
//        throw "Socket File Descriptor Failed";
//
//    struct hostent *server = gethostbyname("127.0.0.1");
//    if (server == NULL)
//        throw "Could Not Find Server";
//
//    struct sockaddr_in serverAddress = {};
//    serverAddress.sin_family = AF_INET;
//    bcopy((char*)server->h_addr, (char*)&serverAddress.sin_addr.s_addr, server->h_length);
//    serverAddress.sin_port = htons(listeningPort);
//    if (connect(fileDescriptor, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1)
//        throw "Failed to Connect";
//}
//
//void PeerClient::Disconnect() {
//    close(fileDescriptor);
//    fileDescriptor = -1;
//}

std::vector<char> PeerClient::Send(std::vector<char> message, int outputFileDescriptor) {
    if (write(outputFileDescriptor, message.data(), message.size()) == -1)
        throw "Failed to Write Message";

    std::vector<char> buffer(defines->GetPieceSize() + 128);
    if (read(outputFileDescriptor, buffer.data(), buffer.size() - 1) == -1)
        throw "Failed to Read Response";

    return buffer;
}

void PeerClient::SetRemoteFileDescriptor(int _remoteFileDescriptor) {
    remoteFileDescriptor = _remoteFileDescriptor;
}

int PeerClient::GetPeerId() {
    return peerId;
}

const std::string& PeerClient::GetHostName() {
    return hostName;
}

size_t PeerClient::GetListeningPort() {
    return listeningPort;
}

bool PeerClient::HasFile() {
    return hasFile;
}