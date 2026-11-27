#include "core.hpp"
#include <ios>
#include <istream>
#include <system_error>
#include <fstream>
#include <iostream>

namespace fs = std::filesystem;

int main(int argc ,char** argv) {
    
    std::error_code ec{};
    Config config{};
    std::ifstream myFile{};


    if (argc == 2) {
            std::filesystem::path filePath = argv[1];


        if (!fs::exists(filePath, ec)) {
            if (ec) 
                std::cerr << "Error occured: "<< ec.message() << '\n';
            else 
                std::cerr << "File not found: " << filePath << '\n';
            return 1;
        }

        if (fs::is_directory(filePath, ec)) {
            std::cerr << "Error : Directory Found, Please enter path to a file\n";
            return 1;
        }else if (ec) {
            std::cerr << "Error occured: "<< ec.message() << '\n';
            return 1;
        }

        // opening input file in binary mode
        myFile.open(filePath, std::ios::binary);
        if (!myFile.is_open()) {
            std::cerr << "Error opening file\n";
            return 1;
        }
    }
    else if (argc > 2) {
        std::cerr << "Usage: ./my_xxd <filename>\n";
        return 1;
    }

    std::istream& input = (argc != 1) ? myFile : std::cin;

    while(input){
        input.read(config.inputBuffer.data(), inputBufferSize);
        config.bytesRead = input.gcount();

        if (input.bad()) {
            std::cerr << "\nError reading file\n";
            return 1;
        }


        if (config.bytesRead > 0) {
            processBuffer(config);
            std::cout.write(config.outputBuffer.data(), static_cast<std::streamsize>(config.bytesPrinted));
            if (std::cout.bad()) {
                std::cerr << "\nError occurred during I/O operation\n";
                return 1;
            }
        }

        if (input.eof())
            break;
    }

    return 0;
}