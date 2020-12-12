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
            Client(PeerInfo *_peer, Defines *_defines, int _remotePeerPort, int peerId, int _remotePeerId);
            void Start();
            void End();

        private:
            PeerInfo *peer;
            Defines *defines;
            int remotePeerPort;
            int clientId;
            int remotePeerId;
            std::thread primaryThread;
            bool shutdownSignal;
            
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