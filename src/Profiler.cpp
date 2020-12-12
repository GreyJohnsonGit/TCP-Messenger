#include "Profiler.h"
#include <chrono>

using namespace TorrentialBits;

Profiler::Profiler(PeerInfo *_peerInfo) : peerInfo(_peerInfo), terminate(false) {}

void Profiler::Start() {
    process = std::thread(Profile, peerInfo, &terminate);
}

void Profiler::End() {
    terminate = true;
    process.join();
}

void Profiler::Profile(PeerInfo *peerInfo, bool *terminate) {
    while (!*terminate) {
        for (size_t i = 1001; i < 1001 + peerInfo->GetPeerNetworkSize(); i++) {
            peerInfo->SetDataRate(i, peerInfo->GetDataSent(i));
            peerInfo->SetDataSent(i, 0);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}