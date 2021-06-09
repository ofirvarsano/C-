#ifndef MT_CYCLIC_QUEQUE_HPP
#define MT_CYCLIC_QUEQUE_HPP

#include "../../threads/semaphore.hpp"
#include "../../threads/mutex.hpp"

namespace experis {

class MTCyclicBlokingQueue {
public:
	typedef int ValueT;
    MTCyclicBlokingQueue(size_t a_size);
    ~MTCyclicBlokingQueue();

    void Enqueue(const ValueT& a_val);
    void Dequeue(ValueT& a_val);

private:
    MTCyclicBlokingQueue(const MTCyclicBlokingQueue&); // no copy
    MTCyclicBlokingQueue& operator=(const MTCyclicBlokingQueue&); // no copy

    ValueT* m_queue;
    Semaphore m_freeSpace;
    Semaphore m_occupiedSpace;
    Mutex m_queueLock;
    size_t m_size;
    size_t m_front;
    size_t m_back;
};

} //experis

#endif //MT_CYCLIC_QUEQUE_HPP
