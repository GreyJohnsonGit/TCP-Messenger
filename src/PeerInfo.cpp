#include "PeerInfo.h"
#include <fstream>
#include <iostream>

using namespace TorrentialBits;

PeerInfo::PeerInfo(std::string fileName, Defines* _defines) : defines(_defines) {
    std::ifstream file = std::ifstream(fileName);

    if (!file.is_open())
        throw "Peer Info File not found";

    std::string peerString;
    
    while (std::getline(file, peerString)) {
        size_t startOfVar = 0;
        size_t lengthOfVar = peerString.find(' ');
        auto next = [&] () {
            startOfVar = startOfVar + lengthOfVar + 1;
            lengthOfVar = peerString.find(' ', startOfVar) - startOfVar;
        };

        PeerInfoData data;

        int peerId = stoi(peerString.substr(startOfVar, lengthOfVar));
        next();
        data.hostName = peerString.substr(startOfVar, lengthOfVar);
        next();
        data.listeningPort = stoi(peerString.substr(startOfVar, lengthOfVar));
        next();
        data.hasFile = peerString.at(startOfVar) == '1';
        size_t bitFieldSize = (defines->GetPieceCount() / 8) + (defines->GetPieceCount() % 8 ? 1 : 0);
        if (data.hasFile) {
            data.bitField = std::vector<char>(bitFieldSize, 255);
            for (size_t i = 0; defines->GetPieceCount() % 8 != 0 && i < 8 - defines->GetPieceCount() % 8; i++) {
                data.bitField[data.bitField.size() - 1] &= ~(1 << i);
            }
        }
        else {
            data.bitField = std::vector<char>(bitFieldSize, 0);
        }
        data.dataRate = 0;
        data.dataSent = 0;
        peers[peerId] = data;
    }
    file.close();

    for (auto &peer : peers) {
        for (auto &peerIndex : peers) {
            peer.second.chokingTable[peerIndex.first] = true;
            peer.second.interestedTable[peerIndex.first] = false;
        }
    }
}

bool PeerInfo::GetPieceStatus(int peerId, uint32_t index) {
    std::lock_guard<std::mutex> gaurd(entryMutex);
    char &byte = peers[peerId].bitField[index / 8];
    char mask = 1 << (7 - index % 8);
    return byte & mask;
}

bool PeerInfo::HasFile(int peerId) {
    std::lock_guard<std::mutex> gaurd(entryMutex);
    return peers[peerId].hasFile;
}

bool PeerInfo::IsChoking(int senderId, int recieverId) {
    std::lock_guard<std::mutex> gaurd(entryMutex);
    return peers[senderId].chokingTable[recieverId];
}

bool PeerInfo::IsInteresting(int senderId, int recieverId) {
    std::lock_guard<std::mutex> gaurd(entryMutex);
    return peers[senderId].interestedTable[recieverId];
}

size_t PeerInfo::GetListeningPort(int peerId) {
    return peers[peerId].listeningPort;
}

size_t PeerInfo::GetPeerNetworkSize() {
    return peers.size();
}

const std::string& PeerInfo::GetHostName(int peerId) {
    return peers[peerId].hostName;
}

const std::vector<char>& PeerInfo::GetBitField(int peerId) {
    std::lock_guard<std::mutex> gaurd(entryMutex);
    return peers[peerId].bitField;
}

size_t PeerInfo::GetDataSent(int peerId) {
    std::lock_guard<std::mutex> gaurd(entryMutex);
    return peers[peerId].dataSent;
}

double PeerInfo::GetDataRate(int peerId) {
    std::lock_guard<std::mutex> gaurd(entryMutex);
    return peers[peerId].dataRate;
}

bool PeerInfo::IsFileDistributed() {
    for (auto peer : peers) {
        for (size_t i = 0; i < defines->GetFileSize() / defines->GetPieceSize() + (defines->GetFileSize() % defines->GetPieceSize() ? 1 : 0); i++) {
             if (GetPieceStatus(peer.first, i) != true)
                return false;
        }
    }
}

void PeerInfo::SetPieceStatus(int peerId, uint32_t index, bool hasPiece) {
    std::lock_guard<std::mutex> gaurd(entryMutex);
    char &byte = peers[peerId].bitField[index / 8];
    char mask = 1 << (7 - index % 8);
    if (hasPiece)
        byte = byte | mask;
    else
        byte = byte & ~mask;
}

void PeerInfo::SetChoke(int senderId, int recieverId, bool choke) {
    std::lock_guard<std::mutex> gaurd(entryMutex);
    peers[senderId].chokingTable[recieverId] = choke;
}

void PeerInfo::SetInterested(int senderId, int recieverId, bool interested) {
    std::lock_guard<std::mutex> gaurd(entryMutex);
    peers[senderId].interestedTable[recieverId] = interested;
}

void PeerInfo::SetBitField(int senderId, std::vector<char> bitField) {
    std::lock_guard<std::mutex> gaurd(entryMutex);
    peers[senderId].bitField = bitField;
}

void PeerInfo::SetDataSent(int peerId, size_t data) {
    std::lock_guard<std::mutex> gaurd(entryMutex);
    peers[peerId].dataSent = data;
}

void PeerInfo::AddDataSent(int peerId, size_t data) {
    std::lock_guard<std::mutex> gaurd(entryMutex);
    peers[peerId].dataSent = peers[peerId].dataSent + data;
}

void PeerInfo::SetDataRate(int peerId, double rate) {
    std::lock_guard<std::mutex> gaurd(entryMutex);
    peers[peerId].dataRate = rate;
}
