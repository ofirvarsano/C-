#ifndef __NAMEDPIPE_H_
#define __NAMEDPIPE_H_
#include <unistd.h>
#include <string>

namespace experis {

class NamedPipe{
public:
    NamedPipe(const char * a_path);
    ~NamedPipe() {}
    
    void CreatePipe();
    void Ping();
    void Pong();

private:
    std::string m_path;
    int m_sum;
};


} //experis



#endif //__NAMEDPIPE_H_
