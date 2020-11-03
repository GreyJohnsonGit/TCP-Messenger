#ifndef TB_MESSAGE
#define TB_MESSAGE

#include "IMessage.h"
#include "MessageType.h"

namespace TorrentialBits {
    class Message : public IMessage {
        public:
            Message(MessageType _type);
            Message(MessageType _type, const std::vector<char>& _body);
            Message(const std::vector<char>& _message);

            const std::vector<char> GetRawMessage() const;

            MessageType GetType() const;
            const std::vector<char>& GetBody() const;
        private:
            MessageType type;
            std::vector<char> body;
    };
}
#endif