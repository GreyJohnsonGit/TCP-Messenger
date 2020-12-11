#include "Message.h"
#include "Utility.h"

using namespace TorrentialBits;

const int LENGTH_WIDTH = 4;
const int TYPE_WIDTH = 1;

Message::Message(MessageType _type) {
    type = _type;
    body = std::vector<char>(0);
}

Message::Message(MessageType _type, const std::vector<char>& _body) {
    type = _type;
    body = _body;
}

Message::Message(const std::vector<char>& _message) {
    if (_message.size() < 5)
        throw "Messages must be at least 5 bytes";

    type = (MessageType) _message[4];
    body = std::vector<char>(_message.begin() + 5, _message.end());
}

const std::vector<char> Message::GetRawMessage() const {
    auto length = Utility::UintToCharVector(body.size());
    auto typeVector = std::vector<char>(1);
    typeVector[0] = type;

    auto data = std::vector<char>();
    data.insert(data.end(), length.begin(), length.end());
    data.insert(data.end(), typeVector.begin(), typeVector.end());
    data.insert(data.end(), body.begin(), body.end());
    return data;
}

MessageType Message::GetType() const {
    return type;
}

const std::vector<char>& Message::GetBody() const {
    return body;
}