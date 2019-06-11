#ifndef PUBSUB_H
#define PUBSUB_H

#include <string>
#include <map>
#include <memory>
#include <thread>
#include <vector>
#include <mutex>
#include <condition_variable>

#include "Subscriber.h"
#include "Semaphore.h"

using string = std::string;

class PubSub
{
public:  
    PubSub(const PubSub &pubsub) = delete;
    PubSub operator=(PubSub &pubsub) = delete;
    static PubSub &getInstance();
    PubSub &addSubscriber(const string &topic_name, Subscriber &subscriber);
    PubSub &updateAll(const string &topic_name, Data *data);
    ~PubSub();

private: //structs

    struct Topic
    {
        string name;
        std::mutex mutex;
        std::condition_variable_any cv;
        std::vector<std::shared_ptr<std::thread>> threads;
        std::vector<Subscriber*> subscribers;
        Semaphore semaphore;
    };

private: //methods
    PubSub() = default;
    void sendSubscriberToListen(std::shared_ptr<Topic> topic, Subscriber *subscriber);

public: //members

    std::map<string, std::shared_ptr<Topic>> _topics;
};

#endif // PUBSUB_H
