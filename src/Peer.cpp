#include <Peer.h>
#include <string>
#include <cstdint>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <string.h>

using namespace TorrentialBits;

Peer::Peer(std::string _address, uint16_t _portNumber)
    : address(_address), portNumber(_portNumber)
{}

void Peer::Start()
{
    int socket = AttemptClientConnection();
    if (socket == -1)
        socket = AttemptServerConnection();
}

void Peer::End()
{}

int Peer::AttemptClientConnection()
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

int Peer::AttemptServerConnection()
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