#ifndef _HASH_ITERATOR_
#define _HASH_ITERATOR_

#include "hash.hpp"

namespace experis {

template<typename KeyT, typename ValueT>
class HashIterator {
public:
	typedef typename std::list<Item<KeyT, ValueT> >::const_iterator list_citer_t;
    typedef typename std::vector<std::list< Item<KeyT, ValueT> > >::const_iterator vector_citer_t;
    
    HashIterator(vector_citer_t a_vecItr);
    //~HashIterator = default;
    //HashIterator(const HashIterator&) = default;
    //HashIterator& operator=(const HashIterator&) = default;

    HashIterator Next();
    HashIterator Prev();
    HashIterator operator++() { return Next(); }
    HashIterator operator--() { return Prev(); }

    const Item<KeyT, ValueT>& operator*() const { return *m_listItr; }

    bool operator==(const HashIterator& _it);
    bool operator!=(const HashIterator& _it);

private:
    vector_citer_t	m_vecItr;
    list_citer_t	m_listItr;
};

template<typename KeyT, typename ValueT>
HashIterator<KeyT, ValueT>::HashIterator(Vector_citer_t a_vecItr)
: m_vecItr(a_vecItr)
, m_listItr((*a_vecItr).begin())
{
	while(m_listItr == (*m_vecItr).end()) {
		m_vecItr ++;
		m_listItr = (*m_vecItr).begin();
	}
}

template<typename KeyT, typename ValueT>
HashIterator<KeyT, ValueT> HashIterator<KeyT, ValueT>::Next() {
    m_listItr++;
    if(m_listItr == (*m_vecItr).end() && m_vecItr != m_vecItr) {
        do {
            m_vecItr++;
            m_listItr = (*m_vecItr).begin();
        }
        while(m_listItr == (*m_vecItr).end());
    }
    return *this;
}

template<typename KeyT, typename ValueT>
HashIterator<KeyT, ValueT> HashIterator<KeyT, ValueT>::Prev() {
    if(m_listItr == (*m_vecItr).begin()) {
        do{
            m_vecItr --;
            m_listItr = (*m_vecItr).end();
        }
        while(m_listItr == (*m_vecItr).begin());
    }
    m_listItr--;
    return *this;
}

} //experis

#endif //_HASH_ITERATOR_
