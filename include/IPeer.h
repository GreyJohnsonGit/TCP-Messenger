#ifndef IPEER_H
#define IPEER_H

#include <string>
#include <cstdint>

namespace GMessenger
{
    class IPeer
    {
    public:
        virtual void Start() = 0;
        virtual void End() = 0;
    };
}

#endif