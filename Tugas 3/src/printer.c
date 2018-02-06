#include "printer.h"

/**
 * Menuliskan karakter pada x dan y tertentu
 */
void printChar(FrameBuffer *fb, char c, Font font, int x, int y, Color color) {
    char *dict = font.dict[(int)c];
    for (int i = 0; i < font.height; i++) {
        for (int j = 0; j < font.width; j++) {
            if (dict[i * font.width + j] == '1') {
                addPixelToBuffer(fb, (x) + j, (y) + i, color.r, color.g,
                                 color.b, color.a);
            }
            printf("%c", dict[i * font.width + j]);
        }
        printf("\n");
    }
}

/**
 * Menuliskan string pada x dan y tertentu
 */
void printString(FrameBuffer *fb, char *s, Font font, int x, int y,
                 Color color) {
    char c;
    int charX = x;
    int charY = y;
    for (int char_index = 0; char_index < strlen(s); char_index++) {
        memcpy(&c, &s[char_index], 1);
        printChar(fb, c, font, charX, charY, color);
        charX += font.width;
        if (charX > fb->screen_width - font.width) {
            charX = x;
            charY += font.height + 10;
        }
    }
}
