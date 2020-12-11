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
        data.isServerChoked = true;
        data.isPeerChoked = true;
        if (data.hasFile) {
            data.bitField = std::vector<char>(defines.GetPieceCount(), 1);
            for (size_t i = 1; i <= defines.GetPieceCount() % (sizeof(char) * 8); i++) {
                data.bitField[data.bitField.size() - i] = 0;
            }
        }
        else {
            data.bitField = std::vector<char>(defines.GetPieceCount(), 0);
        }

        peers[peerId] = data;
    }

    file.close();
}

bool PeerInfo::GetPieceStatus(int peerId, uint32_t index) {
    char &byte = peers[peerId].bitField[index / 8];
    char mask = 1 << (7 - index % 8);
    return byte & mask;
}

bool PeerInfo::GetHasFile(int peerId) {
    return peers[peerId].hasFile;
}

bool PeerInfo::GetIsServerChoked(int peerId) {
    return peers[peerId].isServerChoked;
}

bool PeerInfo::GetIsPeerChoked(int peerId) {
    return peers[peerId].isPeerChoked;
}

bool PeerInfo::GetIsServerInterested(int peerId) {
    return peers[peerId].isServerInterested;
}

bool PeerInfo::GetIsPeerIntereseted(int peerId) {
    return peers[peerId].isPeerInterested;
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

void PeerInfo::SetIsServerChoked(int peerId, bool choked) {
    peers[peerId].isServerChoked = choked;
}

void PeerInfo::SetIsPeerChoked(int peerId, bool choked) {
    peers[peerId].isPeerChoked = choked;
}

void PeerInfo::SetIsServerInterested(int peerId, bool interested) {
    peers[peerId].isServerInterested = interested;
}

void PeerInfo::SetIsPeerIntereseted(int peerId, bool interested) {
    peers[peerId].isPeerInterested = interested;
}