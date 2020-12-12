#ifndef TB_PROFILER
#define TB_PROFILER

#include "PeerInfo.h"
#include <thread>

namespace TorrentialBits {
    class Profiler {
        public:
            Profiler(PeerInfo *_peerInfo);

            void Start();
            void End();
        private:
            PeerInfo *peerInfo;
            std::thread process;
            bool terminate;

            static void Profile(PeerInfo *peerInfo, bool *terminate);
    };
}

#endif