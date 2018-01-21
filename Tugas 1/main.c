#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "framebuffer.h"
#include "printer.h"

FrameBuffer fb;
char* cdict [255];

int main(){
    int x, y, i;
    printf("Initializing framebuffer\n");
    fb = initialize();
    printf("Framebuffer initialized\n");

    char* font;
    printf("Font type: ");
    scanf("%s", font);
    initializeDictionary(font);
    
    bufferString(&fb, "a", 9, 11, 200, 200, 1, 3, 255, 255, 255, 0);
    
    updateFrame(&fb);
    
    return 0;
}
