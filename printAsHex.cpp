//
// Created by amrit on 14/02/26.
//

#include <iostream>
#include <fstream>
#include <iomanip>


//defining ANSI colors need only foreground colors.
[[maybe_unused]] const char* colorRed {"\033[1;91m"};
[[maybe_unused]] const char* colorGreen {"\033[1;92m"};
[[maybe_unused]] const char* colorYellow {"\033[1;93m"};
[[maybe_unused]] const char* colorBlue {"\033[1;94m"};
[[maybe_unused]] const char* colorWhite {"\033[1;97m"};
[[maybe_unused]] const char* defaultColor {"\033[0m"};

void printAsHex(unsigned char (&bufferArray)[16], int bytesPrinted, int bytesTogether , bool color);
const char* decideColor(bool color , unsigned char c);


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
void printAsHex(unsigned char (&bufferArray)[16], int bytesPrinted, int bytesTogether , bool color) {

    std::string colorState{}, colorTemp{};
    
    //defining stringstream as cout is becoming expensive
    std::stringstream lineBuffer{};

    if (color) {
        lineBuffer << colorWhite;
        colorState = colorWhite;
    }
    lineBuffer << std::hex << std::setw(8) << std::setfill('0') << bytesPrinted - 16 << ": " << std::flush;

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
        colorTemp = decideColor(color, bufferArray[i]);
        if (colorState != colorTemp) {
            lineBuffer << colorTemp;
            colorState = colorTemp;
        }
        lineBuffer << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(bufferArray[i]);

        counter++;
        if (counter%bytesTogether ==0)
            lineBuffer << ' ';
    }

    // print white spaces for case if say there are only 10 bytes instead of 16
    for (int i{0} ; i< hexWidth-counter*2-counter/bytesTogether ; ++i ) {
        lineBuffer << ' ';
    }
    lineBuffer << ' ' << std::dec;


    //printing the ascii wall
    for (int i{0} ; i< bytesToPrint ; ++i) {
        // non printable ascii characters

        colorTemp = decideColor(color, bufferArray[i]);
        if (colorState != colorTemp) {
            lineBuffer << colorTemp;
            colorState = colorTemp;
        }
        if (bufferArray[i]<=126 && bufferArray[i]>=32) {
            lineBuffer <<  bufferArray[i];
        }
        else
            lineBuffer << '.';

    }
    lineBuffer << reset(color);
    lineBuffer << '\n';
    std::cout << lineBuffer.str();

}