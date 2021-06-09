#include <errno.h>
#include <assert.h>
#include <stdexcept>

#include "thread.hpp"
#include "thread_exceptions.hpp"

namespace advcpp {

Thread::Thread(actFunc a_action)
: m_joinable(true)
{
	if(!a_action) {
		throw std::runtime_error("NULL pointer");
	}
    int result = pthread_create(&m_thread, 0, a_action, 0);
    switch(result) {
    	case EINVAL:
    	case EPERM:
    		assert(!"pthread_create failed");
    		break;
    	case EAGAIN:
    		throw ThreadLackResourcesException();
    		break;
    }   
}

Thread::~Thread() {
	if(m_joinable) {
		Join();
    }
}

void Thread::Join() {
    if(!m_joinable) {
    	throw ThreadAlreadyJoinedException();
        assert(!"thread join failed");
    }
    int result = pthread_join(m_thread, 0);
    if(0 != result) {
        if(result == EDEADLK) {
            throw ThreadJoiningEachOtherException();
        }
        else {
            assert(!"thread join failed");
        }
    }
    m_joinable = false;
}

void Thread::Detach() {
	if(!m_joinable) {
        assert(!"thread detach failed");
    }
    int result = pthread_detach(m_thread);
    if(0 != result) {
        assert(errno != EINVAL);
    }
    m_joinable = false;
}

} //advcpp
