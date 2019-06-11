#include "Semaphore.h"

Semaphore::Semaphore(const uint &count) :
    _count(count)
{

}

Semaphore &Semaphore::notify()
{
    std::unique_lock<std::mutex> lock(_mutex);
    _count++;
    _cv.notify_one();

    return *this;
}

Semaphore &Semaphore::wait()
{
    std::unique_lock<std::mutex> lock(_mutex);
    while(_count == 0)
    {
        _cv.wait(_mutex);
    }
    _count--;

    return *this;
}

Semaphore &Semaphore::notifyAll(const uint &count)
{
    std::unique_lock<std::mutex> lock(_mutex);
    _count = count;
    _cv.notify_all();

    return *this;
}
