#ifndef SEMAPHORE_EXCEPTIONS_HPP
#define SEMAPHORE_EXCEPTIONS_HPP

#include <exception>

namespace experis {

class SemaphoreOverFlow : public std::exception {
    virtual const char* what() const throw() {return "Semaphore overflow\n";}
};

class SemaphoreBlocked : public std::exception {
    virtual const char* what() const throw() {return "Semaphore is blocked\n";}
};

class SemaphoreTimedOut : public std::exception {
    virtual const char* what() const throw() {return "Semaphore timedout\n";}
};

} //experis

#endif //SEMAPHORE_EXCEPTIONS_HPP
