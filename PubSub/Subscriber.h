#ifndef SUBSCRIBER_H
#define SUBSCRIBER_H

#include <memory>
#include <mutex>
#include <condition_variable>

#include "Data.h"

class Subscriber
{
public:

    Subscriber();
    Subscriber &setData(Data &new_data);
    virtual Subscriber &update() = 0;
    bool isNotifyEnabled() const {return _is_notify_enabled;}
    Subscriber &setNotifyEnabled(const bool &new_val) {_is_notify_enabled = new_val; return *this;}
    virtual ~Subscriber() = default;

private:
    Data *_data;
    bool _is_notify_enabled;
};

#endif // SUBSCRIBER_H
