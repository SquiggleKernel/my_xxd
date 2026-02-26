//
// Created by amrit on 25/02/26.
//

#ifndef MY_XXD_XXDCORE_H
#define MY_XXD_XXDCORE_H



void formatToHex(char* buffer , int bytestoConvert, char* outputBuffer, int* bufferFilled, int bytesPrinted);
void processBuffer(char* buffer, int bytesRead, int* bytesPrinted);

void intToHex(char* line, int bytesPrinted);
void charToHex(char* buffer , int bytesToConvert, char* line);

void xxdAsciiWall(char* buffer, int bytesToConvert, char* line);

#endif //MY_XXD_XXDCORE_H