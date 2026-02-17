//
// Created by amrit on 14/02/26.
//

#include <iostream>
#include <fstream>
#include <iomanip>

void printAsHex(char *bufferArray,int bytesToRead, int bytesPrinted, int bytesTogether , bool color);
void processBuffer(char* buffer, int bytesRead, int* bytesPrinted, int bytesTogether, bool color) ;
const char* decideColor(bool color , unsigned char c);



//defining ANSI colors need only foreground colors.
[[maybe_unused]] const char* colorRed {"\033[1;91m"};
[[maybe_unused]] const char* colorGreen {"\033[1;92m"};
[[maybe_unused]] const char* colorYellow {"\033[1;93m"};
[[maybe_unused]] const char* colorBlue {"\033[1;94m"};
[[maybe_unused]] const char* colorWhite {"\033[1;97m"};
[[maybe_unused]] const char* defaultColor {"\033[0m"};
// A flat array of 512 characters (256 pairs of hex)
static const char hex_table[] =
    "000102030405060708090a0b0c0d0e0f"
    "101112131415161718191a1b1c1d1e1f"
    "202122232425262728292a2b2c2d2e2f"
    "303132333435363738393a3b3c3d3e3f"
    "404142434445464748494a4b4c4d4e4f"
    "505152535455565758595a5b5c5d5e5f"
    "606162636465666768696a6b6c6d6e6f"
    "707172737475767778797a7b7c7d7e7f"
    "808182838485868788898a8b8c8d8e8f"
    "909192939495969798999a9b9c9d9e9f"
    "a0a1a2a3a4a5a6a7a8a9aaabacadaeaf"
    "b0b1b2b3b4b5b6b7b8b9babbbcbdbebf"
    "c0c1c2c3c4c5c6c7c8c9cacbcccdcecf"
    "d0d1d2d3d4d5d6d7d8d9dadbdcdddedf"
    "e0e1e2e3e4e5e6e7e8e9eaebecedeeef"
    "f0f1f2f3f4f5f6f7f8f9fafbfcfdfeff";


void processBuffer(char* buffer, int bytesRead, int* bytesPrinted, int bytesTogether, bool color) {

    int blocks = bytesRead / 16;
    int remaining = bytesRead % 16;

    //passing the subbuffers to printAsHex
    for (int i {0} ; i < blocks ; i++) {
        printAsHex(& buffer[i*16], 16, *bytesPrinted, bytesTogether, color );
        *bytesPrinted+=16;
    }

    if (remaining>0) {
        printAsHex(&buffer[blocks*16], remaining, *bytesPrinted, bytesTogether, color );
        *bytesPrinted += remaining;
    }

}


// different colors for different characters are decided here
const char* decideColor(bool color , unsigned char c) {
    if (color) {
        if (c<=126 && c>=32)
            return colorGreen ;
        else if (c == 0 )
            return colorWhite ;
        else if ((c == 0x0a) || (c ==0x09) || (c == 0x0d) )
            return colorYellow;
        else if (c == 0xff)
            return colorBlue;
        else
            return colorRed;
    }
    else
        return "";
}

//defining function for reset
std::string reset(bool color) {
    if (color) return defaultColor;
    else return "";
}



// takes 16 bytes buffer and prints them into hex
void printAsHex(char *bufferArray,int bytesToRead, int bytesPrinted, int bytesTogether , bool color) {


    // for (int i{0} ; i < bytesToRead ; i++) {
    //     std::cout << (int)bufferArray[i] << " ";
    // }
    // std::cout <<std::endl;

    std::string colorState{}, colorTemp{};
    
    //defining stringstream as cout is becoming expensive
    std::stringstream lineBuffer{};

    if (color) {
        lineBuffer << colorWhite;
        colorState = colorWhite;
    }
    lineBuffer << std::hex << std::setw(8) << std::setfill('0') << bytesPrinted << ": ";

    int counter{0};
    //printing the hex
    for (int i{0} ; i< 16 ; ++i) {
        colorTemp = decideColor(color, bufferArray[i]);
        if (colorState != colorTemp) {
            lineBuffer << colorTemp;
            colorState = colorTemp;
        }
        if (i < bytesToRead){
            int x = static_cast<int>(static_cast<unsigned char>(bufferArray[i]));
        lineBuffer << hex_table[x];
    }
        else
            lineBuffer << "  ";

        counter++;
        if (counter%bytesTogether ==0)
            lineBuffer << ' ';
    }

    lineBuffer << ' ' << std::dec;


    //printing the ascii wall
    for (int i{0} ; i< 16 ; ++i) {
        // non printable ascii characters
        unsigned char chi{static_cast<unsigned char>(bufferArray[i])};

        colorTemp = decideColor(color, chi);
        if (colorState != colorTemp) {
            lineBuffer << colorTemp;
            colorState = colorTemp;
        }
        if (i < bytesToRead) {
            if (chi<=126 && chi>=32) {
                lineBuffer <<  chi;
            }
            else
                lineBuffer << '.';
        }
        else {
            lineBuffer <<  " ";
        }

    }
    lineBuffer << reset(color);
    lineBuffer << '\n';
    std::cout << lineBuffer.str();

}