#include "xxdCore.h"
#include <iostream>
#include <fstream>
#include <iomanip>

int main(int argc ,char** argv) {

    if (argc < 2) {
        std::cerr << "Usage: ./my_xxd <filename>\n";
        return 1;
    }
    // opening input file in binary mode
    std::ifstream myFile(argv[argc-1] , std::ios::binary);

    if (!myFile.is_open()) {
        std::cerr << "[ERROR]: unable to open file";
        return 1;
    }



    int bytesPrinted{};
    // problem  is that i am taking char by char intput which is hell lot slower because of expensive system calls
    // lets define an buffer to get 4096bytes or 4KB of data at once saving us from expensive ssytem calls;

    const int bufferSize = 4096;
    char buffer[bufferSize]{};


    while(myFile){
        myFile.read(buffer, bufferSize);
        int bytesRead = static_cast<int>(myFile.gcount());


        if (bytesRead > 0) {
            processBuffer(&buffer[0] , bytesRead, & bytesPrinted);
        }

        if (myFile.eof())
            break;
    }

    myFile.close();

    return 0;
}