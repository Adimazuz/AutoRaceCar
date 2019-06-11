#include <iostream>
#include <signal.h>

#include "PubSub.h"
#include "Subscriber.h"
#include "Publisher.h"

std::mutex mu;

void handle(int a)
{
    std::cout << "bye bye" << std::endl;
    exit(0);
}

class Manager1 : public Subscriber
{
public:
    Manager1() = default;
    virtual Subscriber &update() override
    {
        std::lock_guard<std::mutex> m(mu);
        std::cout << "manager1 is now printing be ready" << std::endl;

        return *this;
    }
};

class Manager2 : public Subscriber
{
public:
    Manager2() = default;
    virtual Subscriber &update() override
    {
        std::lock_guard<std::mutex> m(mu);
        std::cout << "manager2 is now printing be ready" << std::endl;

        return *this;
    }
};

class Data1 : public Data
{
public:
    Data1() = default;
};

class Data2 : public Data
{
public:
    Data2() = default;
};

class Publisher1 : public Publisher
{
public:
    Publisher1() = default;
};

class Publisher2 : public Publisher
{
public:
    Publisher2() = default;
};

int main()
{
    signal(SIGINT, &handle);

    auto &pubsub = PubSub::getInstance();

    uint num = 2;

    Manager1 m[num];
    Publisher1 p[num];

    for(uint i = 0; i < num; i++)
    {
        pubsub.addSubscriber("asaf", m[i]);
    }

//    std::thread t1([&p1, &d1]()
//    {
//        while(true)
//        {
//            p1.publish("asaf", &d1);
//        }
//    });

//    std::thread t2([&p2, &d2]()
//    {
//        while(true)
//        {
//            p2.publish("narkis", &d2);
//        }
//    });

    while(true)
    {
        auto ch = getchar();
        if(ch == 's')
        {
            for(uint i = 0; i < num; i++)
            {
                m[i].setNotifyEnabled(false);
            }
            PubSub::getInstance()._topics["asaf"]->semaphore.notifyAll(num);
        }
        if(ch == 'q')
        {
            goto label;
        }
    }
    label:

    return 0;
}
