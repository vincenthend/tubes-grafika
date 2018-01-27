#include "font.h"

void openFont(char* font, Font* f){
    int i;
    for(i = 0; i<256; i++){
        (*f).dict[i] = (char*)malloc(100);
    }
    
    int cidx = 'a';
    char font_filename[30];
    strcpy(font_filename, "fonts/");
    strcat(font_filename, font);
    strcat(font_filename, ".txt");

    FILE *font_file;
    font_file = fopen(font_filename, "r");
    if (font_file) {
        fscanf(font_file, "%d", &((*f).width));
        fscanf(font_file, "%d", &((*f).height));
        while ((fscanf(font_file, "%s", (*f).dict[cidx]) == 1) && (cidx <= 'z')) {
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