#ifndef TB_LOGGER
#define TB_LOGGER

#include <string>
#include <vector>

namespace TorrentialBits {
    class Logger {
        public:
            void LogTCPConnect(unsigned int recieverId, unsigned int neighborId, bool localOrigin);
            void LogChangeNeighbor(unsigned int recieverId, std::vector<unsigned int> neighbors);
            void LogOptimisticUnchoke(unsigned int recieverId, unsigned int neighborId);
            void LogUnchoked(unsigned int recieverId, unsigned int neighborId);
            void LogChoked(unsigned int recieverId, unsigned int neighborId);
            void LogHave(unsigned int recieverId, unsigned int neighborId, unsigned int index);
            void LogInterested(unsigned int recieverId, unsigned int neighborId);
            void LogNotInterested(unsigned int recieverId, unsigned int neighborId);
            void LogPieceDownload(unsigned int recieverId, unsigned int neighborId, unsigned int index, unsigned int ownedPieces);
            void LogDownloadComplete(unsigned int recieverId);
        private:
            void WriteToFile(unsigned int writerId, std::string message);
    };
}

#endif