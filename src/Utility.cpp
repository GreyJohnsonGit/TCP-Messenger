#include "Utility.h"

using namespace TorrentialBits;

std::vector<char> Utility::UintToCharVector(unsigned int value) {
    int factor = sizeof(unsigned int)/sizeof(char);
    auto converted = std::vector<char>(factor);
    for (int i = 0; i < factor; i++) {
        converted[factor - i - 1] = value & (255 << (8 * i));
    }
    return converted;
}

unsigned int Utility::UintToCharVector(std::vector<char> value) {
    int factor = sizeof(unsigned int)/sizeof(char);
    int converted = 0;
    for (int i = 0; i < factor; i++) {
        converted += (unsigned int)value[i] << (8 * i);
    }
    return converted;
}

std::vector<char> Utility::StringToCharVector(std::string value) {
    std::vector<char> buffer;
    buffer.insert(buffer.end(), value.begin(), value.end());
    return buffer;
}

std::string Utility::StringToCharVector(std::vector<char> value) {
    std::string buffer;
    buffer.insert(buffer.end(), value.begin(), value.end());
    return buffer;
}