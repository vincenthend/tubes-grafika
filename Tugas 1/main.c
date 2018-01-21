#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "framebuffer.h"
#include "printer.h"

FrameBuffer fb;
char* cdict [255];

int main(){
    int x, y, i;
    fb = initialize();
    initializeDictionary();
    
    bufferString(&fb, "a", 9, 11, 200, 200, 1, 3, 255, 255, 255, 0);
    
    updateFrame(&fb);
    
    return 0;
}
