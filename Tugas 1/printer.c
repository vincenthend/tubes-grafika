#include "printer.h"

#include <string.h>

void bufferChar(FrameBuffer* fb, char* c, int char_width, int char_height, int x, int y, int scale, int r, int g, int b, int a) {
    int i, j;
    int scale_x_offset, scale_y_offset;
    for (i = 0; i < char_height; i++) {
        for (j = 0; j < char_width; j++) {
            if(c[i+(j*char_width)] == '1') {
                addPixelToBuffer(fb, (x)+i, (y)+j, r, g, b, a);
            }
        }
    }
}

void bufferString(FrameBuffer* fb, char* s, int char_width, int char_height, int x, int y, int spacing, int scale, int r, int g, int b, int a) {
    int char_index = 0;
    int string_length = strlen(s) / 99;
    char c[100];
    int char_x = x;
    int char_y = y;
    for (char_index = 0; char_index < string_length; char_index++) {
        memcpy(c, &s[99*char_index], 99);
        bufferChar(fb, c, char_width, char_height, char_x, char_y, scale, r, g, b, a);
        char_x += char_width + spacing;
        if (char_x > fb->screen_width - char_width) {
            char_y += char_height + 10;
        }
    }
}

void alignString(FrameBuffer* fb, char* c, int char_width, int char_height, int alignment, int y, int spacing, int scale, int r, int g, int b, int a) {
    /**
     * alignment
     * 1 = left
     * 2 = center
     * 3 = right
     * 4 = justified
     */ 

}