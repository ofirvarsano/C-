#include "tmsFilter.hpp"
#include <sstream>

namespace experis {

TmsFilter ::TmsFilter(const wordsContainer& a_words)
: m_words(a_words)
{}

const String& TmsFilter::Manipulate(String& _str) {
	for (iter it = m_words.begin() ; it!=m_words.end(); ++it ){
		std::size_t wordFound = _str.find(*it);

		while(wordFound != String::npos) {
		    _str.replace(wordFound ,it->size(), it->size(), '*');
		    wordFound = _str.find(*it);
		}
	}
 	return _str;
}

}//experis     
