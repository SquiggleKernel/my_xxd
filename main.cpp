#include <iostream>
#include <fstream>
#include <iomanip>

// break it into funcitons
// functions to take 16 bytes as input from file and convert them to unsigned then return the array


void printAsHex( char* bufferArray, int bytesToRead ,int bytesPrinted, int bytesTogether , bool color);
void processBuffer(char* buffer, int bytesRead, int* bytesPrinted, int bytesTogether, bool color);

int main(int argc ,char** argv) {


    // 1. Create a large buffer (e.g., 64 KB)
    const int BUF_SIZE = 65536;
    static char b[BUF_SIZE];

    // 2. Tell cout to use this buffer instead of its internal one
    std::cout.rdbuf()->pubsetbuf(b, BUF_SIZE);

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
    int bytesTogether{2}, bytesPrinted{0} ;

    // problem  is that i am taking char by char intput which is hell lot slower because of expensive system calls
    // lets define an buffer to get 4096bytes 4KB of data at once saving us from expensive ssytem calls;

    const int bufferSize = 4096;
    char buffer[bufferSize]{};


    while(myFile){
        myFile.read(buffer, bufferSize);
        int bytesRead = static_cast<int>(myFile.gcount());


        if (bytesRead > 0) {
            processBuffer(&buffer[0] , bytesRead, & bytesPrinted, bytesTogether, color);
        }

        if (myFile.eof())
            break;
    }

    myFile.close();

    return 0;
}