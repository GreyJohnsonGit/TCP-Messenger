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
    try {
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

        //TODO: Handle all choking/unchoking logic

        for(PeerClient previousPeer : peerClients) {
            std::cout << "Trying to create a client, current peer is: " << peerId << " and the previous is: " << previousPeer.GetPeerId() << "with listening port: " << previousPeer.GetListeningPort() << std::endl;
            if(previousPeer.GetPeerId() == peerId) break;


            Client *client = new Client(peer, previousPeer);
            client->Connect();
        }

        serverThread.join();
    }
    catch(const char* message) {
        std::cout << message << std::endl;
    }
    return 0;
}