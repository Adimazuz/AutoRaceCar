#ifndef PUBLISHER_H
#define PUBLISHER_H

#include "PubSub.h"
#include "Data.h"

class Publisher
{
public:
    Publisher();
    Publisher &publish(const string &topic_name, Data *data);

private:
    PubSub &_pubsub;
};

#endif // PUBLISHER_H
