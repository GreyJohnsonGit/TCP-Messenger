#include <MessengerController.h>
#include <string>
#include <unistd.h> 
#include <iostream>
#include <thread>
#include <poll.h>

using namespace TorrentialBits;

MessengerController::MessengerController(std::string _userName)
    : userName(_userName)
{}

void MessengerController::Init(int socketHandle)
{
    bool terminateSignal = false;
    std::thread reader(ReadMessage, userName, socketHandle, &terminateSignal);
    std::thread writer(WriteMessage, userName, socketHandle, &terminateSignal);
    reader.join();
    writer.join();
}

void MessengerController::WriteMessage(std::string userName, int socketHandle, bool *terminateSignal) 
{
    try{
    struct pollfd consolePoll = { STDIN_FILENO, POLLIN, 0};
    std::string message;
    while (!*terminateSignal)
    {
        if (poll(&consolePoll, 1, 100))
        {
            message = std::string(128, '\0');
            std::getline(std::cin, message);

            if (message == "q")
            {
                *terminateSignal = true;
                message = std::string("");
            }

            message = userName + ": " + message + "\n";
            if (write(socketHandle, message.c_str(), message.size() + 1) == -1)
                throw "Could not write :(";
        }
        
    }
    }catch(const char* msg){std::cout<<msg<<std::endl;}
}

void MessengerController::ReadMessage(std::string userName, int socketHandle, bool *terminateSignal) 
{
    struct pollfd readPoll = { socketHandle, POLLIN, 0};
    auto message = std::string(128, '\0');
    while (!*terminateSignal)
    {
        if (poll(&readPoll, 1, 100) > 0)
        {
            int readResult = read(socketHandle, (void *)message.data(), message.size());
            if (readResult == -1)
                throw "Could not read :(";
            if (readResult == 0 || message == "q")
                *terminateSignal = true;
            else
                std::cout << message << std::endl;
            message = std::string(128, '\0');
        }
    }
    close(socketHandle);
}