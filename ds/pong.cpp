#include<stdio.h>
#include<signal.h>
#include<sys/types.h>
#include<string.h> //memset
#include<unistd.h> //sleep

void SigHandle(int _sig, siginfo_t *_siginfo, void *_context) {    
    int pid = getpid();
    printf ("Sent from: %ld To: %d\n", (long)_siginfo->si_pid, pid);
    kill(_siginfo->si_pid, SIGUSR1);
}

int main(int srgc, const char* argv[]) {
	int pingPid;
	sscanf(argv[1],"%d",&pingPid);
	/*
    FILE* fp = fopen("pid.txt", "r");
    int pingPid;
    fscanf(fp, "%d", &pingPid);
    fclose(fp); 
	*/
    struct sigaction action = {0};
	//memset(&action, '\0', sizeof(action));
	action.sa_sigaction = &SigHandle;
	action.sa_flags = SA_SIGINFO;
 
	sigaction(SIGUSR1, &action, NULL);
    
    kill(pingPid, SIGUSR1);
	while (1) {
        sleep(1);
    }
 
	return 0;    
}
