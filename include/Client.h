#ifndef TB_CLIENT
#define TB_CLIENT

#include <vector>
#include <string>
#include <thread>
#include "PeerClient.h"

namespace TorrentialBits {
    class Client {
        public:
            Client(PeerClient _peer, PeerClient _remotePeer) : peer(_peer), remotePeer(_remotePeer) {}
            void Connect();
            void Disconnect();

        private:
            PeerClient peer;
            PeerClient remotePeer;
            int fileDescriptor;
    };
}
#endif