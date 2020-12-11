#ifndef TB_SERVER
#define TB_SERVER

#include "PeerInfo.h"
#include "Defines.h"
#include "FragmentRepository.h"
#include <vector>
#include <string>
#include <thread>

namespace TorrentialBits {
    class Server {
        public:
            Server(int _serverId, PeerInfo *_peerInfo, Defines *_defines, FragmentRepository *_fragmentRepository);
            void Start();
            void End();
        
        private:
            int serverId;
            PeerInfo *peerInfo; 
            Defines *defines;
            FragmentRepository *fragmentRepository;
            std::thread primaryThread;
            bool shutdownSignal;
    };
}
#endif