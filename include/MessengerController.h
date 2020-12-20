#ifndef MESSENGERCONTROLLER_H
#define CONTROLLER_H

#include <IController.h>
#include <string>

namespace TorrentialBits
{
    class MessengerController : public IController
    {
    public:
        MessengerController(std::string _userName);

        void Init(int socketHandle);

    private:
        std::string userName;
        static void WriteMessage(std::string userName, int socketHandle, bool *terminateSignal);
        static void ReadMessage(std::string userName, int socketHandle, bool *terminateSignal);
    };
}

#endif