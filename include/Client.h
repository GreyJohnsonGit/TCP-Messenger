#ifndef TB_CLIENT
#define TB_CLIENT

#include <vector>
#include <string>
#include <thread>
#include "Defines.h"
#include "PeerInfo.h"

namespace TorrentialBits {
    class Client {
        public:
            Client(PeerInfo *_peer, int _remotePeerPort, int peerId, int _remotePeerId, Defines *_defines) : peer(_peer), remotePeerPort(_remotePeerPort), clientId(peerId), remotePeerId(_remotePeerId), defines(_defines){}
            void Start();
            void End();

        private:
            PeerInfo *peer;
            int remotePeerPort;
            int clientId;
            Defines *defines;
            std::thread primaryThread;
            bool shutdownSignal;
            int remotePeerId;
            struct ClientDataPackage {
                int fileDescriptor;
                int remotePeerId;
                int clientId;
                int remotePeerPort;
                bool *shutdownSignal;
                Defines *defines;
                PeerInfo *peer;
            };

        static void StartBackgroundClient(ClientDataPackage package);
    };
}
#endif