#include "PeerInfo.h"
#include <fstream>
#include <iostream>

using namespace TorrentialBits;

PeerInfo::PeerInfo(std::string fileName, Defines& defines) {
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
        size_t bitFieldSize = (defines.GetPieceCount() / 8) + (defines.GetPieceCount() % 8 ? 1 : 0);
        if (data.hasFile) {
            data.bitField = std::vector<char>(bitFieldSize, 255);
            for (size_t i = 0; defines.GetPieceCount() % 8 != 0 && i < 8 - defines.GetPieceCount() % 8; i++) {
                data.bitField[data.bitField.size() - 1] &= ~(1 << i);
            }
        }
        else {
            data.bitField = std::vector<char>(bitFieldSize, 0);
        }
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
    char &byte = peers[peerId].bitField[index / 8];
    char mask = 1 << (7 - index % 8);
    return byte & mask;
}

bool PeerInfo::HasFile(int peerId) {
    return peers[peerId].hasFile;
}

bool PeerInfo::IsChoking(int senderId, int recieverId) {
    return peers[senderId].chokingTable[recieverId];
}

bool PeerInfo::IsInteresting(int senderId, int recieverId) {
    return peers[senderId].interestedTable[recieverId];
}

size_t PeerInfo::GetListeningPort(int peerId) {
    return peers[peerId].listeningPort;
}

const std::string& PeerInfo::GetHostName(int peerId) {
    return peers[peerId].hostName;
}

const std::vector<char>& PeerInfo::GetBitField(int peerId) {
    return peers[peerId].bitField;
}

void PeerInfo::SetPieceStatus(int peerId, uint32_t index, bool hasPiece) {
    char &byte = peers[peerId].bitField[index / 8];
    char mask = 1 << (7 - index % 8);
    if (hasPiece)
        byte = byte | mask;
    else
        byte = byte & ~mask;
}

void PeerInfo::SetChoke(int senderId, int recieverId, bool choke) {
    peers[senderId].chokingTable[recieverId] = choke;
}

void PeerInfo::setInterested(int senderId, int recieverId, bool interested) {
    peers[senderId].interestedTable[recieverId] = interested;
}