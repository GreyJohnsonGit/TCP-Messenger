#ifndef TB_PEERINFO
#define TB_PEERINFO

#include "Defines.h"
#include <string>
#include <map>
#include <vector>

namespace TorrentialBits {
    class PeerInfo {
        public:
            PeerInfo(std::string fileName, Defines& defines);

            bool GetPieceStatus(int peerId, uint32_t index);
            bool GetHasFile(int peerId);
            bool GetIsServerChoked(int peerId);
            bool GetIsPeerChoked(int peerId);
            bool GetIsServerInterested(int peerId);
            bool GetIsPeerIntereseted(int peerId);
            size_t GetListeningPort(int peerId);
            const std::string& GetHostName(int peerId);
            const std::vector<char>& GetBitField(int peerId);

            void SetPieceStatus(int peerId, uint32_t index, bool hasPiece);
            void SetIsServerChoked(int peerId, bool choked);
            void SetIsPeerChoked(int peerId, bool choked);
            void SetIsServerInterested(int peerId, bool interested);
            void SetIsPeerIntereseted(int peerId, bool interested);

        private:
            struct PeerInfoData {
                bool hasFile;
                bool isServerChoked;
                bool isPeerChoked;
                bool isServerInterested;
                bool isPeerInterested;
                size_t listeningPort;
                std::string hostName;
                std::vector<char> bitField;
            };
            std::map<int, PeerInfoData> peers;
    };
}

#endif