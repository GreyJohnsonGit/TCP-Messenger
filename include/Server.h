#ifndef TB_SERVER
#define TB_SERVER

#include <vector>
#include <string>
#include <thread>
#include "PeerClient.h"

namespace TorrentialBits {
    class Server {
        public:
            Server(PeerClient _peer) : peer(_peer) {}
            std::thread SpawnThread();
            void Start();
            void Shutdown();

        private:
            PeerClient peer;
            int remotePeer;
    };
}
#endif