#include "tiff_file.hpp"

TiffFile::TiffFile(std::string filename) : filename(filename) 
{
    if (!read()) {
        throw std::runtime_error("Error reading file");
    } 
}

bool TiffFile::read() {
    std::ifstream file(filename, std::ios::binary);

    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return false;
    }

    // Read the header
    file.read(reinterpret_cast<char*>(&header), sizeof(header));

    // Check if the file is a TIFF file
    if (header.byteOrder != 0x4949 && header.byteOrder != 0x4D4D) {
        throw std::runtime_error("Invalid TIFF file");
    }

    // Read the IFD (Image File Directory)
    file.seekg(header.ifdOffset, std::ios::beg);

    uint32_t nextIFDOffset = 0;
    do 
    {
        TiffIFD new_ifd;
        uint16_t entryCount;
        file.read(reinterpret_cast<char*>(&entryCount), sizeof(entryCount));
        new_ifd.entryCount = entryCount;
        std::vector<TiffEntry> entries;
        for (uint16_t i = 0; i < entryCount; ++i) {
            TiffEntry entry;
            file.read(reinterpret_cast<char*>(&entry), sizeof(entry));
            entries.push_back(entry);
        }
        new_ifd.entries = entries;
        file.read(reinterpret_cast<char*>(&nextIFDOffset), sizeof(nextIFDOffset));
        new_ifd.nextIFDOffset = nextIFDOffset;

        ifds.push_back(new_ifd);
    } while (nextIFDOffset != 0);

    file.close();
    return true;
}

void TiffFile::printEntries() const
{

}