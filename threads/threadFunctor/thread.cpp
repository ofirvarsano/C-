#include <errno.h>
#include <assert.h>
#include <stdexcept>
#include <unistd.h>

#include "thread.hpp"
#include "thread_exceptions.hpp"

namespace advcpp {

void* Thread::Start(void* a_func) {
    ((Runnable*)a_func)->Do();
    return NULL;
}

Thread::Thread(Runnable& a_func)
: m_joinable(true)
{
    const int TRIES = 3;
	int sleepTimeUs = 80;
	for(int i = 0; i < TRIES; ++i) {
		int result = pthread_create(&m_thread, 0, Start, &a_func);
	    switch(result) {
	    	case 0:
	    		return;
			case EINVAL:
			case EPERM:
				assert(!"pthread_create failed");
				break;
			case EAGAIN:
				SleepMicroSeconds(sleepTimeUs);
				sleepTimeUs = sleepTimeUs * sleepTimeUs;
				break;
    	}
	}
	throw ThreadLackResourcesException();
}

Thread::~Thread()
{
	if(m_joinable) {
		Join();
    }
}

void Thread::Join()
{
    if(!m_joinable) {
    	throw ThreadAlreadyJoinedException();
    }
    int result = pthread_join(m_thread, 0);
    switch(result) {
    	case 0:
    		m_joinable = false;
    		break;
    	case EDEADLK:
    		throw ThreadJoiningEachOtherException();
    		break;
    	default:
    		assert(!"thread join failed");
    }
}

void Thread::Detach()
{
	if(!m_joinable) {
        throw ThreadAlreadyJoinedException();
    }
    int result = pthread_detach(m_thread);
	switch(result) {
    	case 0:
    		m_joinable = false;
    		break;
    	default:
    		assert(errno != EINVAL);
    		assert(!"thread join failed");
	}
}

void Thread::Cancel()
{
	if(!m_joinable) {
        throw ThreadAlreadyJoinedException();
    }
    int result = pthread_cancel(m_thread);
	switch(result) {
    	case 0:
    		void* exit;
    		result = pthread_join(m_thread, &exit);
    		if(result == 0 && exit == PTHREAD_CANCELED) {
    			return;
    		}
    		m_joinable = false;
    		break;
    	default:
    		assert(result != ESRCH);
    		assert(!"thread Cancel failed");
	}
}

bool Thread::operator==(const Thread& a_other) const
{
	return pthread_equal(m_thread, a_other.m_thread);
}

bool Thread::operator!=(const Thread& a_other) const
{
	return !(*this == a_other);
}

void Thread::Yield()
{
    int result = pthread_yield();
    assert(result == 0);
}

void Thread::SleepMicroSeconds(unsigned long a_microSeconds)
{
    usleep(a_microSeconds);
}

} //advcpp
