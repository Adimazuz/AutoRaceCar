#include "JpegCompressor.h"

JpegCompressor::JpegCompressor() :
    _width(960),
    _height(540),
    _format(Format::RGB),
    _quality_percent(100),
    _output(nullptr),
    _handle(),
    _compressed_size(0)
{

}

JpegCompressor::JpegCompressor(const uint32 &width, const uint32 &height,
                               const JpegCompressor::Format &format, const uint32 &quality_percent) :
    _width(width),
    _height(height),
    _format(format),
    _quality_percent(quality_percent),
    _output(nullptr),
    _compressed_size(0)
{

}

void JpegCompressor::setParams(const uint32 &width, const uint32 &height,
                               const JpegCompressor::Format &format, const uint32 &quality_percent)
{
    _width = width;
    _height = height;
    _format = format;
    _quality_percent = quality_percent;
}

void JpegCompressor::compress(const uint8 *input)
{
    tjFree(_output);
    _output = nullptr;
    _handle = tjInitCompress();

    TJPF format = TJPF_RGB;
    if(_format == Format::GREY_SCALE)
    {
        format = TJPF_GRAY;
    }

    tjCompress2(_handle, input, static_cast<int32>(_width), 0, static_cast<int32>(_height),
                format, &_output, &_compressed_size, TJSAMP_444,
                static_cast<int32>(_quality_percent), TJFLAG_FASTDCT);

    tjDestroy(_handle);
}

uint32 JpegCompressor::formatToInt(const JpegCompressor::Format &format)
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


//void compress(int quality, int width, int height, unsigned char *input, unsigned char **output,
//              unsigned long *compressed_size)
//{
//    tjhandle _jpegCompressor = tjInitCompress();

//    tjCompress2(_jpegCompressor, input, width, 0, height, TJPF_RGB,
//              output, compressed_size, TJSAMP_444, quality,
//              TJFLAG_FASTDCT);

//    tjDestroy(_jpegCompressor);
//}

//void decompress(unsigned char *input, unsigned char *output, unsigned long size, int width, int height)
//{
//    int jpegSubsamp;

//    tjhandle _jpegDecompressor = tjInitDecompress();

//    tjDecompressHeader2(_jpegDecompressor, input, size, &width, &height, &jpegSubsamp);

//    tjDecompress2(_jpegDecompressor, input, size, output, width, 0, height, TJPF_RGB, TJFLAG_FASTDCT);

//    tjDestroy(_jpegDecompressor);
//}
