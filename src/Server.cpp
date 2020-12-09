#include "Server.h"
#include "PeerClient.h"
#include <iostream>

using namespace TorrentialBits;

std::thread Server::SpawnThread() {
    return std::thread( [this] { this->InitializeServer(); } );
}

void Server::InitializeServer() {
    size_t peerId = peer.GetPeerId();
    std::cout << peerId << std::endl;
}