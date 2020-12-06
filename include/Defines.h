#ifndef TB_DEFINES
#define TB_DEFINES

#include <unordered_map>

namespace TorrentialBits {
    class Defines {
        public:
            Defines(std::string fileName);

            size_t GetNumberOfPreferredNeighbors();
            size_t GetUnchokingInterval();
            size_t GetOptimisticUnchokingInterval();
            std::string GetFileName();
            size_t GetFileSize();
            size_t GetPieceSize();

        private:
            std::unordered_map<std::string, std::string> table;
    };
}

#endif