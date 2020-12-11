#ifndef TB_HANDSHAKEMESSAGE
#define TB_HANDSHAKEMESSAGE

#include "IMessage.h"
#include <string>

namespace TorrentialBits {
    class HandshakeMessage : public IMessage{
        public:
            const std::string HANDSHAKE_HEADER = "P2PFILESHARINGPROJ";

            HandshakeMessage(unsigned int _id);
            HandshakeMessage(std::vector<char> _data);
            
            const std::vector<char> GetRawMessage() const;

            const std::string& GetHeader() const;
            const std::vector<char>& GetZeros() const;
            int GetPeerId() const;
        
        private:
            std::string header;
            std::vector<char> zeros;
            int peerId;
    };
}

#endif