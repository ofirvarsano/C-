#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

class Pipe {
public:
    Pipe();
    //~Pipe() = default;
    //Pipe(const Pipe&) = default;
    //Pipe& operator=(const Pipe&) = default;
    
    int Reading() const;
    int Writing() const;
    
private:
    int m_fd[2];
};

Pipe::Pipe()
: m_fd() {
    if (pipe(m_fd) < 0) {
        throw std::runtime_error("pipe failed");
    }
}

int Pipe::Reading() const {
	return m_fd[0];
}

int Pipe::Writing() const {
	return m_fd[1];
}

static void Ping(const Pipe& a_read, const Pipe &a_write) {
    close(a_read.Writing());
    close(a_write.Reading());
    
    srand(clock());
    int sum = 0;
    for ( ; ;) {
        int random = rand() % 100;
        write(a_write.Writing(), &random, sizeof(random));
        int buf;
    	while (read(a_read.Reading(), &buf, sizeof(buf)) <= 0) 
        	;
        sum += buf;
        std::cout << "Child sum: " << sum << std::endl;
        sleep(1);
    }
    
    close(a_read.Reading());
    close(a_write.Writing());
}

static void Pong(const Pipe& a_read, const Pipe& a_write) {
    close(a_read.Writing());
    close(a_write.Reading());

    for ( ; ;) {
        int recieve;
    	while (read(a_read.Reading(), &recieve, sizeof(recieve)) <= 0) 
        	;
        std::cout << "Parent num: " << recieve << std::endl;
        sleep(1);
        write(a_write.Writing(), &recieve, sizeof(recieve));
    }
    
    close(a_read.Reading());
    close(a_write.Writing());
}

int main() {
    Pipe Parent;
    Pipe Child;

    pid_t pid = fork();
    if (pid < 0) {
        throw std::runtime_error("fork failed"); 
    }

    if (0 == pid) {
        Pong(Parent, Child);
    }
    else {
        Ping(Child, Parent);
    }

    return 0;
}

