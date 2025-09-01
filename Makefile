CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O2
LDFLAGS = -lm
TARGET = ascii-art
SOURCES = ascii_art.c
OBJECTS = $(SOURCES:.c=.o)

.PHONY: all clean install

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)

install: $(TARGET)
	mkdir -p ~/.local/bin
	cp $(TARGET) ~/.local/bin/

test: $(TARGET)
	@echo "Testing ASCII art tool..."
	@if [ ! -f "test.png" ]; then \
		echo "No test image found. Please add a test.png file to test the tool."; \
	else \
		./$(TARGET) test.png; \
		echo "\nTesting with color:"; \
		./$(TARGET) -c test.png; \
	fi

help:
	@echo "Available targets:"
	@echo "  all     - Build the ASCII art tool"
	@echo "  clean   - Remove compiled files"
	@echo "  install - Install to ~/.local/bin"
	@echo "  test    - Run basic tests"
	@echo "  help    - Show this help message"