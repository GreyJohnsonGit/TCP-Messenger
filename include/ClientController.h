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
            static void ChokeOrUnchokePeers(std::map<int, bool> interestedTable, size_t preferableNumber, int clientId, int remotePeerId, PeerInfo *peer);
            ClientController(PeerInfo *_peer, int _clientId, int _remotePeerId, Defines *_defines) : peer(_peer), clientId(_clientId), remotePeerId(_remotePeerId), defines(_defines) {}
            void Startup();


        private:
            PeerInfo *peer;
            int clientId;
            int remotePeerId;
            Defines *defines;


    };
}

#endif