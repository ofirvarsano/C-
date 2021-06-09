#ifndef TMS_FILTER
#define TMS_FILTER

#include "tms.hpp"
#include <vector>

namespace experis {
class TmsFilter : public Tms {
public:
    typedef std::vector<std::string> wordsContainer;
    TmsFilter(const wordsContainer& a_words);
    //TmsFilter(const TmsFilter&) = default
    //TmsFilter& operator=(const TmsFilter&) = default
    //~TmsFilter() = default

    virtual const String& Manipulate(String& _str);

private:

wordsContainer m_words;
typedef wordsContainer::iterator iter;

};    

}//experis
#endif
