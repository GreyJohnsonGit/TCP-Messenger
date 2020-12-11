#ifndef TB_SERVERCONTROLLER
#define TB_SERVERCONTROLLER

#include "PeerInfo.h"
#include "Defines.h"
#include "FragmentRepository.h"
#include "MessageType.h"
#include <vector>

namespace TorrentialBits {
    class ServerController {
        public:
            ServerController(int _serverId, int _peerId, PeerInfo &_peerInfo, Defines &_defines, FragmentRepository &_fragmentRepository);
            std::vector<char> ProcessRequest(std::vector<char> &request);

        private:
            int serverId;
            int peerId;
            PeerInfo& peerInfo;
            Defines& defines;
            FragmentRepository& fragmentRepository;


            std::vector<char> Choke(std::vector<char> &request);
            std::vector<char> Unchoke(std::vector<char> &request);
            std::vector<char> Interested(std::vector<char> &request);
            std::vector<char> Disinterested(std::vector<char> &request);
            std::vector<char> Have(std::vector<char> &request);
            std::vector<char> Bitfield(std::vector<char> &request);
            std::vector<char> Request(std::vector<char> &request);
            std::vector<char> Piece(std::vector<char> &request);

            std::vector<char> GenerateNoResponse();
            std::vector<char> GenerateResponse(MessageType type, std::vector<char> payload);
    };
}

#endif