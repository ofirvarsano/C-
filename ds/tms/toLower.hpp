#ifndef TMS_LOWER
#define TMS_LOWER

#include "tms.hpp"
namespace experis {

class ToLower: public Tms {
public:
    //ToLower() = default
    //ToLower(const ToLower&) = default
    //ToLower& operator=(const ToLower&) = default
    //~ToLower() = default

    virtual const String& Manipulate(String& _str);
};

}//experis

#endif//TMS_LOWER
