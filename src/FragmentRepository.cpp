#include "FragmentRepository.h"
#include <fstream>
#include <sstream>

using namespace TorrentialBits;

FragmentRepository::FragmentRepository(Defines* _defines) {
    defines = _defines;
}

void FragmentRepository::CreateFragments(int peerId) {
    std::string fileName = defines->GetFileName();
    size_t fileSize = defines->GetFileSize();
    size_t fragmentSize = defines->GetPieceSize();
    size_t fragmentCount = defines->GetPieceCount();

    std::stringstream directoryBuilder;
    directoryBuilder << "peer_" << peerId << "/";
    std::string directory = directoryBuilder.str();

    std::stringstream fileAddressBuilder;
    fileAddressBuilder << directory << fileName;
    std::string fileAddress = fileAddressBuilder.str();

    std::ifstream file(fileAddressBuilder.str(), std::ios_base::binary);
    if (!file.is_open())
        throw "Directory does not contain file";
    
    for (size_t i = 1; i <= fragmentCount; i++) {
        std::stringstream fragmentAddressBuilder;
        fragmentAddressBuilder << directory << i << "." << fileName;
        std::ofstream fragment(fragmentAddressBuilder.str(), std::ios_base::binary);
        if (!fragment.is_open())
            throw "Could not create fragment";

        std::vector<char> buffer(fragmentSize);
        if (i == fragmentCount)
            buffer = std::vector<char>(fileSize % fragmentSize);
        file.seekg((i - 1) * fragmentSize);
        file.read(buffer.data(), buffer.size());
        fragment.write(buffer.data(), buffer.size());

        fragment.close();
    }
}

void FragmentRepository::MergeFragments(int peerId) {
    std::string fileName = defines->GetFileName();
    size_t fileSize = defines->GetFileSize();
    size_t fragmentSize = defines->GetPieceSize();
    size_t fragmentCount = defines->GetPieceCount();

    std::stringstream directoryBuilder;
    directoryBuilder << "peer_" << peerId << "/";
    std::string directory = directoryBuilder.str();

    std::stringstream fileAddressBuilder;
    fileAddressBuilder << directory << fileName;
    std::string fileAddress = fileAddressBuilder.str();

    std::ofstream file(fileAddressBuilder.str(), std::ios_base::binary);
    if (!file.is_open())
        throw "Could not create file";
    
    for (size_t i = 1; i <= fragmentCount; i++) {
        std::stringstream fragmentAddressBuilder;
        fragmentAddressBuilder << directory << i << "." << fileName;
        std::ifstream fragment(fragmentAddressBuilder.str(), std::ios_base::binary);
        if (!fragment.is_open())
            throw "Fragment not found in directory";

        std::vector<char> buffer(fragmentSize);
        if (i == fragmentCount)
            buffer = std::vector<char>(fileSize % fragmentSize);
        fragment.read(buffer.data(), buffer.size());
        file.write(buffer.data(), buffer.size());

        fragment.close();
    }
}

void FragmentRepository::DeleteFragments(int peerId) {
    std::string fileName = defines->GetFileName();
    size_t fileSize = defines->GetFileSize();
    size_t fragmentSize = defines->GetPieceSize();
    size_t fragmentCount = defines->GetPieceCount();

    std::stringstream directoryBuilder;
    directoryBuilder << "peer_" << peerId << "/";
    std::string directory = directoryBuilder.str();

    for (size_t i = 1; i <= fragmentCount; i++) {
        std::stringstream fragmentAddressBuilder;
        fragmentAddressBuilder << directory << i << "." << fileName;
        remove(fragmentAddressBuilder.str().c_str());
    }
}