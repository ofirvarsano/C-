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

    //unsigned long lenArrNum = atol(argv[1]) + 1;

    size_t lenArrStr = argc - 1;
    std::string arrStr[lenArrStr];

    for (int i = 1; i < argc; ++i) {
        arrStr[i - 1] = argv[i];
    }
    
    // ftok to generate unique key
    key_t key = ftok("write", 65);
    if (key < 0) {
        assert(key < 0);
    }
	
	// shmget returns an identifier in shmid
    int shmId = shmget(key, 1023, 0666 | IPC_CREAT);
    if (shmId < 0) {
        assert(shmId < 0);
    }
	
	// shmat to attach to shared memory 
    unsigned long* shmAdd = (unsigned long*)shmat(shmId, NULL,0);
    
    /*fill the array of the nums with zero*/
    memset(shmAdd, 0, (lenArrStr + 1) * __CHAR_BIT__);
    *shmAdd = lenArrStr + 1;
    
    /*fill the strings in the shMem ?? */
    char* ptrShMemStr = (char*)(shmAdd + lenArrStr + 1);
    
    for (int i = 0; i < lenArrStr; ++i) {
        strcpy(ptrShMemStr, arrStr[i].c_str());
        ptrShMemStr += arrStr[i].size() + 1;
    }
    shmdt(shmAdd);
    //shmctl(shmId, IPC_RMID, NULL);
}
