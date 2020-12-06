#ifndef TB_PEER
#define TB_PEER

#include <string>
#include <vector>

namespace TorrentialBits {
    class Peer {
        public:
            Peer(std::string peerString);

            int GetPeerId();
            const std::string& GetHostName();
            size_t GetListeningPort();
            bool HasFile();

            static std::vector<Peer> CreatePeersFromFile(std::string fileName);
            
        private:
            int peerId;
            std::string hostName;
            size_t listeningPort;
            bool hasFile;
    };
}

#endif