#ifndef MT_CYCLIC_QUEQUE_INL_HPP
#define MT_CYCLIC_QUEQUE_INL_HPP

#include <assert.h>
#include "cyc_blking_queque.hpp"
#include "../../threads/semaphore_exceptions.hpp"
#include "../../threads/mutex_exceptions.hpp"

namespace experis {

MTCyclicBlokingQueue::MTCyclicBlokingQueue(size_t a_size)
: m_queue(new ValueT[a_size])
, m_freeSpace(a_size)
, m_occupiedSpace()
, m_queueLock()
, m_size(a_size)
, m_front(0)
, m_back(0) {
}

MTCyclicBlokingQueue::~MTCyclicBlokingQueue() {
    delete[] m_queue;
}

void MTCyclicBlokingQueue::Enqueue(const ValueT& a_val) {
    m_freeSpace.Acquire();
    try {
        m_queueLock.Lock();
    }
    catch(const std::exception &a_ex) {
        m_freeSpace.Release();
        throw;
    }

    m_queue[m_back] = a_val;
    m_back = (m_back + 1) % m_size;

    try {
        m_queueLock.UnLock();
    }
    catch(const std::exception &a_ex) {
        assert(!a_ex.what());
    }
    m_occupiedSpace.Release();
}

void MTCyclicBlokingQueue::Dequeue(ValueT& a_val) {
    m_occupiedSpace.Acquire();
    try {
        m_queueLock.Lock();
    }
    catch(const std::exception &a_ex) {
        m_occupiedSpace.Release();
        throw;
    }
    a_val = m_queue[m_front];
	m_front = (m_front + 1) % m_size;

    try {
        m_queueLock.UnLock();
    }
    catch(const std::exception &a_ex) {
        assert(!a_ex.what());
    }
    m_freeSpace.Release();
}

} //experis
#endif //MT_CYCLIC_QUEQUE_INL_HPP
