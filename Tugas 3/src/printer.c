#include "printer.h"

/**
 * Menuliskan karakter pada x dan y tertentu
 */
void printChar(FrameBuffer *fb, char c, Font f, int x, int y, Color color) {
    char *dict = f.dict[(int)c];
    for (int i = 0; i < f.height; i++) {
        for (int j = 0; j < f.width; j++) {
            if (dict[i * f.width + j] == '1') {
                addPixelToBuffer(fb, (x) + j, (y) + i, color.r, color.g,
                                 color.b, color.a);
            }
            printf("%c", dict[i * f.width + j]);
        }
        printf("\n");
    }
}

/**
 * Menuliskan string pada x dan y tertentu
 */
void printString(FrameBuffer *fb, char *s, Font f, int x, int y, Color color) {
    int string_length = strlen(s);
    char c;
    int char_x = x;
    int char_y = y;
    for (int char_index = 0; char_index < string_length; char_index++) {
        memcpy(&c, &s[char_index], 1);
        printChar(fb, c, f, char_x, char_y, color);
        char_x += f.width;
        if (char_x > fb->screen_width - f.width) {
            char_x = x;
            char_y += f.height + 10;
        }
    }
}
