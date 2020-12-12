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
            ClientController(PeerInfo *_peer, int _clientId, int _remotePeerId) : peer(_peer), clientId(_clientId), remotePeerId(_remotePeerId) {}
            void Startup();


        private:
            PeerInfo *peer;
            int clientId;
            int remotePeerId;
    };
}

#endif