#include "core.hpp"
#include <system_error>
#include <fstream>
#include <iostream>

namespace fs = std::filesystem;

int main(int argc ,char** argv) {
    if (argc < 2) {
        std::cerr << "Usage: ./my_xxd <filename>\n";
        return 1;
    }

    std::error_code ec{};
    Config config{};
    config.file_path = argv[1];


    if (!fs::exists(config.file_path, ec)) {
        if (ec) 
            std::cerr << "Error occured: "<< ec.message() << '\n';
        else 
            std::cerr << "File not found: " << config.file_path << '\n';
        return 1;
    }

    if (fs::is_directory(config.file_path, ec)) {
        std::cerr << "Error : Directory Found, Please enter path to a file\n";
        return 1;
    }else if (ec) {
        std::cerr << "Error occured: "<< ec.message() << '\n';
        return 1;
    }

    // opening input file in binary mode
    std::ifstream myFile{};
    myFile.open(config.file_path, std::ios::binary);
    if (!myFile.is_open()) {
        std::cerr << "Error opening file\n";
        return 1;
    }


    while(myFile){
        myFile.read(config.inputBuffer.data(), inputBufferSize);
        config.bytesRead = myFile.gcount();

        if (config.bytesRead > 0) {
            //processBuffer(config);
        }
        if (myFile.bad()) {
            std::cerr << "\nError reading file\n";
            return 1;
        }

        if (myFile.eof())
            break;
    }

    myFile.close();
    return 0;
}