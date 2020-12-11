#include "HandshakeMessage.h"
#include "Utility.h"
#include <string>

using namespace TorrentialBits;

const int HEADER_WIDTH = 18;
const int ZERO_WIDTH = 10;
const int ID_WIDTH = 4;
const int HANDSHAKE_WIDTH = HEADER_WIDTH + ZERO_WIDTH + ID_WIDTH;

HandshakeMessage::HandshakeMessage(unsigned int _id) {
    header = HANDSHAKE_HEADER;
    zeros = std::vector<char>(ZERO_WIDTH);
    fill(zeros.begin(), zeros.end(), 0);
    peerId = _id;
}

HandshakeMessage::HandshakeMessage(std::vector<char> _data) {
    header = std::string(_data.begin(), _data.begin() + HEADER_WIDTH);
    zeros = std::vector<char>(_data.begin() + HEADER_WIDTH, _data.begin() + HEADER_WIDTH + ZERO_WIDTH);
    peerId = Utility::UintToCharVector(std::vector<char>(_data.begin() + HEADER_WIDTH + ZERO_WIDTH, _data.end()));
}

const std::vector<char> HandshakeMessage::GetRawMessage() const {
    auto id = Utility::UintToCharVector(peerId);

    auto data = std::vector<char>(header.begin(), header.end());
    data.insert(data.end(), zeros.begin(), zeros.end());
    data.insert(data.end(), id.begin(), id.end());
    return data;
}

const std::string& HandshakeMessage::GetHeader() const {
    return header;
}

const std::vector<char>& HandshakeMessage::GetZeros() const {
    return zeros;
}

int HandshakeMessage::GetPeerId() const {
    return peerId;
}