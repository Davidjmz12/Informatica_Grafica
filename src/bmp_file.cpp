
#include "bmp_file.hpp"

void BmpFile::read(const std::string &filename) {
        // Read the BMP file header
        std::ifstream inputFile{filename, std::ios_base::binary};
        if (inputFile) {
            // Read the file header
            inputFile.read((char*)&fileHeader, sizeof(fileHeader));
            if(fileHeader.signature != 0x4D42) {
                throw std::runtime_error("Unrecognized file format.");
            }

            // Read the info header
            inputFile.read((char*)&infoHeader, sizeof(infoHeader));

            inputFile.read((char*)&colorHeader, sizeof(colorHeader));

            // Jump to the pixel data location
            inputFile.seekg(fileHeader.offsetData, inputFile.beg);

            int data_size = infoHeader.width * infoHeader.height;
            int bits_per_pixel = infoHeader.bitsPerPixel/8;

            std::vector<uint8_t> fileData(data_size * bits_per_pixel);

            inputFile.read((char*)fileData.data(), fileData.size());

            std::vector<std::vector<Color>> data;

            for(unsigned int i=0;i<infoHeader.height;i++)
            {
                std::vector<Color> row;
                for(unsigned int j=0;j<infoHeader.width;j++)
                {
                    float r,g,b;
                    b = (float)fileData[i*infoHeader.width*bits_per_pixel + j*bits_per_pixel];
                    g = (float)fileData[i*infoHeader.width*bits_per_pixel + j*bits_per_pixel + 1];
                    r = (float)fileData[i*infoHeader.width*bits_per_pixel + j*bits_per_pixel + 2];
                    row.push_back(Color({r,g,b},Color::same_range(255),RGB));
                }
                data.push_back(row);
            }
            
            ColorMap cmap(data,RGB);
            std::cout << cmap << std::endl;

        } else {
            throw std::runtime_error("Unable to open the input image file.");
        }
    }

uint32_t BmpFile::makeStrideAligned(uint32_t alignStride) {
        uint32_t newStride = rowStride;
        while (newStride % alignStride != 0) {
            newStride++;
        }
        return newStride;
    }