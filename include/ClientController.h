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
        ClientController(PeerInfo *_peer) : peer(_peer){}
        void Startup();


        private:
            PeerInfo *peer;
    };
}

#endif