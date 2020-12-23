#ifndef ICONTROLLER_H
#define ICONTROLLER_H

#include <string>
#include <cstdint>

namespace GMessenger
{
    class IController
    {
    public:
        virtual void Init(int socketHandle) = 0;
    };
}

#endif