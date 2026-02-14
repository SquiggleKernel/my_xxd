#include <iostream>
#include <fstream>
#include <iomanip>


int main(int argc ,char** argv) {

    // if (argc < 2) {
    //     std::cerr << "Usage: ./my_xxd <filename>\n";
    //     return 1;
    // }

    std::ifstream myFile(argv[argc-1] , std::ios::binary);


    if (!myFile.is_open()) {
        std::cerr << "file not open";
        return 1;
    }


    char rawchar{};
    int bytesTogether{2}, bytesPrinted{0} ;

    unsigned char charBuffer[16]{};
    int counter{0};


    std::cout <<std::setw(8)<<std::setfill('0') << bytesPrinted << ": "  ;

    while (myFile.get(rawchar)) {
        unsigned char ch {static_cast<unsigned char>(rawchar)};


        std::cout << std::hex << std::setw(2) << std::setfill('0')  <<  static_cast<int>(ch) ;
        if (ch >=32 && ch<=126) {
            charBuffer[counter] = ch;
        }
        else charBuffer[counter] = '.';
        counter++;
        bytesPrinted++;

        if (bytesPrinted%bytesTogether ==0) {
            std::cout << " ";
        }

        if (counter == 16 ) {
            std::cout << " ";
            for (unsigned char c : charBuffer) {
                std::cout << c;
            }
            std::cout << '\n' << std::setw(8)<<std::setfill('0') << bytesPrinted << ": "  ;
            counter = 0;
        }
    }
    if (counter) {
        for (int i{0} ; i < (16-counter)*2 + (16-counter)/(bytesTogether) +2 ; i++ ) {
            std::cout << " ";
        }
        for (int i{0} ; i < counter; i++) {
            std::cout << charBuffer[i];
        }
        std::cout << '\n';
    }

    myFile.close();

    return 0;
}