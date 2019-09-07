#ifndef JPEGDECOMPRESSOR_H
#define JPEGDECOMPRESSOR_H

#include "turbojpeg.h"

using uint32 = unsigned int;
using uint8 = unsigned char;
using uint64 = unsigned long;
using int32 = int;

class JpegDecompressor
{
public:

    enum class Format
    {
        RGB,
        GREY_SCALE
    };

    JpegDecompressor();
    JpegDecompressor(const uint32 &width, const uint32 &height,
                     const JpegDecompressor::Format &format);
    JpegDecompressor &setParams(const uint32 &width, const uint32 &height, const JpegDecompressor::Format &format);
    void decompress(uint8 *input, const uint64 &compressed_size);
    int32 getBytesPerPixel();
    uint8 *getOutput() {return _output;}
    ~JpegDecompressor() {delete[] _output;}

private: //methods
    uint32 formatToInt(const Format &format);

private: //members
    uint32 _width;
    uint32 _height;
    Format _format;
    uint8 *_output;
    tjhandle _handle;
};

#endif // JPEGDECOMPRESSOR_H
