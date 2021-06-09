#include "NamedPipe.hpp"
#include <sys/stat.h> 
#include <sys/types.h> 
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

namespace experis {

NamedPipe::NamedPipe(const char* a_path)
: m_path(a_path)
, m_sum(0)
{ }

void NamedPipe::CreatePipe() {
    mkfifo(m_path.c_str(), 0666);
}

void NamedPipe::Ping() {
    int random = rand() % 100;
    // write
    int fd = open(m_path.c_str(), O_WRONLY); 

    write(fd, &random, sizeof(int)); 
    close(fd); 

    fd = open(m_path.c_str(), O_RDONLY); 
    read(fd, &random, sizeof(int));
    
    printf("number from child %d\n", random);
    sleep(1); 
    close(fd); 
}

void NamedPipe::Pong() {
	int fd = open(m_path.c_str(), O_RDONLY); 
	int recieve;
	read(fd, &recieve, sizeof(int)); 
	m_sum += recieve;
	printf("number from parent %d\n", recieve);
	sleep(1);  
	close(fd); 

	fd = open(m_path.c_str(), O_WRONLY); 
	write(fd, &m_sum, sizeof(int));; 
	close(fd); 
}

} // experis

