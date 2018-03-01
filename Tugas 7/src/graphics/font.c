#include "font.h"

void openFont(char *ch, Font *font) {
    for (int i = 0; i < 256; i++) {
        font->dict[i] = (char *)malloc(100);
    }

    int c = 'a';
    char filename[30];
    strcpy(filename, "data/fonts/");
    strcat(filename, ch);
    strcat(filename, ".txt");

    FILE *file;
    file = fopen(filename, "r");
    if (file) {
        fscanf(file, "%d", &(font->width));
        fscanf(file, "%d", &(font->height));
        while ((fscanf(file, "%s", font->dict[c]) == 1) && (c <= 'z')) {
            c++;
        }

        if (c == 'z' + 1) {
            printf("Successfully loaded font %s\n", ch);
        } else {
            printf("Error in reading font %s\n", ch);
        }
        fclose(file);
    } else {
        printf("Font does not exist\n");
        exit(5);
    }
}
