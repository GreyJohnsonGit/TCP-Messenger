#ifndef TB_PEERINFO
#define TB_PEERINFO

#include "Defines.h"
#include <string>
#include <map>
#include <vector>
#include <mutex>

namespace TorrentialBits {
    class PeerInfo {
        public:
            PeerInfo(std::string fileName, Defines& defines);

            bool GetPieceStatus(int peerId, uint32_t index);
            bool HasFile(int peerId);
            bool IsChoking(int senderId, int recieverId);
            bool IsInteresting(int senderId, int recieverId);
            size_t GetListeningPort(int peerId);
            size_t GetPeerNetworkSize();
            const std::string& GetHostName(int peerId);
            const std::vector<char>& GetBitField(int peerId);

            void SetPieceStatus(int peerId, uint32_t index, bool hasPiece);
            void SetChoke(int senderId, int recieverId, bool choke);
            void SetInterested(int senderId, int recieverId, bool interested);

        private:
            struct PeerInfoData {
                bool hasFile;
                size_t listeningPort;
                std::string hostName;
                std::vector<char> bitField;
                std::map<int, bool> chokingTable;
                std::map<int, bool> interestedTable;
            };
            std::map<int, PeerInfoData> peers;
            std::mutex entryMutex;
    };
}

#endif