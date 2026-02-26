//
// Created by amrit on 26/02/26.
//


#include "xxdCore.h"

const char hexLookup[]{"0123456789abcdef"};

void charToHex(char* buffer , int bytesToConvert, char* line) {
    int counter{0};
    char* end{&line[0]};
    for (int i{0} ; i <bytesToConvert ; i++ ) {
        end[1] = hexLookup[buffer[i] & 0x0f];
        end[0] = hexLookup[(buffer[i] >> 4) & 0x0f];
        end = &end[2];
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
    unsigned int x {static_cast<unsigned int>(bytesPrinted)};
    for (int i{0}; i < 8; i++) {
        line[7-i] = hexLookup[(x >> i * 4) & 0x0f];
    }
}
