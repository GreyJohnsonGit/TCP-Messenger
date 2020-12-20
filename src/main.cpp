#include <iostream>
#include <memory>
#include <string>
#include <Peer.h>
#include <MessengerController.h>

using namespace TorrentialBits;

int main(int argc, char** argv)
{
    if (argc != 4)
    {
        std::cout << "peerProcess <address> <port> <name>" << std::endl;
        return 0;
    }
    std::string address = std::string(argv[1]);
    int port = std::stoi(argv[2]);
    std::string name = std::string(argv[3]);

    IController *controller = new MessengerController(name);
    IPeer *peer = new Peer(port, address, *controller);
    peer->Start();
    std::cout << "Exiting..." << std::endl;
    return 0;
}