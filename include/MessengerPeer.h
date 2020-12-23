#ifndef MESSENGERPEER_H
#define MESSENGERPEER_H

#include <IPeer.h>
#include <IController.h>
#include <string>
#include <cstdint>

namespace GMessenger
{
    class MessengerPeer : public IPeer
    {
    public:
        MessengerPeer(uint16_t _portNumber, std::string _address, IController &_controller);

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