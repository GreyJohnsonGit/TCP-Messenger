#include "Logger.h"
#include <ctime>
#include <chrono>
#include <iostream>
#include <sstream>

using namespace TorrentialBits;

void Logger::LogTCPConnect(unsigned int recieverId, unsigned int neighborId, bool localOrigin) {
    std::stringstream messageBuilder;
    messageBuilder << "Peer " << recieverId 
        << (localOrigin ? " makes a connection to Peer " : " is connected from Peer ") 
        << neighborId << ".";
    std::string message = messageBuilder.str();

    WriteToFile(recieverId, message);
}

void Logger::LogChangeNeighbor(unsigned int recieverId, std::vector<unsigned int> neighbors) {
    std::stringstream messageBuilder;
    messageBuilder << "Peer " << recieverId << " has the preferred neighbors ";
    for (unsigned int id : neighbors) {
        messageBuilder << id << ",";
    }
    messageBuilder << ".";
    std::string message = messageBuilder.str();

    WriteToFile(recieverId, message);
}

void Logger::LogOptimisticUnchoke(unsigned int recieverId, unsigned int neighborId) {
    std::stringstream messageBuilder;
    messageBuilder << "Peer " << recieverId << " has the optimistcally unchoked neighbor " << neighborId << ".";
    std::string message = messageBuilder.str();

    WriteToFile(recieverId, message);
}

void Logger::LogUnchoked(unsigned int recieverId, unsigned int neighborId) {
    std::stringstream messageBuilder;
    messageBuilder << "Peer " << recieverId << " is unchoked by " << neighborId << ".";
    std::string message = messageBuilder.str();

    WriteToFile(recieverId, message);
}

void Logger::LogChoked(unsigned int recieverId, unsigned int neighborId) {
    std::stringstream messageBuilder;
    messageBuilder << "Peer " << recieverId << " is choked by " << neighborId << ".";
    std::string message = messageBuilder.str();

    WriteToFile(recieverId, message);
}

void Logger::LogHave(unsigned int recieverId, unsigned int neighborId, unsigned int index) {
    std::stringstream messageBuilder;
    messageBuilder << "Peer " << recieverId << " received the 'have' message from " << neighborId << "for the piece " 
        << index << ".";
    std::string message = messageBuilder.str();

    WriteToFile(recieverId, message);
}

void Logger::LogInterested(unsigned int recieverId, unsigned int neighborId) {
    std::stringstream messageBuilder;
    messageBuilder << "Peer " << recieverId << " is choked by " << neighborId << ".";
    std::string message = messageBuilder.str();

    WriteToFile(recieverId, message);
}

void Logger::LogNotInterested(unsigned int recieverId, unsigned int neighborId) {
    std::stringstream messageBuilder;
    messageBuilder << "Peer " << recieverId << " recieved the 'not interested' message from " << neighborId << ".";
    std::string message = messageBuilder.str();

    WriteToFile(recieverId, message);
}

void Logger::LogPieceDownload(unsigned int recieverId, unsigned int neighborId, unsigned int index, unsigned int ownedPieces) {
    std::stringstream messageBuilder;
    messageBuilder << "Peer " << recieverId << "has downloaded the piece " << index << " from " << neighborId 
    << ". Now the number of pieces it has is " << ownedPieces << ".";
    std::string message = messageBuilder.str();

    WriteToFile(recieverId, message);
}

void Logger::LogDownloadComplete(unsigned int recieverId) {
    std::stringstream messageBuilder;
    messageBuilder << "Peer " << recieverId << "has downloaded the complete file.";
}

void Logger::WriteToFile(unsigned int writerId, std::string message) {
    std::stringstream fileNameBuilder;
    fileNameBuilder << "log_peer_" << writerId << ".log";
    std::string filename = fileNameBuilder.str();

    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    std::time_t time = std::chrono::system_clock::to_time_t(now);

    std::cout << filename << " - [" << std::string(std::ctime(&time)).substr(0, 24) << "]:" << message << std::endl;
}