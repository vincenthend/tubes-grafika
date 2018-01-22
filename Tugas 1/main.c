#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "framebuffer.h"
#include "printer.h"

/** 
 * TODO:
 * 1. Scaling
 * 2. alignString
 * 
 * BUG:
 * 1. First character in every string seems to be cut in half (missing the top part)
*/

FrameBuffer fb;
char* cdict [255];

int main(){
    int x, y, i;
    printf("Initializing framebuffer\n");
    fb = initialize();
    printf("Framebuffer initialized\n");

    // char* font;
    // printf("Font type: ");
    // scanf("%s", font);
    initializeDictionary("archaic");

    char* in;
    printf("Input: ");
    scanf("%s", in);
    
    bufferString(&fb, in, 9, 11, 1500, 300, 1, 3, 255, 255, 255, 0);

    updateFrame(&fb);
    
    return 0;
}
