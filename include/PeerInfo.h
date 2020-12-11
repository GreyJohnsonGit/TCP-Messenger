#ifndef TB_PEERINFO
#define TB_PEERINFO

#include <string>
#include <map>

namespace TorrentialBits {
    class PeerInfo {
        public:
            PeerInfo(std::string fileName);

            const std::string& GetHostName(int peerId);
            size_t GetListeningPort(int peerId);
            bool HasFile(int peerId);

        private:
            struct PeerInfoData {
                bool hasFile;
                size_t listeningPort;
                std::string hostName;
            };
            std::map<int, PeerInfoData> peers;
    };
}

#endif