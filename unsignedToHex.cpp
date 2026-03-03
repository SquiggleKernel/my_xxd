//
// Created by amrit on 26/02/26.
//


#include "xxdCore.h"
#include <array>
#include <cstdint>


constexpr auto buildHexTable() {
    const char hex[] = "0123456789abcdef";
    std::array<uint16_t, 256> t{};
    for (int i = 0; i < 256; i++)
        t[i] = (uint16_t)(hex[i >> 4]) | ((uint16_t)(hex[i & 0x0f]) << 8);
    return t;
}

static constexpr auto hexPairs = buildHexTable();

void charToHex(char* buffer , int bytesToConvert, char* line) {
    int counter{0};
    char* end{&line[0]};
    for (int i{0} ; i <bytesToConvert ; i++ ) {
        *reinterpret_cast<uint16_t*>(end) = hexPairs[(unsigned char)buffer[i]];
        end += 2;
        if (counter++%2) {
            end[0] = ' ';
            end = end +1;
        }
    }
    for (int i{0} ; i <16-bytesToConvert ; i++ ) {
        end[1] = ' ';
        end[0] = ' ';
        end +=2;
        if (counter++%2) {
            end[0] = ' ';
            end = end +1;
        }
    }
}

void intToHex(char* line, int bytesPrinted) {
    unsigned int x = static_cast<unsigned int>(bytesPrinted);
    *reinterpret_cast<uint16_t*>(line+6) = hexPairs[(x) & 0xff];
    *reinterpret_cast<uint16_t*>(line+4) = hexPairs[(x >>  8) & 0xff];
    *reinterpret_cast<uint16_t*>(line+2) = hexPairs[(x >> 16) & 0xff];
    *reinterpret_cast<uint16_t*>(line+0) = hexPairs[(x >> 24) & 0xff];
}
