#include "PeerInfo.h"
#include <fstream>
#include <iostream>

using namespace TorrentialBits;

PeerInfo::PeerInfo(std::string fileName) {
    std::ifstream file = std::ifstream(fileName);

    if (!file.is_open())
        throw "Peer Info File not found";

    std::string peerString;
    
    for (size_t i = 0; std::getline(file, peerString); i++) {
        size_t startOfVar = 0;
        size_t lengthOfVar = peerString.find(' ');
        auto next = [&] () {
            startOfVar = startOfVar + lengthOfVar + 1;
            lengthOfVar = peerString.find(' ', startOfVar) - startOfVar;
        };

        PeerInfoData data;

        int peerId = stoi(peerString.substr(startOfVar, lengthOfVar));
        next();

        data.hostName = peerString.substr(startOfVar, lengthOfVar);
        next();

        data.listeningPort = stoi(peerString.substr(startOfVar, lengthOfVar));
        next();

        data.hasFile = peerString.at(startOfVar) == '1';
        
        peers[peerId] = data;
    }

    file.close();
}

const std::string& PeerInfo::GetHostName(int peerId) {
    return peers[peerId].hostName;
}

size_t PeerInfo::GetListeningPort(int peerId) {
    return peers[peerId].listeningPort;
}

bool PeerInfo::HasFile(int peerId) {
    return peers[peerId].hasFile;
}