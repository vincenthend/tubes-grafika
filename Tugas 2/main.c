#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "framebuffer.h"
#include "drawer.h"
#include "printer.h"
#include "font.h"
#include "color.h"

/** 
 * 
 * BUG:
 * 1. Characters missing the bottom part
*/

FrameBuffer fb;
char* cdict [255];

int main(){
    int x, y, i;
    printf("Initializing framebuffer\n");
    fb = initialize();
    printf("Framebuffer initialized\n");

    Color c;
    initColor(&c, "FFFFFF");

    drawSquare(&fb, fb.screen_width-500, fb.screen_height-300,fb.screen_width-10, fb.screen_height-10, c);

    updateFrame(&fb);
    return 0;
}
