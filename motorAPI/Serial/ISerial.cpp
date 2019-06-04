#include "Serial.h"

std::shared_ptr<ISerial> ISerial::create()
{
    return std::make_shared<Serial>();
}
