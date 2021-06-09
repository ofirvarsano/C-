#ifndef TMS_HPP
#define TMS_HPP

#include <string>
#include <fstream>

namespace experis {

typedef std::string  String;

class Tms{
public:
    //Tms() = default
    //~Tms() = default
    //Tms(const Tms&) = default
    //Tms& operator=(const Tms&) = default

    virtual const String& Manipulate(String& _str) = 0;
    String ManipulateFromFile(const String& _fileName);
};

}//experis

#endif //TMS_HPP

