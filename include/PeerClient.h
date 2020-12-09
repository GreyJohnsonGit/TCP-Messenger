#ifndef TB_PEERCLIENT
#define TB_PEERCLIENT

#include <string>
#include <vector>
#include <Defines.h>

namespace TorrentialBits {
    class PeerClient {
        public:
            static std::vector<PeerClient> CreatePeersFromFile(std::string fileName, Defines* _defines);
            static PeerClient GetPeer(int peerId, std::vector<PeerClient> peers);
            PeerClient(std::string peerString, Defines* _defines);

            void Connect();
            void Disconnect();
            std::vector<char> Send(std::vector<char> message);

            int GetPeerId();
            const std::string& GetHostName();
            size_t GetListeningPort();
            bool HasFile();

        private:
            Defines* defines;
            std::string hostName;
            size_t listeningPort;
            int peerId;
            int fileDescriptor;
            bool hasFile;

    };
}

#endif