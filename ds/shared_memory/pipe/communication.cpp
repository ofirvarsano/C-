#include "communication.h"
#include <unistd.h>
#include <cstdio>
#include <stdexcept> //throw
#include <stdlib.h>
namespace experis{

void Communication::CreateTwoPipes() {
    if (pipe(m_ping) == -1) { 
        throw std::runtime_error("Could not open pipe");
    } 
    if (pipe(m_pong)==-1) { 
        throw std::runtime_error("Could not open pipe");
    } 
}

void Communication::Parent() {
    int randNum = rand() % 100;
    write(m_ping[1], &randNum, sizeof(int)); 
    read(m_pong[0], &randNum, sizeof(int)); 
    printf("number from child %d\n", randNum); 
}

void Communication::Child() {
    int numFromFather;
    read(m_ping[0], &numFromFather, sizeof(int)); 
    m_sum += numFromFather;
    printf("number from parent %d\n", numFromFather);  
    write(m_pong[1], &m_sum, sizeof(int));  
}

}  // experis