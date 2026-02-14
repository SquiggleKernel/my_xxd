//
// Created by amrit on 14/02/26.
//

#include <iostream>
#include <fstream>
#include <iomanip>

void printAsHex(unsigned char (&bufferArray)[16], int bytesPrinted, int bytesTogether);

void printAsHex(unsigned char (&bufferArray)[16], int bytesPrinted, int bytesTogether) {

    std::cout << std::hex << std::setw(8) << std::setfill('0') << bytesPrinted - 16 << ": " << std::flush;


    const int hexWidth {16*2 + 16/bytesTogether};
    int counter {0};
    int bytesToPrint{};

    //finding out how many bytes are there to print
    if (bytesPrinted%16==0)
        bytesToPrint = 16;
    else
        bytesToPrint = bytesPrinted%16;


    //printing the hex
    for (int i{0} ; i< bytesToPrint ; ++i) {
        std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(bufferArray[i]);

        counter++;
        if (counter%bytesTogether ==0)
            std::cout << ' ';
    }

    // print white spaces for case if say there are only 10 bytes instead of 16
    for (int i{0} ; i< hexWidth-counter*2-counter/bytesTogether ; ++i ) {
        std::cout << ' ';
    }
    std::cout << ' ' << std::dec;


    //printing the ascii wall
    for (int i{0} ; i< bytesToPrint ; ++i) {
        // non printable ascii characters
        if (bufferArray[i]<=126 && bufferArray[i]>=32) {
            std::cout <<  bufferArray[i];
        }
        else
            std::cout << '.';
    }
    std::cout << '\n';

}