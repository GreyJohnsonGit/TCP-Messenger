#ifndef TB_UTILITY
#define TB_UTILITY

#include <vector>
#include <string>

namespace TorrentialBits {
    class Utility {
        public:
            static std::vector<char> UintToCharVector(unsigned int value);
            static unsigned int UintToCharVector(std::vector<char> value);
            static std::vector<char> StringToCharVector(std::string value);
            static std::string StringToCharVector(std::vector<char> value);
    };
}

#endif
