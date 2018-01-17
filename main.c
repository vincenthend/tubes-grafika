#include <stdio.h>
#include <stdlib.h>
#include "FrameBuffer.h"

FrameBuffer fb;
char* cdict[255];

void printChar(char c, int x, int y){
    int i,j,cnt;

    char* dict = cdict[(int)c];
    for(i = 0; i<=9; i++){
        for(j = 0; j<=11; j++){
            if(dict[i+(j*9)] == '1'){
                printPixel(&fb,x+i,y+j,255,255,255,0);
            }
        }
    }
}

int main(){
    int x, y, i;
    fb = initFB();
    
    //Initialize dictionary
    for(i = 0; i<256; i++){
        cdict[i] = (char*)malloc(100);
    }
    cdict['a'] = "000111000001111100011111110011000110011000110011000110011111110011111110011000110011000110011000110";
    cdict['b'] = "011111000011111100011001110011000110011001110011111100011111100011000110011000110011001110011111100";
    cdict['c'] = "000111000001111100011100110011000010011000000011000000011000000011000010011100110001111100000111000";
    
    // Ukuran huruf : lebar 9, tinggi 11, jarak antar huruf ?
    printChar('a',200,200);
    printChar('b',209,200);
    printChar('c',218,200);
    
    finalizeChanges(&fb);
    
    return 0;
}
