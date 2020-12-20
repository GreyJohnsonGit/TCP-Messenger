#ifndef PEER_H
#define PEER_H

#include <IPeer.h>
#include <IController.h>
#include <string>
#include <cstdint>

namespace TorrentialBits
{
    class Peer : public IPeer
    {
    public:
        Peer(uint16_t _portNumber, std::string _address, IController &_controller);

        void Start();
        void End();

    private:
        uint16_t portNumber;
        std::string address;
        IController &controller;

        int AttemptClientConnection();
        int AttemptServerConnection();
    };
}

#endif