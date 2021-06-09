#include <iostream>
#include <stdio.h>
#include "thread.hpp"
#include "mu_test.h"
#include "../cpp/threads/mutex.hpp"

const size_t arraySize = 100;
double arr[arraySize];
experis::Mutex g_mutex;
const int LOOP_TIMES = 5000000;
int g = 0;

void* IncGlobalInLoop(void* a_ignored) {
    int i = 0;
    for ( ; i < LOOP_TIMES ; ++i) {
    	g_mutex.Lock();
        ++g;
        g_mutex.UnLock();
    }
    //fprintf(stderr, "g = %d\n", g);
    
    return NULL;
}

void* IncGlobalInLoopNoMutex(void* a_ignored) {
    int i = 0;
    for ( ; i < LOOP_TIMES ; ++i) {
        ++g;
    }
    //fprintf(stderr, "g = %d\n", g);
    
    return NULL;
}

void* FillOdd(void* a_ctx) {
    for(size_t i = 1; i < arraySize; i += 2) {
        arr[i] = i;
        std::cout << arr[i] << std::endl;
    }
    std::cout << "Finished Odd" << std::endl;
}

void* FillEven(void* a_ctx) {
    for(size_t i = 0; i < arraySize; i += 2) {
        arr[i] = i;
        std::cout << arr[i] << std::endl;
    }
    std::cout << "Finished Even" << std::endl;
}

UNIT(fill_array)
	try {
		advcpp::Thread t1(FillOdd); 
		advcpp::Thread t2(FillEven);
    	t1.Join();
    	t2.Join();
    }
	catch(const std::exception& ex) {
		std::cout << ex.what() << std::endl;
	}
END_UNIT

UNIT(inc_global_mutex)
	g = 0;
	try {
		advcpp::Thread t1(IncGlobalInLoop); 
		advcpp::Thread t2(IncGlobalInLoop);

    	t1.Join();
    	t2.Join();
    }
    catch(const std::exception& ex) {
		std::cout << ex.what() << std::endl;
	}
    ASSERT_THAT(g == LOOP_TIMES * 2);
END_UNIT

UNIT(inc_global_without_mutex)
	g = 0;
	try {
		advcpp::Thread t1(IncGlobalInLoopNoMutex); 
		advcpp::Thread t2(IncGlobalInLoopNoMutex);

    	t1.Join();
		t2.Join();
	}
	catch(const std::exception& ex) {
		std::cout << ex.what() << std::endl;
	}
    ASSERT_THAT(g != LOOP_TIMES * 2);
END_UNIT

TEST_SUITE(thread)
	IGNORE_TEST(fill_array)
	TEST(inc_global_mutex)
	TEST(inc_global_without_mutex)
END_SUITE
