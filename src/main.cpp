//
// Created by renne_000 on 10/26/2020.
//

#include "Defines.h"
#include "PeerClient.h"
#include "Utility.h"
#include "Server.h"
#include "Client.h"
#include <iostream>
#include <string>
#include <thread>
#include <stdlib.h>

using namespace TorrentialBits;

int main(int argc, char *argv[]) {
    if(argc != 2) {
        std::cout << "Command should be: make run <peerId>" << std::endl;
        exit(-1);
    }

    int peerId = strtol(argv[1], nullptr, 10);
    Defines defines = Defines("Common.cfg");
    std::vector<PeerClient> peerClients = PeerClient::CreatePeersFromFile("PeerInfo0.cfg", &defines);

    PeerClient peer = PeerClient::GetPeer(peerId, peerClients);

    Server *peerServer = new Server(peer);
    std::thread serverThread = peerServer->SpawnThread();

    serverThread.join();

    //TODO: Handle all choking/unchoking logic

    for(PeerClient previousPeer : peerClients) {
        if(previousPeer.GetPeerId() == peerId) break;
        Client *client = new Client(peer, previousPeer);
        client->Connect();
    }

//    try {
//        Defines defines = Defines("Common.cfg");
//        std::vector<PeerClient> peers = PeerClient::CreatePeersFromFile("PeerInfo0.cfg", &defines);
//
//        for (auto &peer : peers) {
//            peer.Connect();
//            auto message = Utility::StringToCharVector(std::to_string(peer.GetPeerId()));
//            auto response = Utility::StringToCharVector(peer.Send(message));
//            std::cout << response << std::endl;
//        }
//    }
//    catch(const char* message) {
//        std::cout << message << std::endl;
//    }
    return 0;
}