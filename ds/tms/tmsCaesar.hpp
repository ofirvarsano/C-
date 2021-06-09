#ifndef TMS_CAESAR
#define TMS_CAESAR

#include "tms.hpp"
namespace experis {
class TmsCaesar : public Tms {
public:
    TmsCaesar(int a_caesarNum);
    //TmsCaesar(const TmsCaesar&) = default
    //TmsCaesar& operator=(const TmsCaesar&) = default
    //~TmsCaesar() = default

    virtual const std::string& Manipulate(std::string& _str);
private:
    int m_caesarNum;
};

}//experis  
#endif  