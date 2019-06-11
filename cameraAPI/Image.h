#ifndef IMAGE_H
#define IMAGE_H

using uint = unsigned int;
using ullong = unsigned long long;

class Image
{
public:
    //TODO add bytes per pixel
    Image(const unsigned char *data, const uint &width, const uint &height, const ullong frame_num, const double timestamp_ms , const int bytes_per_pixel) :
        _data(data),
        _width(width),
        _height(height),
        _size(width * height),
        _frame_num(frame_num),
        _timestamp_ms(timestamp_ms),
        _bytes_per_pixel(bytes_per_pixel){}

    Image(const Image &other) :
        _data(other._data),
        _width(other._width),
        _height(other._height),
        _size(other._size),
        _frame_num(other._frame_num),
        _timestamp_ms(other._timestamp_ms),
        _bytes_per_pixel(other._bytes_per_pixel)
    {}

    Image(Image &&other) :
        _data(other._data),
        _width(other._width),
        _height(other._height),
        _size(other._size),
        _frame_num(other._frame_num),
        _timestamp_ms(other._timestamp_ms),
        _bytes_per_pixel(other._bytes_per_pixel)
    {
        other._data = nullptr;
        other._width = 0;
        other._height = 0;
        other._size = 0;
        other._frame_num = 0;
        other._timestamp_ms = 0;
        other._bytes_per_pixel = 0;
    }

    ~Image(){}

    const unsigned char* getData() const{
        return _data;
    }

    uint getWidth() const{
        return _width;
    }

    uint getHeight() const{
        return _height;
    }

    unsigned long getSize() const{
        return _size*_bytes_per_pixel;
    }

    ullong getFrameNum() const{
        return _frame_num;
    }

    double getTimestampMS() const{
        return _timestamp_ms;
    }

private:
    const unsigned char *_data;
    uint _width;
    uint _height;
    unsigned long _size;
    ullong _frame_num;
    double _timestamp_ms;
    int _bytes_per_pixel;
};


#endif // IMAGE_H
