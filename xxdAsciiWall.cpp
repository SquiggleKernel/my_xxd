//
// Created by amrit on 26/02/26.
//
#include "xxdCore.h"


void xxdAsciiWall(char* buffer, int bytesToConvert, char* line) {
    char* end{&line[0]};
    for (int i{0} ; i <bytesToConvert ; i++ ) {
        if (buffer[i] >=32 && buffer[i] <= 126)
            end[0] = buffer[i];
        else
            end[0] = '.';
        end +=1;
    }
    for (int i{0} ; i <16- bytesToConvert ; i++ ) {
        end[0] = ' ';
        end +=1;
    }
}