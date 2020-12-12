#include "PeerMessageController.h"
#include <iostream>
#include <unistd.h>
#include <thread>
#include <netinet/in.h>


using namespace TorrentialBits;

std::thread PeerMessageController::SpawnThread() {
    return std::thread( [this] { this->Start(); } );
}

void PeerMessageController::Start() {
    while(true){
        std::cout << "Beginning Message controller, attempting to read input..." << std::endl;
        char buffer[1024];
        if (read(socket, buffer, 1024) == -1)
            throw "Socket Read Failed";

        std::cout << "This is the message sent, printing directly: " << buffer << std::endl;
        std::cout << "Now sleeping for six seconds before sending a message" << std::endl;
        sleep(6);

        std::string message = "Hello Client! I am: " + peer.GetPeerId();
        if (send(socket, message.c_str(), message.length() + 1, 0) == -1)
            throw "Socket Send Failed";
        std::cout << "Message Sent: " << message << std::endl;
    }
}