//
// Created by renne_000 on 10/26/2020.
//

#include "Defines.h"
#include "PeerClient.h"
#include "Utility.h"
#include <iostream>
#include <string>

using namespace TorrentialBits;

int main() {
    try {
        Defines defines = Defines("Common.cfg");
        std::vector<PeerClient> peers = PeerClient::CreatePeersFromFile("PeerInfo0.cfg", &defines);

        for (auto &peer : peers) {
            peer.Connect();
            auto message = Utility::StringToCharVector(std::to_string(peer.GetPeerId()));
            auto response = Utility::StringToCharVector(peer.Send(message));
            std::cout << response << std::endl;
        }
    }
    catch(const char* message) {
        std::cout << message << std::endl;
    }
    return 0;
}