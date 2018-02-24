#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "color.h"
#include "drawer.h"
#include "font.h"
#include "framebuffer.h"
#include "printer.h"

/**
 * BUG:
 * 1. Characters missing the bottom part
*/

FrameBuffer fb;
char *cdict[255];

int main() {
    printf("Initializing framebuffer\n");
    fb = initialize();
    printf("Framebuffer initialized\n");

    Font f;
    Color c;

    openFont("archaic", &f);
    c.r = 255;
    c.g = 255;
    c.b = 255;
    c.a = 0;

    char in[1000];
    printf("Input: ");
    scanf("%999[0-9a-zA-Z ]", in);
    printString(&fb, in, f, 200, 200, c);

    updateFrame(&fb);
    return 0;
}
