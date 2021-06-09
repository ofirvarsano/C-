#ifndef THREAD
#define THREAD

#include <pthread.h>

namespace advcpp {

class Uncopyable {
protected:
	Uncopyable() {};
private:
	Uncopyable(Uncopyable const&); // no copy
};

class Thread : private Uncopyable {
public:
	typedef void* (*actFunc)(void*);
	explicit Thread(actFunc a_action);
    ~Thread();

    void Join();
    void Detach();

private:
	Thread(const Thread&); // no copy
	Thread& operator=(const Thread&); // no copy

private:	
	bool m_joinable;
	pthread_t m_thread;
};

} //advcpp

#endif // THREAD
