#ifndef TB_PEERMESSAGECONTROLLER
#define TB_PEERMESSAGECONTROLLER

#include <vector>
#include <string>
#include <thread>
#include "PeerClient.h"

namespace TorrentialBits {
    class PeerMessageController {
        public:
            PeerMessageController(PeerClient _peer, int _socket) : peer(_peer), socket(_socket) {}
            std::thread SpawnThread();
            void Start();

        private:
            PeerClient peer;
            int socket;
            bool hasShaken = false;
    };
}
#endif