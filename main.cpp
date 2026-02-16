#include <iostream>
#include <fstream>
#include <iomanip>
#include <chrono>

// break it into funcitons
// functions to take 16 bytes as input from file and convert them to unsigned then return the array


void printAsHex(unsigned char (&bufferArray)[16], int bytesPrinted, int bytesTogether , bool color);

int main(int argc ,char** argv) {


    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    if (argc < 2) {
        std::cerr << "Usage: ./my_xxd <filename>\n";
        return 1;
    }

    std::ifstream myFile(argv[argc-1] , std::ios::binary);

    if (!myFile.is_open()) {
        std::cerr << "[ERROR]: unable to open file";
        return 1;
    }



    bool color {false};
    char rawchar{};
    int bytesTogether{2}, bytesPrinted{0} ;

    unsigned char charBuffer[16]{};
    int counter{0};

    while (myFile.get(rawchar)) {
        unsigned char ch {static_cast<unsigned char>(rawchar)};

        charBuffer[counter] = ch;

        bytesPrinted++;
        counter ++;
        if (counter == 16) {
            printAsHex(charBuffer, bytesPrinted, bytesTogether, color);
            counter = 0;
        }
    }
    if (counter) {
        printAsHex(charBuffer, bytesPrinted, bytesTogether, color);
    }

    myFile.close();

    return 0;
}