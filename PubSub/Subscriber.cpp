#include "Subscriber.h"

Subscriber::Subscriber() :
    _data(nullptr),
    _is_notify_enabled(true)
{

}

Subscriber &Subscriber::setData(Data &new_data)
{
    _data = &new_data;

    return *this;
}
