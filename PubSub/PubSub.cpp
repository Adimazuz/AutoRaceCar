#include "PubSub.h"

PubSub &PubSub::getInstance()
{
    static PubSub instance;

    return instance;
}

PubSub &PubSub::addSubscriber(const string &topic_name, Subscriber &subscriber)
{
    auto it = _topics.find(topic_name);
    std::shared_ptr<Topic> topic;

    if(it != _topics.end())
    {
        topic = _topics[topic_name];
    }
    else
    {
        topic = std::make_shared<Topic>();
        topic->name = topic_name;
        _topics.insert(std::pair<string, std::shared_ptr<Topic>>(topic_name, topic));
    }
    topic->subscribers.push_back(&subscriber);
    topic->threads.push_back(std::shared_ptr<std::thread>());
    *(topic->threads.end() - 1) = std::make_shared<std::thread>(&PubSub::sendSubscriberToListen,
                                                  this, topic, &subscriber);

    return *this;
}

PubSub &PubSub::updateAll(const string &topic_name, Data *data)
{
    auto topic = _topics[topic_name];

    for(auto &subscriber : topic->subscribers)
    {
        subscriber->setData(*data);
    }

    return *this;
}

PubSub::~PubSub()
{
    for(auto &pair : _topics)
    {
        for(auto &thread : pair.second->threads)
        {
            thread->join();
        }
    }
}

void PubSub::sendSubscriberToListen(std::shared_ptr<Topic> topic, Subscriber *subscriber)
{

//    std::lock_guard<std::mutex> lock_guard(topic->mutex);
//    std::lock_guard<std::mutex> lock_guard(topic->semaphore.getMutex());
    while(subscriber->isNotifyEnabled())
    {
//        topic->cv.wait(topic->mutex);
        topic->semaphore.wait();
        subscriber->update();
    }
}
