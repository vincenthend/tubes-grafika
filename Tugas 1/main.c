#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "framebuffer.h"
#include "drawer.h"
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

    // // char* font;
    // // printf("Font type: ");
    // // scanf("%s", font);
    // initializeDictionary("archaic");

    // char in[1000];
    // printf("Input: ");
    // scanf("%999[0-9a-zA-Z ]", in);
    // printf("%s",in);
    // bufferString(&fb, in, 9, 11, 1500, 300, 1, 3, 255, 255, 255, 0);

    drawLine(&fb, 400, 600, 400, 800, 255, 255, 255, 0);
    drawCircle(&fb, 400, 600, 200, 255, 255, 255, 0);

    for (i=1; i<=200; i++) {
        drawCircle(&fb, 800, 600, i, 255, 255, 255, 0);
    }

    updateFrame(&fb);
    
    return 0;
}
