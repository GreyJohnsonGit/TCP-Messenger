#include <MessengerPeer.h>
#include <string>
#include <cstdint>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <string.h>
#include <iostream>
#include <poll.h>

using namespace GMessenger;

MessengerPeer::MessengerPeer(uint16_t _portNumber, std::string _address, IController &_controller)
    : portNumber(_portNumber), address(_address), controller(_controller)
{}

void MessengerPeer::Start()
{
    int socketHandle = AttemptClientConnection();
    if (socketHandle == -1)
    {
        std::cout << "Listening..." << std::endl;
        socketHandle = AttemptServerConnection();
    }
    
    std::cout << "Connection Successful..." << std::endl;

    controller.Init(socketHandle);
}

void MessengerPeer::End()
{
    
}

int MessengerPeer::AttemptClientConnection()
{
    int socketHandle = socket(AF_INET, SOCK_STREAM, 0);
    if (socketHandle == -1)
        throw "Could not create socket";

    struct hostent *server = gethostbyname(address.c_str());
    if (server == nullptr)
        throw "Unable to resolve server name";

    struct sockaddr_in socketAddress = {};
    socketAddress.sin_family = AF_INET;
    socketAddress.sin_port = htons(portNumber);
    bcopy((char*)server->h_addr, (char*)&socketAddress.sin_addr.s_addr, server->h_length);

    if (connect(socketHandle, (struct sockaddr*)&socketAddress, sizeof(socketAddress)) == -1)
        return  -1;
    else
        return socketHandle;
}

int MessengerPeer::AttemptServerConnection()
{
    int socketHandle = socket(AF_INET, SOCK_STREAM, 0);
    if (socketHandle == -1)
        throw "Could not create socket";

    int option = 1;
    if (setsockopt(socketHandle, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &option, sizeof(option)) == -1)
        throw "Socket Set Options Failed";

    struct sockaddr_in socketAddress = {};
    socketAddress.sin_family = AF_INET;
    socketAddress.sin_port = htons(portNumber);
    socketAddress.sin_addr.s_addr = INADDR_ANY;

    if (bind(socketHandle, (struct sockaddr*) &socketAddress, sizeof(socketAddress)) == -1)
        throw "Socket Binding Failed";

    if (listen(socketHandle, 1) == -1)
        throw "Socket Listen Failed";

    int addressLength = sizeof(socketAddress);
    return accept(socketHandle, (struct sockaddr*) &socketAddress, (socklen_t*) &addressLength);
}