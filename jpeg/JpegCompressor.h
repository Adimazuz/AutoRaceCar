#ifndef JPEGCOMPRESSOR_H
#define JPEGCOMPRESSOR_H

#include "turbojpeg.h"

using uint32 = unsigned int;
using uint8 = unsigned char;
using uint64 = unsigned long;
using int32 = int;

class JpegCompressor
{
public:
    enum class Format
    {
        RGB,
        GREY_SCALE
    };

    JpegCompressor();
    JpegCompressor(const uint32 &width, const uint32 &height,
                   const JpegCompressor::Format &format, const uint32 &quality_percent);
    void setParams(const uint32 &width, const uint32 &height,
                   const JpegCompressor::Format &format, const uint32 &quality_percent);
    void compress(const uint8 *input);
    uint64 getCompressedSize() const {return _compressed_size;}
    uint8 *getOutput() {return _output;}
    ~JpegCompressor() {tjFree(_output);}

private: //methods
    uint32 formatToInt(const Format &format);

private: //members
    uint32 _width;
    uint32 _height;
    Format _format;
    uint32 _quality_percent;
    uint8 *_output;
    tjhandle _handle;
    uint64 _compressed_size;
};

#endif // JPEGCOMPRESSOR_H


