#ifndef ASCII_ART_H
#define ASCII_ART_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "stb_image.h"

typedef struct {
    int width;
    int height;
    int channels;
    unsigned char *data;
} Image;

typedef struct {
    int enable_color;
    int width;
    char *input_file;
} Config;

const char ascii_chars[] = " .:-=+*#%@";
const int ascii_chars_len = 10;

Image* load_image(const char* filename);
void free_image(Image* img);
void image_to_ascii(Image* img, Config* config);
void print_colored_char(char c, uint8_t r, uint8_t g, uint8_t b);
void print_usage(const char* program_name);
int parse_args(int argc, char* argv[], Config* config);

#endif