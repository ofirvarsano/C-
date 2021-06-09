#include <stdio.h> 
#include <signal.h> 
#include <unistd.h> 
void SigintHandler(int a_sig) 
{ 
    printf("\n Ha Ha Ha Ha \n"); 
} 

int main() {
  signal(SIGINT, SigintHandler);
  int i = 0;

  for( ; ; ++ i ) {
    printf ("%d\n" ,i);
    sleep (1);
  }
  
  return 0;
}
