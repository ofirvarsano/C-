#include <stdio.h>
#include <iostream>
#include <thread>

#include "mutex.hpp"

typedef experis::Mutex Mutex;

int index;
enum { NUM_OF_THREADS = 4 };
int BEGIN = 10000000;
int END = 11000000;
int g_num = BEGIN;
int count = 0;

bool IsPrime(int a_num) {
	for (size_t i = 3; i * i <= a_num; i += 2) {
		if (a_num % i == 0) {
		    return false;
		}
	}
	return true;
}

void* PrintPrimes(void* a_mutex) {
	while(g_num < END) {
		static_cast<Mutex*>(a_mutex)->Lock();
		int number = g_num;
		g_num += 2;
		static_cast<Mutex*>(a_mutex)->UnLock();

		if(IsPrime(number)) {
			fprintf(stderr, "%d\n", number);
			
			static_cast<Mutex*>(a_mutex)->Lock();
			++count;
			static_cast<Mutex*>(a_mutex)->UnLock();
		}
    }
}

int main()
{
	int i, status;
	index = 0;
	pthread_t threads[NUM_OF_THREADS];
	
	//try {
	Mutex mutex;
	//}
	//catch() {
	
	//}
	
	if(BEGIN % 2 == 0) {
		++g_num;
	}
	
	for(i = 0; i < NUM_OF_THREADS; ++i)
	{
		status = pthread_create(&threads[i], NULL, &PrintPrimes, (void*)&mutex);
		if (status != 0) {
            throw std::bad_alloc();
        }
	}
	for(i = 0; i < NUM_OF_THREADS; ++i)
	{
		status = pthread_join(threads[i], NULL);
		if (status != 0) {
            throw std::bad_alloc();
        }
	}
	fprintf(stderr, "%d prime numbers\n", count);
	
	return(0);
}
