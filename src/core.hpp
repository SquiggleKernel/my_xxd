#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <filesystem>
#include <ios>


constexpr std::size_t inputBufferSize = 4096;
constexpr std::size_t charPerLineOfInput = 76;   // magic number !, no it is calculated it also include \n
constexpr std::size_t outputBufferSize = (4096/16)*charPerLineOfInput;  // turns out to be 19,456 bytes

constexpr std::array<char, 16>  hex{'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f'};

constexpr auto buildHexTable() {
    std::array<std::array<char, 2>, 256> t{};
    uint64_t c{};
    for (uint64_t i{} ; i<16 ; i++) {
        for (uint64_t j{}; j<16 ; j++) {
            t[c][0] = hex[i];
            t[c][1] = hex[j];
            c++;
        }
    }
    return t;
}

consteval auto buildWallChar() {
    std::array<char, 256> t{};
    t.fill('.');
    for (char i{' '}; i< 127 ; i++) {
        t[static_cast<uint64_t>(i)] = i;
    }
    return t;
}

static constexpr auto hexPairs = buildHexTable();
static constexpr auto wallChar = buildWallChar();


struct Config{
    std::uint64_t bytesPrinted{};
    std::streamsize bytesRead{};
    std::size_t totalBytesProcessed{};
    std::array<char, inputBufferSize> inputBuffer{};
    std::array<char, outputBufferSize> outputBuffer{};
};


void processBuffer(Config& config);