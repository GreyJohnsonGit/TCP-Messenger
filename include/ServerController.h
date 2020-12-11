#ifndef TB_SERVERCONTROLLER
#define TB_SERVERCONTROLLER

#include "PeerInfo.h"
#include "Defines.h"
#include <vector>

namespace TorrentialBits {
    class ServerController {
        public:
            ServerController(int peerId, PeerInfo &_peerInfo, const Defines &_defines);
            std::vector<char> ProcessRequest(std::vector<char> request);

        private:
            int peerId;
            PeerInfo& peerInfo;
            const Defines& defines;

            std::vector<char> Choke(std::vector<char> &request);
            std::vector<char> Unchoke(std::vector<char> &request);
            std::vector<char> Interested(std::vector<char> &request);
            std::vector<char> Disinterested(std::vector<char> &request);
            std::vector<char> Have(std::vector<char> &request);
            std::vector<char> Bitfield(std::vector<char> &request);
            std::vector<char> Request(std::vector<char> &request);
            std::vector<char> Piece(std::vector<char> &request);
    };
}

#endif