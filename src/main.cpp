#include <iostream>
#include <memory>
#include <string>
#include <Peer.h>
#include <Controller.h>

using namespace TorrentialBits;

int main()
{
    IController *controller = new Controller();
    IPeer *peer = new Peer(8008, std::string("127.0.0.1"), *controller);
    peer->Start();
    std::cout << "Compiled and Ran :)" << std::endl;
    return 0;
}