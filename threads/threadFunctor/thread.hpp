#ifndef THREAD_H
#define THREAD_H

#include <pthread.h>

namespace advcpp {

class Runnable {
public:
	virtual ~Runnable() { }
	//virtual void operator()() const = 0;
	virtual void Do() const = 0;
};

class Uncopyable {
protected:
	Uncopyable() {};
private:
	Uncopyable(Uncopyable const&); // no copy
};

class Thread : private Uncopyable {
public:
	//typedef void* (*actFunc)(void*);
	explicit Thread(Runnable& a_func);
    ~Thread();

    void Join();
    void Detach();
    
    void Cancel();
    
    bool operator==(const Thread& a_other) const;
    bool operator!=(const Thread& a_other) const;
    
public:
	static void SleepMicroSeconds(unsigned long a_microSeconds);
	static void Yield();
	
private:
	Thread(const Thread&); // no copy
	Thread& operator=(const Thread&); // no copy

private:	
	bool m_joinable;
	pthread_t m_thread;

private:
    static void* Start(void*);
};

} //advcpp

#endif // THREAD_H
