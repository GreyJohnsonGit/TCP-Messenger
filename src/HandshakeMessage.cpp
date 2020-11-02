#include "HandshakeMessage.h"

#include <string>

namespace TB = TorrentialBits;

const int HEADER_WIDTH = 18;
const int ZERO_WIDTH = 10;
const int ID_WIDTH = 4;
const int HANDSHAKE_WIDTH = HEADER_WIDTH + ZERO_WIDTH + ID_WIDTH;

TB::HandshakeMessage::HandshakeMessage(unsigned int _id) {
    header = HANDSHAKE_HEADER;
    zeros = std::vector<char>(ZERO_WIDTH);
    fill(zeros.begin(), zeros.end(), 0);
    peerId = _id;
}

TB::HandshakeMessage::HandshakeMessage(std::vector<char> _data) {
    header = std::string(_data.begin(), _data.begin() + HEADER_WIDTH);
    zeros = std::vector<char>(_data.begin() + HEADER_WIDTH, _data.begin() + HEADER_WIDTH + ZERO_WIDTH);
    unsigned int id = 0;
    for (int i = ID_WIDTH; i > 0; i--) {
        id <<= 8;
        char byte = _data[HANDSHAKE_WIDTH - i];
        id += byte;
    }
    peerId = id;
}

const std::vector<char> TB::HandshakeMessage::GetMessageData() const {
    auto data = std::vector<char>(header.begin(), header.end());
    data.insert(data.end(), zeros.begin(), zeros.end());
    data.resize(HANDSHAKE_WIDTH);
    unsigned int id = peerId;
    for (int i = 0; i < ID_WIDTH; i++) {
        char byte = id & 255;
        data[HANDSHAKE_WIDTH - i - 1] = byte;
        id >>= 8;
    }
    return data;
}

const std::string& TB::HandshakeMessage::GetHeader() const {
    return header;
}

const std::vector<char>& TB::HandshakeMessage::GetZeros() const {
    return zeros;
}

int TB::HandshakeMessage::GetPeerId() const {
    return peerId;
}