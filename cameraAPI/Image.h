#ifndef IMAGE_H
#define IMAGE_H

using uint = unsigned int;

class Image
{
public:
    Image(char *data, const uint &width, const uint &height) :
        _data(data),
        _width(width),
        _height(height),
        _size(width * height) {}

    Image(const Image &other) :
        _data(other._data),
        _width(other._width),
        _height(other._height),
        _size(other._size)
    {}

    Image(Image &&other) :
        _data(other._data),
        _width(other._width),
        _height(other._height),
        _size(other._size)
    {
        other._data = nullptr;
        other._width = 0;
        other._height = 0;
        other._size = 0;
    }

    ~Image(){}

    char* getDate(){
        return _data;
    }

    uint getWidth(){
        return _width;
    }

    uint getHeight(){
        return _height;
    }

    uint getSize(){
        return _size;
    }


private:
    char *_data;
    uint _width;
    uint _height;
    uint _size;
};


#endif // IMAGE_H
