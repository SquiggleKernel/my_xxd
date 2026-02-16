//
// Created by amrit on 14/02/26.
//

#include <iostream>
#include <fstream>
#include <iomanip>


//defining colors need only foreground colors.
[[maybe_unused]] const char* red {"\033[1;91m"};
[[maybe_unused]] const char* green {"\033[1;92m"};
[[maybe_unused]] const char* yellow {"\033[1;93m"};
[[maybe_unused]] const char* blue {"\033[1;94m"};
[[maybe_unused]] const char* white {"\033[1;97m"};
[[maybe_unused]] const char* reset {"\033[0m"};

void printAsHex(unsigned char (&bufferArray)[16], int bytesPrinted, int bytesTogether , bool color);
const char* decideColor(bool color , unsigned char c);


const char* decideColor(bool color , unsigned char c) {
    if (color) {
        if (c<=126 && c>=32)
            return green ;
        else if (c == 0 )
            return white ;
        else if ((c == 0x0a) || (c ==0x09) || (c == 0x0d) )
            return yellow;
        else if (c == 0xff)
            return blue;
        else
            return red;
    }
    else
        return white;
}

void printAsHex(unsigned char (&bufferArray)[16], int bytesPrinted, int bytesTogether , bool color) {

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

        std::cout << decideColor(color, bufferArray[i]);
        std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(bufferArray[i]);
        std::cout << reset;

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
        std::cout << decideColor(color, bufferArray[i]);
        if (bufferArray[i]<=126 && bufferArray[i]>=32) {
            std::cout <<  bufferArray[i];
        }
        else
            std::cout << '.';

        std::cout << reset;
    }
    std::cout << '\n';

}