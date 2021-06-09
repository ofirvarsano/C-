#include <stdio.h>
#include <sys/ipc.h> //ftok
#include <sys/shm.h> //shared memory
#include <assert.h> //assert
#include <stdlib.h> //atoi
#include <string.h> //memset
#include <iostream> //cout
#include <unistd.h>
#include <signal.h>

/****************************************************************************************/
//Static Declarations
/****************************************************************************************/
static int InitShm(const char* a_path, int a_projId);
void signalHandler(int a_sig);
/****************************************************************************************/
//Main
/****************************************************************************************/
int main(int argc,char* argv[]) {
    signal(SIGINT, signalHandler); 
    
    int shmid = InitShm("../prog_1/prog_1.cpp", 126);
    size_t * ptr = (size_t*)shmat(shmid, (void*)0, 0);
    assert((size_t*)-1 != ptr);

    const size_t len = *ptr;
    for (size_t i = 1; ; i = (i % len) + 1) {
        while (0 == ptr[i]) 
            ;
        std::cout << ((char*)ptr + ptr[i]) << std::endl;
        *(ptr + i) = 0;
    }

    shmdt(ptr);
    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}
/****************************************************************************************/
//Static Functions
/****************************************************************************************/
static int InitShm(const char* a_path, int a_projId) {
    key_t key = ftok(a_path, a_projId);
    assert(-1 != key);

    int shmid = shmget(key, 0, 0666);
    assert(-1 != shmid);

    FILE* fp = fopen("shmId.txt", "w+");
    fprintf(fp, "%d", shmid);
    fclose(fp);

    return shmid;
}
/****************************************************************/
void signalHandler(int a_sig) {
    FILE* fp = fopen("shmId.txt", "r");
    int shmid;
    fscanf(fp, "%d", &shmid);
    fclose(fp);

    system("rm shmId.txt");

    shmctl(shmid,IPC_RMID,0);
    kill(getpid(), SIGKILL);
}