#include <stdio.h>
#include <sys/ipc.h> //ftok
#include <sys/shm.h> //shared memory
#include <assert.h> //assert
#include <stdlib.h> //atoi
#include <string.h> //memset
#include <iostream> //cout
#include <unistd.h> //sysconf, getpid
#include <string>
#include <signal.h>

#define SIZE_OF(arr) ((sizeof(arr)) / (sizeof(arr[0]))) 

const size_t NUM_OF_STRS = 3;
/****************************************************************************************/
//Struct Defenition
/****************************************************************************************/
typedef struct Mem {
    size_t m_len;
    size_t m_size;
    std::string m_strings[NUM_OF_STRS];
    size_t m_offsets[NUM_OF_STRS];
} Mem;
/****************************************************************************************/
//Static Declarations
/****************************************************************************************/
static void InitMem(char *a_args[], Mem *a_mem);
static int InitShmPages(const char* a_path, int a_projId, size_t *a_numBytes);
static void InitPtr(size_t **a_ptr, Mem *a_mem);
static void FillArrWithPtrToStr(size_t **a_ptr, size_t a_offsets[], size_t a_offsetLen);
void signalHandler(int a_sig);
/****************************************************************************************/
//Main
/****************************************************************************************/
int main(int argc,char* argv[]) {
    assert(5 == argc);
    signal(SIGINT, signalHandler);  

    Mem mem = { (size_t)atol(argv[1]), (mem.m_len + 1) * sizeof(size_t) + 1 };
    InitMem(&argv[2], &mem);

    int shmid = InitShmPages("prog_1.cpp", 126, &mem.m_size);
    size_t * ptr = (size_t*)shmat(shmid, (void*)0, 0);
    if ((size_t*)-1 != ptr) {
        //perror
    }
    //assert((size_t*)-1 != ptr);

    InitPtr(&ptr, &mem);
    
    FillArrWithPtrToStr(&ptr, mem.m_offsets, NUM_OF_STRS);

    shmdt(ptr);
    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}
/****************************************************************************************/
//Static Functions
/****************************************************************************************/
static void InitMem(char *a_args[], Mem *a_mem) {
    for (size_t strIdx = 0; strIdx < SIZE_OF(a_mem->m_strings); ++strIdx) {
        a_mem->m_strings[strIdx] = a_args[strIdx];
        a_mem->m_offsets[strIdx] = a_mem->m_size;
        a_mem->m_size += a_mem->m_strings[strIdx].size() + 1;
    }
}
/****************************************************************/
static int InitShmPages(const char* a_path, int a_projId, size_t *a_numBytes) {
    key_t key = ftok(a_path, a_projId);
    assert(-1 != key);

    if (*a_numBytes <= sysconf(_SC_PAGE_SIZE)) {
        *a_numBytes = sysconf(_SC_PAGE_SIZE);
    }
    else {
        *a_numBytes = (*a_numBytes / sysconf(_SC_PAGE_SIZE)) * sysconf(_SC_PAGE_SIZE);
    }

    int shmid = shmget(key, *a_numBytes, 0666 | IPC_CREAT);
    std::cout << shmid << std::endl;
    assert(-1 != shmid);

    FILE* fp = fopen("shmId.txt", "w+");
    fprintf(fp, "%d", shmid);
    fclose(fp); 
    
    return shmid;
}
/****************************************************************/
static void InitPtr(size_t **a_ptr, Mem *a_mem) {
    memset(*a_ptr, 0, a_mem->m_size);
    **a_ptr = a_mem->m_len;
    for (size_t i = 0; i < SIZE_OF(a_mem->m_strings); ++i) {
        memcpy((char*)*a_ptr + a_mem->m_offsets[i], a_mem->m_strings[i].c_str(), a_mem->m_strings[i].size() + 1);
    }
}
/****************************************************************/
static void FillArrWithPtrToStr(size_t **a_ptr, size_t a_offsets[], size_t a_offsetLen) {
    srand(clock());

    for (size_t i = 1; ; i = (i % **a_ptr) + 1) {
        while (0 != *(*a_ptr + i))
            ;
        *(*a_ptr + i) = a_offsets[rand() % a_offsetLen];
    }
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