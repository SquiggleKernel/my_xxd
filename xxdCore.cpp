//
// Created by amrit on 14/02/26.
//

#include "xxdCore.h"
#include <iostream>
#include <fstream>
#include <format>
#include <cstring>
#include <unistd.h> // For write() and STDOUT_FILENO



void processBuffer(char* buffer, int bytesRead, int* bytesPrinted) {

    int blocks = bytesRead / 16;
    int remaining = bytesRead % 16;


    // size = 8 for bytes + 1 for : 8 spaces + 32 chars for 16 bytes hex + 2 spaces + 16 ascii chars + 1 \n =
    const int outputBufferSize{17408};
    char outputBuffer[outputBufferSize];
    int bufferFilled{0};

    //passing the subbuffers to printAsHex
    for (int i {0} ; i < blocks ; i++) {
        formatToHex(& buffer[i*16], 16 , & outputBuffer[bufferFilled], &bufferFilled ,  *bytesPrinted);
        *bytesPrinted+=16;
    }

    if (remaining>0) {
        formatToHex(&buffer[blocks*16], remaining, & outputBuffer[bufferFilled] , &bufferFilled, *bytesPrinted);
        *bytesPrinted += remaining;
    }
    ssize_t bytesWritten = write(STDOUT_FILENO, outputBuffer, bufferFilled);

    if (bytesWritten == -1) {
        // Handle potential write errors (e.g., broken pipe)
        perror("write failed");
    }
}

// formats 16 bytes of input data and copies to output buffer
void formatToHex(char* buffer , int bytestoConvert, char* outputBuffer, int* bufferFilled, int bytesPrinted) {
    char line[68];
    auto end = std::format_to(line, "{:08x}: ", static_cast<unsigned int>(bytesPrinted));

    int counter{0};
    for (int i{0} ;  i< bytestoConvert ; i++) {
        end = std::format_to(end, "{:02x}", static_cast<unsigned char>(buffer[i]));
        if (counter++%2) {
            end = std::format_to(end, " ");
        }
    }
    for (int i{0} ;  i< 16-bytestoConvert ; i++) {
        end = std::format_to(end, "  ");
        if (++counter%2) {
            end = std::format_to(end, " ");
        }
    }

    end = std::format_to(end, " ");

    for (int i{0} ; i< bytestoConvert ; i++) {
        if (buffer[i] >=32 && buffer[i] <= 126) {
            end = std::format_to(end, "{:c}",buffer[i]);
        }
        else
            end = std::format_to(end, ".");
    }
    for (int i{0} ; i< 16-bytestoConvert ; i++) {
        end = std::format_to(end, " ");
    }
    *end = '\n';

    std::memcpy(outputBuffer , line, 68); // their are 68 characters in line
    *bufferFilled += 68;
}