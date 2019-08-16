#ifndef IMAGE_H
#define IMAGE_H

#include <vector>

#include "RemoteControl_types.h"

class Image
{
public:
    Image()
    {

    }

private:
    ImageMetaData _metadata;
    std::vector<uint8> _data;
};

#endif // IMAGE_H
