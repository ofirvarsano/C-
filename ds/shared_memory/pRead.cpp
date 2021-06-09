#include <unistd.h>
#include <climits>
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

int main() {

    key_t key = ftok("pWrite.o", 5888);
    if (key < 0) {
        assert(key < 0);
    }

    int shmId = shmget(key, 1024, 0666 | IPC_CREAT);
    if (shmId < 0) {
        assert(shmId < 0);
    }

    unsigned long* shmAdd = (unsigned long*)shmat(shmId, NULL,0);
    unsigned long lenArrNum = *shmAdd;

    int i = 1;
    while (status) {
        if (*(shmAdd + i) != 0 && i != 0) {
            std::cout << *(shmAdd + i) << std::endl;
            
            *(shmAdd + i) = 0;
        }
        
        i = (i + 1) % lenArrNum;
        signal(SIGINT, SigIntHandler);
        sleep(1);
    }
    
    std::cout << "received a signal" << std::endl;
    shmdt(shmAdd);
    shmctl(shmId, IPC_RMID, NULL);
}
