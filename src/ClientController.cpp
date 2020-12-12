#include "ClientController.h"
#include "Utility.h"
#include <string>
#include <vector>
#include <algorithm>

using namespace TorrentialBits;

ClientController::ClientController(PeerInfo *_peer, Defines *_defines, int _clientId, int _remotePeerId) :
    peer(_peer), defines(_defines), clientId(_clientId), remotePeerId(_remotePeerId) {}


void ClientController::Startup() {
    if(peer->IsInteresting(clientId, remotePeerId)) {

    } else {
        if(peer->HasFile(clientId)) {
            ChokeOrUnchokePeers(peer->GetInterestedTable(clientId), defines->GetNumberOfPreferredNeighbors(), clientId, remotePeerId, peer);
        }
    }

}

//TODO: Choose by data rate
//TODO: Add optimistic unchoked check later
void ClientController::ChokeOrUnchokePeers(std::map<int, bool> interestedTable, size_t preferableNumber, int clientId, int remotePeerId, PeerInfo *peer) {
    std::vector<int> preferableNeighbors;
    std::vector<int> unchokedPeers;

    for(size_t i = 1001; i < peer->GetPeerNetworkSize() + 1001; i++) {
        if(preferableNeighbors.size() >= preferableNumber)
            break;
        if(peer->IsInteresting(clientId, i) && i != (size_t) clientId)
            preferableNeighbors.push_back(i);
    }

    for(size_t i=0; i<peer->GetPeerNetworkSize(); i++) {
        int currentPeer = 1001 + i;
        if(peer->IsChoking(clientId, currentPeer) && clientId != currentPeer) {
            unchokedPeers.push_back(currentPeer);
        }
    }

    for(int unchokedPeerId : unchokedPeers) {
        if(std::find(preferableNeighbors.begin(), preferableNeighbors.end(), unchokedPeerId) == preferableNeighbors.end()) {
            //TODO: Send choke message
            //TODO: Choke peer
        }
    }

    for(int preferredNeighbor : preferableNeighbors) {
        if(std::find(unchokedPeers.begin(), unchokedPeers.end(), preferredNeighbor) == unchokedPeers.end()) {
            //TODO: Send unchoke message
            //TODO: Unchoke peer
        }
    }
}