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

            std::vector<char> GetFragment(int peerId, uint32_t index);
            void PlaceFragment(int peerId, uint32_t index, std::vector<char> data);
        private:
            Defines* defines;
    };
}

#endif