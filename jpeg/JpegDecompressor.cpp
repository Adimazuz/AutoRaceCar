#include "JpegDecompressor.h"

JpegDecompressor::JpegDecompressor() :
    _width(640),
    _height(480),
    _format(Format::GREY_SCALE),
    _output(nullptr),
    _handle()
{
    uint32 num_of_components = formatToInt(_format);
    _output = new uint8[_width * _height * num_of_components];
}

JpegDecompressor::JpegDecompressor(const uint32 &width, const uint32 &height,
                                   const JpegDecompressor::Format &format) :
    _width(width),
    _height(height),
    _format(format),
    _output(nullptr),
    _handle()
{
    uint32 num_of_components = formatToInt(_format);
    _output = new uint8[_width * _height * num_of_components];
}

JpegDecompressor &JpegDecompressor::setParams(const uint32 &width, const uint32 &height,
                                              const JpegDecompressor::Format &format)
{
    _width = width;
    _height = height;
    _format = format;

    delete[] _output;

    uint32 num_of_components = formatToInt(_format);
    _output = new uint8[_width * _height * num_of_components];

    return *this;
}

void JpegDecompressor::decompress(uint8 *input, const uint64 &compressed_size)
{
    _handle = tjInitDecompress();

    TJPF format = TJPF_RGB;
    if(_format == Format::GREY_SCALE)
    {
        format = TJPF_GRAY;
    }

    int width, height, jpegSubsamp;

    tjDecompressHeader2(_handle, input, compressed_size, &width, &height, &jpegSubsamp);
    tjDecompress2(_handle, input, compressed_size, _output, static_cast<int32>(_width), 0,
                  static_cast<int32>(_height), format, TJFLAG_FASTDCT);

    tjDestroy(_handle);
}

uint32 JpegDecompressor::formatToInt(const JpegDecompressor::Format &format)
{
    if(format == Format::RGB)
    {
        return 3;
    }
    else
    {
        return 1;
    }
}
