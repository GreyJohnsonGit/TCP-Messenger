#include <Controller.h>
#include <string>
#include <unistd.h> 
#include <iostream>

using namespace TorrentialBits;

Controller::Controller()
{}

void Controller::Init(int socketHandle)
{
    WriteMessage(socketHandle, std::string("Hello Brother!"));
    std::cout << ReadMessage(socketHandle);
}

void Controller::WriteMessage(int socketHandle, const std::string &message) 
{
    if (write(socketHandle, message.c_str(), message.size() + 1) == -1)
        throw "Failed to write message :(";
}

std::string Controller::ReadMessage(int socketHandle) 
{
    auto message = std::string(128, '\0');
    if (read(socketHandle, (void *)message.data(), message.size()) == -1)
        throw "Failed to read message :(";
    return message;
}