#ifndef TB_CLIENT
#define TB_CLIENT

#include <vector>
#include <string>
#include <thread>
#include "PeerInfo.h"

namespace TorrentialBits {
    class Client {
        public:
            Client(PeerInfo *_peer, int _remotePeerPort, int peerId) : peer(_peer), remotePeerPort(_remotePeerPort), clientId(peerId) {}
            void Start();
            void End();
            void StartBackgroundClient();
            void Disconnect();

        private:
            PeerInfo *peer;
            int remotePeerPort;
            int clientId;
            int fileDescriptor;
            std::thread primaryThread;
            bool shutdownSignal;
    };
}
#endif