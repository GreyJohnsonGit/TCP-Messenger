#ifndef TB_FRAGMENTREPOSITORY
#define TB_FRAGMENTREPOSITORY

#include "Defines.h"
#include <string>
#include <map>
#include <vector>

namespace TorrentialBits {
    class FragmentRepository {
        public:
            FragmentRepository(Defines* _defines);

            void CreateFragments(int peerId);
            void MergeFragments(int peerId);
            void DeleteFragments(int peerId);

            uint32_t GetIndex(int peerId);
            
        private:
            Defines* defines;
    };
}

#endif