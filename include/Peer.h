#ifndef TB_PEER
#define TB_PEER

#include <string>

namespace TorrentialBits {
    class Peer {
        public:
            Peer(std::string peerString);

            int GetPeerId();
            const std::string& GetHostName();
            size_t GetListeningPort();
            bool HasFile();

        private:
            int peerId;
            std::string hostName;
            size_t listeningPort;
            bool hasFile;
    };
}

#endif