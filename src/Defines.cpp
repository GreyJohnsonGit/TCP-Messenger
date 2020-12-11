#include "Defines.h"
#include <fstream>
#include <string>

using namespace TorrentialBits;

Defines::Defines(std::string fileName) {
    table = std::unordered_map<std::string, std::string>();
    std::ifstream file = std::ifstream(fileName);

    if (!file.is_open())
        throw "Common.cfg not found";

    std::string line;
    while (std::getline(file, line)) {
        std::string varName = line.substr(0, line.find(' '));
        std::string varVal = line.substr(line.find(' ') + 1, line.find('\n'));
        table[varName] = varVal;
    }

    file.close();
}

size_t Defines::GetNumberOfPreferredNeighbors() {
    return std::stoul(table["NumberOfPreferredNeighbors"]);
}

size_t Defines::GetUnchokingInterval() {
    return std::stoul(table["UnchokingInterval"]);
}

size_t Defines::GetOptimisticUnchokingInterval() {
    return std::stoul(table["OptimisticUnchokingInterval"]);
}

const std::string& Defines::GetFileName() {
    return table["FileName"];
}

size_t Defines::GetFileSize() {
    return std::stoul(table["FileSize"]);
}

size_t Defines::GetPieceSize() {
    return std::stoul(table["PieceSize"]);
}

size_t Defines::GetPieceCount() {
    size_t fileSize = GetFileSize();
    size_t pieceSize = GetPieceSize();
    return (fileSize / pieceSize) + (fileSize % pieceSize ? 1 : 0);
}