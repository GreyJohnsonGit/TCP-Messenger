#include "ClientController.h"
#include "Utility.h"
#include "MessageType.h"
#include <string>
#include <vector>
#include <sys/socket.h>
#include <netinet/in.h>
#include <algorithm>
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <vector>
#include <unistd.h>
#include <string.h>
#include <thread>
#include <chrono>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

using namespace TorrentialBits;

ClientController::ClientController(PeerInfo *_peer, Defines *_defines, FragmentRepository *_fragmentRepository, int _clientId, int _remotePeerId, int _clientFileDescriptor) :
    peer(_peer), defines(_defines), fragmentRepository(_fragmentRepository), clientId(_clientId), remotePeerId(_remotePeerId), clientFileDescriptor(_clientFileDescriptor) {}


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
            std::vector<char> payload;
            std::vector<char> response = GenerateResponse(MessageType::choke, payload);
            if (send(clientFileDescriptor, response.data(), response.size(), 0) == -1)
                throw "Socket Send Failed";

            peer->SetChoke(clientId, remotePeerId, true);
        }
    }

    for(int preferredNeighbor : preferableNeighbors) {
        if(std::find(unchokedPeers.begin(), unchokedPeers.end(), preferredNeighbor) == unchokedPeers.end()) {
            std::vector<char> payload;
            std::vector<char> response = GenerateResponse(MessageType::choke, payload);
            if (send(clientFileDescriptor, response.data(), response.size(), 0) == -1)
                throw "Socket Send Failed";

            peer->SetChoke(clientId, remotePeerId, false);
        }
    }
}

void ClientController::SendRequestMessage(PeerInfo *peer, size_t bitFieldSize, int clientId) {
    for(size_t i =0; i < bitFieldSize; i++) {

        if(!peer->GetPieceStatus(clientId, i)) {
            for(size_t j=1001; j < peer->GetPeerNetworkSize() + 1001; j++) {

                if(clientId != j && peer->GetPieceStatus(j, i)) {
                    std::vector<char> request = GenerateResponse(MessageType::request, fragmentRepository->GetFragment(remotePeerId, i));
                    if (send(clientFileDescriptor, request.data(), request.size(), 0) == -1)
                        throw "Socket Send Failed";
                    
                    std::vector<char> response(defines->GetPieceSize() + 32);
                    if (read(clientFileDescriptor, response.data(), response.size() == -1))
                        throw "Socket Read Failed";
                    
                    uint32_t length = Utility::UintToCharVector(std::vector<char>(response.begin(), response.begin() + 4));
                    response.resize(length + 4);

                    fragmentRepository->PlaceFragment(clientId, i, response);
                    break;
                }
            }
        }
    }

    // TODO SEND HAVE
}

std::vector<char> ClientController::GenerateResponse(MessageType type, std::vector<char> payload) {
    std::vector<char> response;
    std::vector<char> messageLength = Utility::UintToCharVector(payload.size() + sizeof(type));
    response.insert(response.end(), messageLength.begin(), messageLength.end());
    response.push_back(type);
    response.insert(response.end(), payload.begin(), payload.end());
    return response;
}