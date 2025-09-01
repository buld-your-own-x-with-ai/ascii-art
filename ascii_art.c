#define STB_IMAGE_IMPLEMENTATION
#include "ascii_art.h"
#include <string.h>
#include <unistd.h>

Image* load_image(const char* filename) {
    Image* img = malloc(sizeof(Image));
    if (!img) {
        fprintf(stderr, "Error: Failed to allocate memory for image\n");
        return NULL;
    }
    
    img->data = stbi_load(filename, &img->width, &img->height, &img->channels, 3);
    if (!img->data) {
        fprintf(stderr, "Error: Failed to load image %s\n", filename);
        free(img);
        return NULL;
    }
    
    img->channels = 3;
    return img;
}

void free_image(Image* img) {
    if (img) {
        if (img->data) {
            stbi_image_free(img->data);
        }
        free(img);
    }
}

void print_colored_char(char c, uint8_t r, uint8_t g, uint8_t b) {
    printf("\033[38;2;%d;%d;%dm%c", r, g, b, c);
}

void image_to_ascii(Image* img, Config* config) {
    int target_width = config->width > 0 ? config->width : 80;
    int target_height = (img->height * target_width) / (img->width * 2);
    
    for (int y = 0; y < target_height; y++) {
        for (int x = 0; x < target_width; x++) {
            int img_x = (x * img->width) / target_width;
            int img_y = (y * img->height) / target_height;
            
            if (img_x >= img->width) img_x = img->width - 1;
            if (img_y >= img->height) img_y = img->height - 1;
            
            int pixel_idx = (img_y * img->width + img_x) * 3;
            uint8_t r = img->data[pixel_idx];
            uint8_t g = img->data[pixel_idx + 1];
            uint8_t b = img->data[pixel_idx + 2];
            
            int gray = (r + g + b) / 3;
            int ascii_idx = (gray * (ascii_chars_len - 1)) / 255;
            char ascii_char = ascii_chars[ascii_idx];
            
            if (config->enable_color) {
                print_colored_char(ascii_char, r, g, b);
            } else {
                printf("%c", ascii_char);
            }
        }
        printf("\n");
    }
    
    if (config->enable_color) {
        printf("\033[0m");
    }
}

void print_usage(const char* program_name) {
    printf("Usage: %s [OPTIONS] <image_file>\n", program_name);
    printf("Convert an image to ASCII art\n\n");
    printf("Options:\n");
    printf("  -c, --color    Enable colored ASCII output\n");
    printf("  -w, --width N  Set output width (default: 80)\n");
    printf("  -h, --help     Show this help message\n");
    printf("\nSupported formats: JPEG, PNG, BMP, TGA, PSD, GIF, HDR, PIC\n");
}

int parse_args(int argc, char* argv[], Config* config) {
    config->enable_color = 0;
    config->width = 80;
    config->input_file = NULL;
    
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-c") == 0 || strcmp(argv[i], "--color") == 0) {
            config->enable_color = 1;
        } else if (strcmp(argv[i], "-w") == 0 || strcmp(argv[i], "--width") == 0) {
            if (i + 1 < argc) {
                config->width = atoi(argv[++i]);
                if (config->width <= 0) {
                    fprintf(stderr, "Error: Width must be a positive integer\n");
                    return -1;
                }
            } else {
                fprintf(stderr, "Error: -w/--width requires an argument\n");
                return -1;
            }
        } else if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            return -2;
        } else if (argv[i][0] != '-') {
            if (config->input_file == NULL) {
                config->input_file = argv[i];
            } else {
                fprintf(stderr, "Error: Multiple input files specified\n");
                return -1;
            }
        } else {
            fprintf(stderr, "Error: Unknown option %s\n", argv[i]);
            return -1;
        }
    }
    
    if (config->input_file == NULL) {
        fprintf(stderr, "Error: No input file specified\n");
        return -1;
    }
    
    return 0;
}

int main(int argc, char* argv[]) {
    Config config;
    int parse_result = parse_args(argc, argv, &config);
    
    if (parse_result == -2) {
        print_usage(argv[0]);
        return 0;
    }
    
    if (parse_result != 0) {
        print_usage(argv[0]);
        return 1;
    }
    
    if (access(config.input_file, F_OK) != 0) {
        fprintf(stderr, "Error: File '%s' does not exist\n", config.input_file);
        return 1;
    }
    
    Image* img = load_image(config.input_file);
    if (!img) {
        return 1;
    }
    
    image_to_ascii(img, &config);
    free_image(img);
    
    return 0;
}