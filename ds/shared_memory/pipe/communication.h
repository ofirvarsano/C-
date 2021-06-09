#ifndef __COMMUNICATION_H_
#define __COMMUNICATION_H_
#include <unistd.h>
namespace experis {

class Communication{
public:
    Communication():m_sum(0) {}
    ~Communication() {}
    
    void CreateTwoPipes();
    void Parent();
    void Child();

private:
    int m_ping[2];  // Used to store two ends of first pipe 
    int m_pong[2];  // Used to store two ends of second pipe 
    int m_sum;
};


} //experis



#endif //__COMMUNICATION_H_