# ASCII Art Generator

A command-line tool written in C that converts images to ASCII art for terminal display.

## Features

- Convert various image formats (JPEG, PNG, BMP, TGA, PSD, GIF, HDR, PIC) to ASCII art
- Optional colored ASCII output using ANSI escape codes
- Customizable output width
- Lightweight and fast

## Installation

### Prerequisites

- GCC compiler
- Make

### Build from source

```bash
git clone <repository-url>
cd ascii-art
make
```

### Install system-wide (optional)

```bash
make install
```

This will install the binary to `~/.local/bin/ascii-art`. Make sure `~/.local/bin` is in your PATH.

## Usage

### Basic usage

```bash
./ascii-art image.jpg
```

### Options

```bash
./ascii-art [OPTIONS] <image_file>
```

Available options:

- `-c, --color`: Enable colored ASCII output
- `-w, --width N`: Set output width in characters (default: 80)
- `-h, --help`: Show help message

### Examples

```bash
# Convert image to ASCII art with default width (80 characters)
./ascii-art photo.jpg

# Convert with colored output
./ascii-art -c photo.jpg

# Convert with custom width
./ascii-art -w 120 photo.jpg

# Combine options
./ascii-art -c -w 100 photo.jpg
```

## Supported Formats

- JPEG (.jpg, .jpeg)
- PNG (.png)
- BMP (.bmp)
- TGA (.tga)
- PSD (.psd)
- GIF (.gif)
- HDR (.hdr)
- PIC (.pic)

## How it works

1. The tool loads the input image using the stb_image library
2. Resizes the image to fit the specified width while maintaining aspect ratio
3. Converts each pixel to grayscale
4. Maps grayscale values to ASCII characters: ` .:-=+*#%@`
5. Optionally applies ANSI color codes for colored output

## Dependencies

- [stb_image](https://github.com/nothings/stb) - Single-file image loading library (included)

## Building

The project uses a simple Makefile:

```bash
# Build the project
make

# Clean build artifacts
make clean

# Run tests (requires test.png)
make test

# Show help
make help
```

## License

This project is licensed under the terms specified in the LICENSE file.
