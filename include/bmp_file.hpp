#ifndef BMP_FILE_HPP
#define BMP_FILE_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>

#include "color_map.hpp"


// Structure adapted from https://www.ece.ualberta.ca/~elliott/ee552/studentAppNotes/2003_w/misc/bmp_file_format/bmp_file_format.htm
// and https://en.wikipedia.org/wiki/BMP_file_format
// and https://stackoverflow.com/questions/2654480/writing-bmp-image-in-pure-c-c-without-other-libraries


enum type_compression {
    BI_RGB = 0, // No compression
    BI_RLE8 = 1, // 8-bit RLE encoding
    BI_RLE4 = 2, // 4-bit RLE encoding
};


#pragma pack(push, 1)

struct BMPHeader {
    uint16_t signature{0x4D42}; // File type always BM which is 0x4D42
    uint32_t fileSize{0};       // Size of the file (in bytes)
    uint32_t reserved{0};      // Reserved, always 0
    uint32_t offsetData{0};     // Start position of pixel data (bytes from the beginning of the file)
};

struct BMPInfoHeader {
    uint32_t size{40};          // Size of this header (in bytes)
    int32_t width{0};          // width of bitmap in pixels
    int32_t height{0};         // width of bitmap in pixels
                               // (if positive, bottom-up, with origin in lower left corner)
                               // (if negative, top-down, with origin in upper left corner)
    uint16_t planes{1};        // Number of planes for the target device, this is always 1
    uint16_t bitsPerPixel{0};  // Number of bits per pixel
    uint32_t compression{0};   // 0 or 3 - uncompressed. THIS PROGRAM CONSIDERS ONLY UNCOMPRESSED BMP images
    uint32_t sizeImage{0};     // 0 - for uncompressed images
    int32_t xPixelsPerMeter{0};
    int32_t yPixelsPerMeter{0};
    uint32_t colorsUsed{0};    // Number color indexes in the color table.
    uint32_t colorsImportant{0}; // Number of colors used for displaying the bitmap.
};

struct BMPColorTable {
    uint32_t redMask{0x00ff0000};         // Bit mask for the red channel
    uint32_t greenMask{0x0000ff00};       // Bit mask for the green channel
    uint32_t blueMask{0x000000ff};        // Bit mask for the blue channel
    uint32_t alphaMask{0xff000000};       // Bit mask for the alpha channel
    uint32_t colorSpaceType{0x73524742};  // Default "sRGB" (0x73524742)
    uint32_t unused[16]{0};               // Unused data for sRGB color space
};

#pragma pack(pop)


class BmpFile {
private:
    uint32_t rowStride{0};

    uint32_t makeStrideAligned(uint32_t alignStride);

public:
    BMPHeader fileHeader;
    BMPInfoHeader infoHeader;
    BMPColorTable colorHeader;
    std::vector<uint8_t> data;

    void read(const std::string &filename);

};


#endif