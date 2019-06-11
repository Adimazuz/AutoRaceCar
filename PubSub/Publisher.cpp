#include "Publisher.h"

Publisher::Publisher() :
    _pubsub(PubSub::getInstance())
{

}

Publisher &Publisher::publish(const string &topic_name, Data *data)
{
    _pubsub.getInstance().updateAll(topic_name, data);

    return *this;
}
