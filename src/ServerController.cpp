#include "ServerController.h"
#include "Utility.h"

using namespace TorrentialBits;

ServerController::ServerController(int _serverId, int _peerId, PeerInfo &_peerInfo, Defines &_defines, FragmentRepository &_fragmentRepository) 
    : serverId(_serverId), peerId(_peerId), peerInfo(_peerInfo), defines(_defines), fragmentRepository(_fragmentRepository) {}

std::vector<char> ServerController::ProcessRequest(std::vector<char> &request) {
    if (request.size() < 5)
        throw "Malformed request";

    MessageType type = (MessageType) request[4];
    switch (type) {
    case MessageType::choke:
        return Choke(request);
    case MessageType::unchoke:
        return Unchoke(request);
    case MessageType::interested:
        return Interested(request);
    case MessageType::disinterested:
        return Disinterested(request);
    case MessageType::have:
        return Have(request);
    case MessageType::bitfield:
        return Bitfield(request);
    case MessageType::request:
        return Request(request);
    default:
        throw "Unexpected request type";
    }
}

std::vector<char> ServerController::Choke(std::vector<char> &request) {
    peerInfo.SetChoke(peerId, serverId, true);
    return GenerateNoResponse();
}

std::vector<char> ServerController::Unchoke(std::vector<char> &request)  {
    peerInfo.SetChoke(peerId, serverId, false);
    return GenerateNoResponse();
}

std::vector<char> ServerController::Interested(std::vector<char> &request)  {
    peerInfo.setInterested(peerId, serverId, true);
    return GenerateNoResponse();
}

std::vector<char> ServerController::Disinterested(std::vector<char> &request)  {
    peerInfo.setInterested(peerId, serverId, false);
    return GenerateNoResponse();
}

std::vector<char> ServerController::Have(std::vector<char> &request)  {
    std::vector<char> requestPayload;
    requestPayload.insert(requestPayload.end(), request.begin() + 5, request.end());
    uint32_t requestedIndex = Utility::UintToCharVector(requestPayload);

    peerInfo.SetPieceStatus(peerId, requestedIndex, true);
    return GenerateNoResponse();
}

std::vector<char> ServerController::Bitfield(std::vector<char> &request)  {
    return GenerateResponse(MessageType::bitfield, peerInfo.GetBitField(serverId));
}

std::vector<char> ServerController::Request(std::vector<char> &request)  {
    std::vector<char> requestPayload;
    requestPayload.insert(requestPayload.end(), request.begin() + 5, request.end());
    uint32_t pieceIndex = Utility::UintToCharVector(requestPayload);

    return GenerateResponse(MessageType::piece, fragmentRepository.GetFragment(serverId, pieceIndex));
}

std::vector<char> ServerController::GenerateNoResponse() {
    return std::vector<char>(0);
}

std::vector<char> ServerController::GenerateResponse(MessageType type, std::vector<char> payload) {
    std::vector<char> response;
    std::vector<char> messageLength = Utility::UintToCharVector(payload.size() + sizeof(type));
    response.insert(response.end(), messageLength.begin(), messageLength.end());
    response.push_back(type);
    response.insert(response.end(), payload.begin(), payload.end());
    return response;
}