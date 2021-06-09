#include <unistd.h> //pipe
#include <stdio.h> //perroe
#include <stdlib.h> //perror
#include <time.h> //clock
#include <iostream>

class Pipe {
public:
    Pipe();
    //~Pipe() = default;
    
    int ReadingFd()const { return m_fd[0];}
    int WritingFd()const { return m_fd[1];} 
    
private:
    Pipe(const Pipe& a_other);
    Pipe& operator=(const Pipe& a_other);

    int m_fd[2];
};

Pipe::Pipe()
: m_fd() {
    if (pipe(m_fd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
}

static int ReadFromPipe(int a_readingFd) {
    int buf;
    while (read(a_readingFd, &buf, sizeof(buf)) <= 0) 
        ;
    return buf;    
}

static void WriteToPipe(int a_writingFd, int a_val) {
    write(a_writingFd, &a_val, sizeof(a_val));
}

static void Ping(const Pipe &a_reading, const Pipe &a_writing) {
    close(a_reading.WritingFd());
    close(a_writing.ReadingFd());
    
    srand(clock());
    int sum = 0;
    for ( ; ;) {
        int randomNum = rand() % 100;
        WriteToPipe(a_writing.WritingFd(), randomNum);
        sum += ReadFromPipe(a_reading.ReadingFd());
        std::cout << sum << std::endl;
        sleep(1);
    }
    
    close(a_reading.ReadingFd());
    close(a_writing.WritingFd());
}

static void Pong(const Pipe& a_reading, const Pipe& a_writing) {
    close(a_reading.WritingFd());
    close(a_writing.ReadingFd());

    for ( ; ;) {
        int recieved = ReadFromPipe(a_reading.ReadingFd());
        WriteToPipe(a_writing.WritingFd(), recieved);
    }
    
    close(a_reading.ReadingFd());
    close(a_writing.WritingFd());
}

int main() {
    Pipe ParentToChild;
    Pipe ChildToParent;

    pid_t pid = fork();
    if (-1 == pid) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (0 == pid) { //Child process
        Pong(ParentToChild, ChildToParent);
    }
    else {  //Parent process
        Ping(ChildToParent, ParentToChild);
    }

    return 0;
}

