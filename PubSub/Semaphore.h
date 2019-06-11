#ifndef SEMAPHORE_H
#define SEMAPHORE_H

#include <mutex>
#include <condition_variable>

using uint = unsigned int;

class Semaphore
{
public:
    explicit Semaphore(const uint &count = 0);
    Semaphore &notify();
    Semaphore &wait();
    Semaphore &notifyAll(const uint &count);
    std::mutex &getMutex() {return _mutex;}

private:
    std::mutex _mutex;
    std::condition_variable_any _cv;
    uint _count;
};

#endif // SEMAPHORE_H
