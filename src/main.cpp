#include "Defines.h"
#include "PeerClient.h"
#include "Utility.h"
#include "Server.h"
#include "Client.h"
#include "PeerInfo.h"
#include "FragmentRepository.h"
#include "ServerController.h"
#include <iostream>
#include <string>
#include <thread>
#include <stdlib.h>

using namespace TorrentialBits;

int main(int argc, char *argv[]) {
    try {
        if (argc < 2)
            throw "Command should be: tb.exe <peerId>";
        int peerId = strtol(argv[1], nullptr, 10);

        Defines defines("Common0.cfg");
        PeerInfo peerInfo("PeerInfo0.cfg");
        FragmentRepository repo(&defines);
        
        if (peerInfo.GetHasFile(peerId))
            repo.CreateFragments(peerId);

        
        /*
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
        */
    }
    catch(const char* message) {
        std::cout << message << std::endl;
    }
    return 0;
}