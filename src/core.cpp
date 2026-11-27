#include "core.hpp"
#include <cstdint>
#include <cstring>
#include <span>

uint64_t processDigits(uint64_t bytesProcessed) {
	uint64_t digits{};
	for (int i{}; i< 16 && bytesProcessed; i++) {
		digits++;
		bytesProcessed/=16;
	}
	return std::max<uint64_t>(8 , digits);
}

void processOffset(std::span<char> output, Config& config) {
	uint64_t& bytesProcessed = config.totalBytesProcessed;
	uint64_t digits = processDigits(bytesProcessed);
	for (uint64_t i{16 - digits}, start{}; i<16 ; i++, start++) {
		output[start] = hex[(bytesProcessed>>(64 - (i+1)*4)) & 0xF];
		config.bytesPrinted+=1;
	}
}

uint64_t processHexWall(std::span<char> output, std::span<char> blockChar) {
	uint64_t remaining = blockChar.size();
	uint64_t asciiWallStart = 8*5+1;
	uint64_t writeAt{};
	for (uint64_t i{}; i<remaining ; i++) {
		std::memcpy(output.data() + writeAt, hexPairs[static_cast<uint8_t>(blockChar[i])].data(), 2);
		writeAt+=2;

		if (i%2) output[writeAt++] = ' ';

		output[asciiWallStart + i] = wallChar[static_cast<uint8_t>(blockChar[i])];
		
	}
	output[asciiWallStart-1] = ' ';
	return asciiWallStart+remaining;
}

void processBuffer(Config& config) {
	config.bytesPrinted = 0;
	uint64_t blocks = static_cast<uint64_t>(config.bytesRead)/16;
	uint64_t remaining = static_cast<uint64_t>(config.bytesRead) % 16;

	config.outputBuffer.fill(0x00);


	for (uint64_t i{}; i<blocks; i++) {

		std::span<char> offset{config.outputBuffer.data()+config.bytesPrinted, 16};
		processOffset(offset, config);

		config.outputBuffer[config.bytesPrinted++] = ':';
		config.outputBuffer[config.bytesPrinted++] = ' ';

		std::span<char> blockChar{config.inputBuffer.data() + i*16, 16};
		std::span<char> hexWall{config.outputBuffer.data()+config.bytesPrinted, 57};
		config.bytesPrinted+= processHexWall(hexWall, blockChar);

		config.outputBuffer[config.bytesPrinted++] = '\n';
		config.totalBytesProcessed+=16;
	}
	if (remaining>0) {
		std::span<char> offset{config.outputBuffer.data()+config.bytesPrinted, 16};
		processOffset(offset, config);

		config.outputBuffer[config.bytesPrinted++] = ':';
		config.outputBuffer[config.bytesPrinted++] = ' ';

		std::span<char> blockChar{config.inputBuffer.data() + blocks*16, remaining};
		std::span<char> hexWall{config.outputBuffer.data()+config.bytesPrinted, 57};
		std::memset(hexWall.data(), ' ', 40+1);
		config.bytesPrinted+= processHexWall(hexWall, blockChar);

		config.outputBuffer[config.bytesPrinted++] = '\n';
		config.totalBytesProcessed+=remaining;
	}
}