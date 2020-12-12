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
            ClientController(PeerInfo *_peer, Defines *_defines, int _clientId, int _remotePeerId);

            void Startup();
            static void ChokeOrUnchokePeers(std::map<int, bool> interestedTable, size_t preferableNumber, int clientId, int remotePeerId, PeerInfo *peer);

        private:
            PeerInfo *peer;
            Defines *defines;
            int clientId;
            int remotePeerId;


    };
}

#endif