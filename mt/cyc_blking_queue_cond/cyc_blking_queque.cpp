#include <assert.h>
#include "cyc_blking_queque.hpp"
#include "../../threads/semaphore_exceptions.hpp"
#include "../../threads/mutex_exceptions.hpp"

namespace experis {

MTCyclicBlokingQueue::MTCyclicBlokingQueue(size_t a_size)
: m_queue(new ValueT[a_size])
, m_enqWaiting()
, m_deqWaiting()
, m_queueLock()
, m_size(a_size)
, m_front(0)
, m_back(0) 
, m_freeSpace(a_size)
{}

MTCyclicBlokingQueue::~MTCyclicBlokingQueue() {
    delete[] m_queue;
}

void MTCyclicBlokingQueue::Enqueue(const ValueT& a_val) {
	try {
        m_queueLock.Lock();
    }
    catch(const std::exception &a_ex) {
        assert(!a_ex.what());
    }
    while(m_freeSpace <= 0) {
        m_enqWaiting.WaitToBeNotified(m_queueLock);
    }
    try{
        m_queue[m_back] = a_val;
        m_back = (m_back + 1) % m_size;
        --m_freeSpace;
    }
    catch(...) {
        try {
            m_queueLock.UnLock();
        }
        catch(const std::exception &a_ex) {
            throw;
        }
    }
    try {
        m_queueLock.UnLock();
    }
    catch(const std::exception &a_ex) {
        assert(!a_ex.what());
    }
    m_deqWaiting.Notify();
}

void MTCyclicBlokingQueue::Dequeue(ValueT& a_val) {
	try {
        m_queueLock.Lock();
    }
    catch(const std::exception &a_ex) {
        assert(!a_ex.what());
    }
    while(m_freeSpace == m_size) {
        m_deqWaiting.WaitToBeNotified(m_queueLock);
    }
    try {
        a_val = m_queue[m_front];
        m_front = (m_front + 1) % m_size;
        ++m_freeSpace;
    }
    catch(...) {
        try {
            m_queueLock.UnLock();
        }
        catch(const std::exception &a_ex) {
            assert(!a_ex.what());
        }
        throw;
    }
    try {
        m_queueLock.UnLock();
    }
    catch(const std::exception &a_ex) {
        assert(!a_ex.what());
    }
    m_enqWaiting.Notify();
}

} //experis
