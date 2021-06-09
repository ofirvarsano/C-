#ifndef MUTEX_HPP
#define MUTEX_HPP

#include <pthread.h>

namespace experis {

class Mutex {
public:
    Mutex();
    ~Mutex();

    void Lock();
    void UnLock();
private:
    Mutex(const Mutex&); //no copy
    Mutex& operator=(const Mutex&); //no copy

    pthread_mutex_t m_mutex;
};

} //experis

#endif //MUTEX_HPP
