#ifndef TILL_FILE_HPP
#define TILL_FILE_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>



// Structure got from https://www.fileformat.info/format/tiff/egff.htm
class TiffFile {
private:

    #pragma pack(push, 1)
    struct TiffHeader {
        uint16_t byteOrder;
        uint16_t version;
        uint32_t ifdOffset;
    } header;

    struct TiffEntry {
        uint16_t tag; // Type of information
        uint16_t type; // Type of data
        uint32_t count; // Number of values
        uint32_t valueOffset; // Value or offset to value
    };

    #pragma pack(pop)	

    struct TiffIFD {
        uint16_t entryCount;
        std::vector<TiffEntry> entries;
        uint32_t nextIFDOffset;
    };

    bool read();

    std::string filename;
    std::vector<TiffIFD> ifds;
    
public:

    TiffFile(std::string filename);
    
    

    void printEntries() const;

};


#endif