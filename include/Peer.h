#ifndef PEER_H
#define PEER_H

#include <IPeer.h>
#include <string>
#include <cstdint>

namespace TorrentialBits
{
    class Peer : public IPeer
    {
    public:
        Peer(std::string _address, uint16_t _portNumber);

        void Start();
        void End();

    private:
        std::string address;
        uint16_t portNumber;

        int AttemptClientConnection();
        int AttemptServerConnection();
    };
}

#endif