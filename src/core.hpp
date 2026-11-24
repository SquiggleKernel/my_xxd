#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <filesystem>
#include <ios>


constexpr std::size_t inputBufferSize = 4096;


struct Config{
    std::filesystem::path file_path{};
    std::uint64_t bytesPrinted{};
    std::streamsize bytesRead{};
    std::array<char, inputBufferSize> inputBuffer{};
};