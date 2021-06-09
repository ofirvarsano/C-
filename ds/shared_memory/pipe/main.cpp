#include<stdio.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include "communication.h"
#include <stdexcept> //throw

#define LOOP 100

void Loop(size_t a_communicationNumber, pid_t a_pid, experis::Communication& a_communication){
    for(int index = 0; index < a_communicationNumber; ++index){
            // Parent process 
            if (a_pid > 0) { 
                a_communication.Parent();
            } 
            // child process 
            else{   
                a_communication.Child();
            } 
    } 
}

int main() { 
    experis::Communication pingPong;
    pingPong.CreateTwoPipes();
    pid_t p = fork(); 
    if (p < 0) { 
        throw std::runtime_error("Could not make fork"); 
    } 
    Loop(LOOP, p, pingPong);
}























 /*
     for(int i =0; i < 5; i++){
        switch(p){
        case 0:     //children process
        
        read(ping[0], &numFromFather, sizeof(int)); 
        sum += numFromFather;
        printf("number from parent %d\n", numFromFather); 
        write(pong[1], &sum, sizeof(int)); 
        if(i == 5){
              close(ping[0]);
              close(pong[1]);
        }
        break;
        default :   //parent process
         int randNum = rand() % 100;
        write(ping[1], &randNum, sizeof(int)); 
        read(pong[0], &randNum, sizeof(int)); 
        printf("number from child %d\n", randNum); 
            //read(pong[0], &entier_ping, sizeof(entier_ping));   //reading in pong
           // printf("I am father, I have received %ld - PING \n", entier_ping);
            //write(ping[1], &entier_ping, sizeof(entier_ping));  //writing in pong
            if(i == 5){
                close(ping[1]);
                close(pong[0]);
            }
        }
    }
    return 0;
}*/