#include <unistd.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <iostream>
#include <errno.h>
#include <time.h>
#include <signal.h>

int main(int argc, const char* argv[]) {
	// ftok to generate unique key 
    key_t key = ftok("write",65); 
  
    // shmget returns an identifier in shmid 
    int shmId = shmget(key,1023,0666|IPC_CREAT); 

	unsigned long* shmAdd = (unsigned long*)shmat(shmId, NULL,0);
    
    unsigned long lenArrNum = *shmAdd;
    char* arrStrBegin = (char*)(shmAdd + lenArrNum);
    char* ptr;

    for (int j = 1; j < lenArrNum; ++j) {
        unsigned long offset = *(shmAdd + j);
        
            ptr = (char*)(arrStrBegin + offset);
            while (*ptr != '\0') {
                std::cout << *ptr;
                ++ptr;    
            }
            std::cout<< std::endl;
            *(shmAdd + j) = 0;
    }

    //detach from shared memory  
    shmdt(shmAdd); 
    
    // destroy the shared memory 
    shmctl(shmId,IPC_RMID,NULL);
}
