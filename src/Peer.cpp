#include "Peer.h"

using namespace TorrentialBits;

Peer::Peer(std::string peerString) {
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

int Peer::GetPeerId() {
    return peerId;
}

const std::string& Peer::GetHostName() {
    return hostName;
}

size_t Peer::GetListeningPort() {
    return listeningPort;
}

bool Peer::HasFile() {
    return hasFile;
}