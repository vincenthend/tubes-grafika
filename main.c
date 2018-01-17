#include <stdio.h>
#include "FrameBuffer.h"

FrameBuffer fb;

void printChar(char c, int x, int y){
    int i,j,cnt;

    //Nanti jadi array of string length 255 (ascii) jadi bisa cdict[(int)c]
    char cdict[99] = "000111000001111100011111110011000110011000110011000110011111110011111110011000110011000110011000110";

    for(i = 0; i<x+11; i++){
        for(j = 0; j<y+9; j++){
            if(cdict[i*11+j] == '1'){
                printPixel(&fb,x+i,y+j,255,255,255,0);
            }
        }
    }
}

int main(){
    int x, y;
    fb = initFB();
    
    printChar('a',200,200);
    
    finalizeChanges(&fb);
    
    return 0;
}
