#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

enum { LOOP_TIMES = 100000000 };
enum { NUM_OF_THREADS = 2 };
pthread_mutex_t lock;
int g = 0;

void* IncGlobalInLoop(void* a_ignored) {	
    int i = 0;
    for ( ; i < LOOP_TIMES ; ++i) {
    	pthread_mutex_lock(&lock);
        ++g;
        pthread_mutex_unlock(&lock);
    }

    fprintf(stderr, "i = %d\n", i);
    fprintf(stderr, "g = %d\n", g);
    printf("thread num: %d\n\n", (int)a_ignored); 
    
    pthread_exit(NULL);
}

int main()
{
	int i,status;
	pthread_t threads[NUM_OF_THREADS];
	
	if(pthread_mutex_init(&lock, NULL) != 0) {
		return 1;
	}
	
	for(i = 0; i < NUM_OF_THREADS; ++i)
	{
		status = pthread_create(&threads[i], NULL, &IncGlobalInLoop, (void*)i);
	}
	for(i = 0; i < NUM_OF_THREADS; ++i)
	{
		pthread_join(threads[i], NULL);
	}
	
	pthread_mutex_destroy(&lock);
	fprintf(stderr, "Exiting process\n");
	
	return(0);
}





