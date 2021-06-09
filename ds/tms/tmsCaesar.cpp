#include "tmsCaesar.hpp"
#include <sstream>

namespace experis {

TmsCaesar ::TmsCaesar(int a_caesarNum)
: m_caesarNum(a_caesarNum){   
}

const String& TmsCaesar::Manipulate(String& _str) {
	for (size_t i = 0 ; i < _str.size() ; ++i){
        _str[i] = isupper(_str[i]) ? (_str[i] + m_caesarNum) > 'Z' ? (_str[i] + m_caesarNum)%'Z' + 'A' : _str[i] + m_caesarNum : _str[i];
        _str[i] = islower(_str[i]) ? (_str[i] + m_caesarNum) > 'z' ? (_str[i] + m_caesarNum)%'z' + 'a' : _str[i] + m_caesarNum : _str[i];
    }
    return _str;
}

}//experis
