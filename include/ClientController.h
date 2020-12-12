#ifndef TB_CLIENTCONTROLLER
#define TB_CLIENTCONTROLLER

#include "PeerInfo.h"
#include "Defines.h"
#include "FragmentRepository.h"
#include "MessageType.h"
#include <vector>

namespace TorrentialBits {
    class ClientController {
        public:
            ClientController(PeerInfo *_peer, Defines *_defines, FragmentRepository *_fragmentRepository, int _clientId, int _remotePeerId, int _clientFileDescriptor);

            void Startup();
            std::vector<char> GenerateResponse(MessageType type, std::vector<char> payload);
            void ChokeOrUnchokePeers(std::map<int, bool> interestedTable, size_t preferableNumber, int clientId, int remotePeerId, PeerInfo *peer);
            void SendRequestMessage(PeerInfo *peer, size_t bitFieldSize, int clientId);
            void SendNotInterestedMessage(PeerInfo *peer, int clientId, int i);

        private:
            PeerInfo *peer;
            Defines *defines;
            FragmentRepository *fragmentRepository;
            int clientId;
            int remotePeerId;
            int clientFileDescriptor;
    };
}

#endif