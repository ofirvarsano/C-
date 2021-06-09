#include "toLower.hpp"

namespace experis {

const String& ToLower::Manipulate(String& _str) {
    for (size_t i = 0 ; i < _str.size() ; ++i) {
    	_str[i] = tolower(_str[i]);
    }
	return _str;
}

}//experis    
