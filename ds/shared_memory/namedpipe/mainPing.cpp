#include "NamedPipe.hpp"
  
int main() { 
    experis::NamedPipe pipe("pipeN");
    pipe.CreatePipe();

    while (1) { 
        pipe.Ping();
    } 
    return 0; 
} 

