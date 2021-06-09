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

    key_t key = ftok(argv[1], 5888);
    if (key < 0) {
        assert(key < 0);
    }

    int shmId = shmget(key, 1023, 0666 | IPC_CREAT);
    if (shmId < 0) {
        assert(shmId < 0);
    }

    unsigned long* shmAdd = (unsigned long*)shmat(shmId, NULL,0);
    
    unsigned long lenArrNum = *shmAdd;
    char* arrStrBegin = (char*)(shmAdd +lenArrNum);
    char* ptr;

    while (status) {
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
        signal(SIGINT, SigIntHandler);
        sleep(1);
    }
    std::cout << "received a signal" << std::endl;
    shmdt(shmAdd);
    shmctl(shmId, IPC_RMID, NULL);

}
