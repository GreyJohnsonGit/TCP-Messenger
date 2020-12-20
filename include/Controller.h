#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <IController.h>
#include <string>

namespace TorrentialBits
{
    class Controller : public IController
    {
    public:
        Controller();

        void Init(int socketHandle);

    private:
        void WriteMessage(int socketHandle, const std::string &message);
        std::string ReadMessage(int socketHandle);
    };
}

#endif