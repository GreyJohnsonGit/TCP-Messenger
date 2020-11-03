#ifndef TB_UTILITY
#define TB_UTILITY

#include <vector>

namespace TorrentialBits {
    class Utility {
        public:
            static std::vector<char> UintToCharVector(unsigned int value);
            static unsigned int UintToCharVector(std::vector<char> value);
    };
}
#endif