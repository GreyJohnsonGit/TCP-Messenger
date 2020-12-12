#include "ClientController.cpp"

#include "Defines.h"
#include "Utility.h"
#include "Server.h"
#include "Profiler.h"
#include "PeerInfo.h"
#include "FragmentRepository.h"
#include "ServerController.h"
#include "Logger.h"
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
        PeerInfo peerInfo("PeerInfo0.cfg", &defines);
        FragmentRepository fragmentRepository(&defines);
        Profiler profiler(&peerInfo);
        Server server(peerId, &peerInfo, &defines, &fragmentRepository);

        if (peerInfo.HasFile(peerId))
            fragmentRepository.CreateFragments(peerId);

        server.Start();
        profiler.Start();

        while (!peerInfo.IsFileDistributed()) {
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }

        profiler.End();
        server.End();
        
        if (!peerInfo.HasFile(peerId))
            fragmentRepository.MergeFragments(peerId);
        fragmentRepository.DeleteFragments(peerId);

    }
    catch(const char* message) {
        std::cout << message << std::endl;
    }
    return 0;
}