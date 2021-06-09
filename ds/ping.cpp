#include<stdio.h>
#include <iostream>
#include<signal.h>
#include<string.h> //memset
#include<unistd.h> //sleep

void SigHandle(int _sig, siginfo_t *_siginfo, void *_context) {   
    int pid = getpid();
    printf ("Sent from: %ld To: %d\n", (long)_siginfo->si_pid, pid);
    sleep(1);
    kill(_siginfo->si_pid, SIGUSR1);        
}

int main() {
    /*FILE* fp = fopen("pid.txt", "w");
    int pid = getpid();
    fprintf(fp, "%d", pid);
    fclose(fp);
	*/
	
	int pid = getpid();
	std::cout << pid << std::endl;
    
    struct sigaction action = {0};
	//memset(&action, '\0', sizeof(action));
	action.sa_sigaction = &SigHandle;
	action.sa_flags = SA_SIGINFO;
 
	sigaction(SIGUSR1, &action, NULL);
 
	while (1) {
		sleep(1);
    }
 
	return 0;
}
