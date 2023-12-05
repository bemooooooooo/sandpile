#include "bmp.hpp"

Color::Color() {
    this->r = 0;
    this->b = 0;
    this->g = 0;
}

Color::Color(unsigned char r, unsigned char g, unsigned char b) {
    this->r = r;
    this->g = g;
    this->b = b;
}

Color::~Color() {
}

const Color kColorWhite = Color(255, 255, 255);
const Color kColorGreen = Color(0, 255, 0);
const Color kColorYellow = Color(255, 255, 0);
const Color kColorPurple = Color(102, 0, 153);
const Color kColorBlack = Color(0, 0, 0);

const int fileHeaderSize = 14;
const int infoHeaderSize = 40;
const int totalColors = 5;
const int bitsPerPixels = 4;
const int colorBites = 4;
const int colorPalleteSize = colorBites * totalColors;

void toImage(uint64_t** &mesh, uint16_t height, uint16_t width, std::string path) {
    std::ofstream f;
    f.open(path, std::ios::out | std::ios::binary);
 
    const uint16_t padding = (8 - (width % 8)) % 8;
    const uint64_t new_width = width + padding;

    const uint64_t fileSize = fileHeaderSize + infoHeaderSize + colorPalleteSize + (new_width * height) / 2;
    uint8_t fileHeader[fileHeaderSize] = {};
    uint8_t informationHeader[infoHeaderSize] = {};

    // File type
    fileHeader[0] = 'B';
    fileHeader[1] = 'M';
    // File size
    fileHeader[2] = fileSize;
    fileHeader[3] = fileSize >> 8;
    fileHeader[4] = fileSize >> 16;
    fileHeader[5] = fileSize >> 24;
    // Reserved 1 (Not used)
    fileHeader[6] = 0;
    fileHeader[7] = 0;
    // Reserved 2 (Not used)
    fileHeader[8] = 0;
    fileHeader[9] = 0;
    // Pixel data offset
    fileHeader[10] = fileHeaderSize + infoHeaderSize + colorPalleteSize;
    fileHeader[11] = 0;
    fileHeader[12] = 0;
    fileHeader[13] = 0;

    // Header size
    informationHeader[0] = infoHeaderSize;
    informationHeader[1] = 0;
    informationHeader[2] = 0;
    informationHeader[3] = 0;
    // Image width
    informationHeader[4] = width;
    informationHeader[5] = width >> 8;
    informationHeader[6] = width >> 16;
    informationHeader[7] = width >> 24;
    // Image height
    informationHeader[8] = height;
    informationHeader[9] = height >> 8;
    informationHeader[10] = height >> 16;
    informationHeader[11] = height >> 24;
    // Planes
    informationHeader[12] = 1;
    informationHeader[13] = 0;
    // Bits per pixel (RGB)
    informationHeader[14] = bitsPerPixels;
    informationHeader[15] = 0;
    // Total colors
    informationHeader[32] = totalColors;
    informationHeader[33] = 0;
    informationHeader[34] = 0;
    informationHeader[35] = 0;

    uint8_t colorPallete[colorPalleteSize] = {};
    //0 - White
    colorPallete[0] = kColorWhite.b;
    colorPallete[1] = kColorWhite.g;
    colorPallete[2] = kColorWhite.r;
    colorPallete[3] = 0;
    //1 - Green
    colorPallete[4] = kColorGreen.b;
    colorPallete[5] = kColorGreen.g;
    colorPallete[6] = kColorGreen.r;
    colorPallete[7] = 0;
    //2 - Yellow
    colorPallete[8] = kColorYellow.b;
    colorPallete[9] = kColorYellow.g;
    colorPallete[10] = kColorYellow.r;
    colorPallete[11] = 0;
    //3 - Purple
    colorPallete[12] = kColorPurple.b;
    colorPallete[13] = kColorPurple.g;
    colorPallete[14] = kColorPurple.r;
    colorPallete[15] = 0;
    //4 - Black
    colorPallete[16] = kColorBlack.b;
    colorPallete[17] = kColorBlack.g;
    colorPallete[18] = kColorBlack.r;
    colorPallete[19] = 0;

    f.write(reinterpret_cast<char*>(fileHeader), fileHeaderSize);
    f.write(reinterpret_cast<char*>(informationHeader), infoHeaderSize);
    f.write(reinterpret_cast<char*>(colorPallete), colorPalleteSize);

    uint64_t first_color, second_color;
    uint8_t total_color;
    for (int64_t x = height - 1; x >= 0; x--) {
        for (int64_t y = 0; y < new_width; y += 2) {
            if (y >= width) {
                first_color = 0;
                second_color = 0;
            }
            else if (y + 1 >= width) {
                first_color = mesh[x][y];
                second_color = 0;
            }
            else {
                first_color = mesh[x][y];
                second_color = mesh[x][y + 1];
            }

            if (first_color >= 4) {
                first_color = 4;
            }
            if (second_color >= 4) {
                second_color = 4;
            }

            total_color = (first_color << bitsPerPixels);
            total_color += second_color;

            f << total_color;
        }
    }
    f.close();
}
