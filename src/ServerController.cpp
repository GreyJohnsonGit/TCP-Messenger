#include "ServerController.h"
#include "Utility.h"
#include "MessageType.h"

using namespace TorrentialBits;

std::vector<char> ServerController::ProcessRequest(std::vector<char> request) {
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
    case MessageType::piece:
        return Piece(request);
    }

    throw "Unexpected request type";
}

std::vector<char> test() {
    std::vector<char> response(5);
    response[0] = 'H';
    response[1] = 'e';
    response[2] = 'l';
    response[3] = 'l';
    response[4] = 'o';
    return response;
}

std::vector<char> ServerController::Choke(std::vector<char> &request) {
    return test();
}
std::vector<char> ServerController::Unchoke(std::vector<char> &request)  {
    return test();
}
std::vector<char> ServerController::Interested(std::vector<char> &request)  {
    return test();
}
std::vector<char> ServerController::Disinterested(std::vector<char> &request)  {
    return test();
}
std::vector<char> ServerController::Have(std::vector<char> &request)  {
    return test();
}
std::vector<char> ServerController::Bitfield(std::vector<char> &request)  {
    return test();
}
std::vector<char> ServerController::Request(std::vector<char> &request)  {
    return test();
}
std::vector<char> ServerController::Piece(std::vector<char> &request)  {
    return test();
}