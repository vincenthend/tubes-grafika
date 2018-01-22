#include "printer.h"

#include <string.h>

void initializeDictionary(char* font) {
    int i;
    for(i = 0; i<256; i++){
        cdict[i] = (char*)malloc(100);
    }
    
    int cidx = 'a';
    char font_filename[30];
    strcpy(font_filename, "fonts/");
    strcat(font_filename, font);
    strcat(font_filename, ".txt");

    FILE *font_file;
    font_file = fopen(font_filename, "r");
    if (font_file) {
        while ((fscanf(font_file, "%s", cdict[cidx]) == 1) && (cidx <= 'z')) {
            cidx++;
        }
        if (cidx == 'z'+1) {
            printf("Successfully loaded font %s\n", font);
        }
        else {
            printf("Error in reading font %s\n", font);
        }
        fclose(font_file);   
    }
    else {
        printf("Font does not exist\n");
        exit(5);
    }
}

void bufferChar(FrameBuffer* fb, char c, int char_width, int char_height, int x, int y, int scale, int r, int g, int b, int a) {
    int i, j;
    int scale_x_offset, scale_y_offset;
    char* dict = cdict[(int) c];
    for (i = 0; i < char_height; i++) {
        for (j = 0; j < char_width; j++) {
            if(dict[i*char_width+j] == '1') {
                addPixelToBuffer(fb, (x)+j, (y)+i, r, g, b, a);
            }
        }
    }
}

void bufferString(FrameBuffer* fb, char* s, int char_width, int char_height, int x, int y, int spacing, int scale, int r, int g, int b, int a) {
    int char_index = 0;
    int string_length = strlen(s);
    char c;
    int char_x = x;
    int char_y = y;
    for (char_index = 0; char_index < string_length; char_index++) {
        memcpy(&c, &s[char_index], 1);
        bufferChar(fb, c, char_width, char_height, char_x, char_y, scale, r, g, b, a);
        char_x += char_width + spacing;
        if (char_x > fb->screen_width - char_width) {
            char_x = x;
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