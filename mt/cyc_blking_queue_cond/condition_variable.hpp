#ifndef CONDITION_VARIABLE_HPP
#define CONDITION_VARIABLE_HPP

#include "../../threads/semaphore.hpp"
#include "../../threads/mutex.hpp"
#include "../../threads/semaphore_exceptions.hpp"
#include "../../threads/mutex_exceptions.hpp"

namespace experis {

class ConditionVariable {
public:
    ConditionVariable();
    //~ConditionVariable = default;

    void Notify();
    void WaitToBeNotified(Mutex &a_lockedMutex);
private:
    ConditionVariable(const ConditionVariable&);
    ConditionVariable& operator=(const ConditionVariable&);

    Semaphore m_waitingSpace;
};

}//experis

#endif //CONDITION_VARIABLE_HPP
