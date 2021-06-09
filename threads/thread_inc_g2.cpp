#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

#include "mutex.hpp"

enum { LOOP_TIMES = 100000 };
enum { NUM_OF_THREADS = 2 };
pthread_mutex_t lock;
int g = 0;

void* IncGlobalInLoop(void* a_mutex) {	
    int i = 0;
    for ( ; i < LOOP_TIMES ; ++i) {
    	(*(experis::Mutex*)a_mutex).Lock();
        ++g;
        (*(experis::Mutex*)a_mutex).UnLock();
    }

    fprintf(stderr, "i = %d\n", i);
    fprintf(stderr, "g = %d\n", g);
    
    pthread_exit(NULL);
}

int main()
{
	int i,status;
	pthread_t threads[NUM_OF_THREADS];
	
	//try {
	experis::Mutex mutex;
	//}
	//catch() {
	
	//}
	
	for(i = 0; i < NUM_OF_THREADS; ++i)
	{
		status = pthread_create(&threads[i], NULL, &IncGlobalInLoop, (void*)&mutex);
	}
	for(i = 0; i < NUM_OF_THREADS; ++i)
	{
		pthread_join(threads[i], NULL);
	}
	fprintf(stderr, "Exiting process\n");
	
	return(0);
}





