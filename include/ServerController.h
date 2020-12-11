#ifndef TB_SERVERCONTROLLER
#define TB_SERVERCONTROLLER

#include <vector>

namespace TorrentialBits {
    class ServerController {
        public:
            std::vector<char> ProcessRequest(std::vector<char> request);

        private:
            std::vector<char> Choke(std::vector<char> &request);
            std::vector<char> Unchoke(std::vector<char> &request);
            std::vector<char> Interested(std::vector<char> &request);
            std::vector<char> Disinterested(std::vector<char> &request);
            std::vector<char> Have(std::vector<char> &request);
            std::vector<char> Bitfield(std::vector<char> &request);
            std::vector<char> Request(std::vector<char> &request);
            std::vector<char> Piece(std::vector<char> &request);
    };
}

#endif