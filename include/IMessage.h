#ifndef TB_IMESSAGE
#define TB_IMESSAGE

#include <vector>

namespace TorrentialBits {
    class IMessage {
        public:
            virtual const std::vector<char> GetMessageData() const = 0;
    };
}

#endif