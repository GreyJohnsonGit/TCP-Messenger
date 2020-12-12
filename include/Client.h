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

        private:
            PeerInfo *peer;
            int remotePeerPort;
            int clientId;
            std::thread primaryThread;
            bool shutdownSignal;
            struct ClientDataPackage {
                int fileDescriptor;
                int clientId;
                int remotePeerPort;
                bool *shutdownSignal;
                PeerInfo *peer;
            };

        static void StartBackgroundClient();
    };
}
#endif