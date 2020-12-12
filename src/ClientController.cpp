#include "ClientController.h"
#include "Utility.h"
#include <string>
#include <vector>
#include <algorithm>

using namespace TorrentialBits;

ClientController::ClientController(PeerInfo *_peer, Defines *_defines, int _clientId, int _remotePeerId, int _clientFileDescriptor) :
    peer(_peer), defines(_defines), clientId(_clientId), remotePeerId(_remotePeerId), clientFileDescriptor(_clientFileDescriptor) {}


void ClientController::Startup() {
    if(peer->IsInteresting(clientId, remotePeerId)) {
        //TODO: set download rate stuff
    } else {
        if(peer->HasFile(clientId)) {
            ChokeOrUnchokePeers(peer->GetInterestedTable(clientId), defines->GetNumberOfPreferredNeighbors(), clientId, remotePeerId, peer);
        } else {
            //TODO: Push to start
            ChokeOrUnchokePeers(peer->GetInterestedTable(clientId), defines->GetNumberOfPreferredNeighbors(), clientId, remotePeerId, peer);
        }
    }

    size_t bitFieldSize = (defines->GetPieceCount() / 8) + (defines->GetPieceCount() % 8 ? 1 : 0);
    SendRequestMessage(peer, bitFieldSize, clientId);


//    std::vector<char> response = controller.ProcessRequest(buffer);
//    if (response.size() != 0 && send(newSocket, response.data(), response.size(), 0) == -1)
//        throw "Socket Send Failed";

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

void ClientController::SendRequestMessage(PeerInfo *peer, size_t bitFieldSize, int clientId) {
    for(size_t i =0; i < bitFieldSize; i++) {

        if(!peer->GetPieceStatus(clientId, i)) {
            for(size_t j=1001; j < peer->GetPeerNetworkSize() + 1001; j++) {

                if(clientId != j && peer->GetPieceStatus(j, i)) {
                    //TODO: SEND
                    return;
                }
            }
        }
    }
}

std::vector<char> ClientController::GenerateResponse(MessageType type, std::vector<char> payload) {
    std::vector<char> response;
    std::vector<char> messageLength = Utility::UintToCharVector(payload.size() + sizeof(type));
    response.insert(response.end(), messageLength.begin(), messageLength.end());
    response.push_back(type);
    response.insert(response.end(), payload.begin(), payload.end());
    return response;
}