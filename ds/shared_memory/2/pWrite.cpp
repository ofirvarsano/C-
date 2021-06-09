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

bool status = true;

void SigIntHandler(int a_signal) {
    if (a_signal == SIGINT) {
        status = false;
    }
}

int main(int argc, const char* argv[]) {

    unsigned long lenArrNum = atol(argv[1]) + 1;

    size_t lenArrStr = argc - 2;
    std::string arrStr[lenArrStr];

    for (int f = 2; f < argc; ++f) {
        arrStr[f -2] = argv[f];
    }
    
    key_t key = ftok("pWrite.o", 5888);
    if (key < 0) {
        assert(key < 0);
    }

    int shmId = shmget(key, 1023, 0666 | IPC_CREAT);
    if (shmId < 0) {
        assert(shmId < 0);
    }

    unsigned long* shmAdd = (unsigned long*)shmat(shmId, NULL,0);
    
    /*fill the array of the nums with zero*/
    memset(shmAdd, 0, lenArrNum * __CHAR_BIT__);
    *shmAdd = lenArrNum;
    
    /*fill the strings in the shMem*/
    char* ptrShMemStr = (char*)(shmAdd + lenArrNum);
    
    for (int i = 0; i < lenArrStr; ++i) {
        strcpy(ptrShMemStr, arrStr[i].c_str());
        ptrShMemStr += arrStr[i].size() + 1;
    }

    /*fill array of offsets of the strings from the shmAdd*/
    unsigned long offsetsArr[lenArrStr];
    offsetsArr[0] = 0;
    for (int i = 1; i < lenArrStr; ++i) {
        offsetsArr[i] = offsetsArr[i - 1] + arrStr[i - 1].size() + 1;
    }

    /*fill the array of nums with random numbers*/
    srand(clock());

    while (status) {
        for (int j = 1; j < lenArrNum; ++j) {
            
            unsigned long num = rand()%3;
            *(shmAdd + j) = offsetsArr[num];
            
        }
        signal(SIGINT, SigIntHandler);
        sleep(1);
    }
    std::cout << "received a signal" << std::endl;
    shmdt(shmAdd);
    shmctl(shmId, IPC_RMID, NULL);
}
