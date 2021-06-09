#ifndef _HASH_ITERATOR_
#define _HASH_ITERATOR_

#include "UniqueKeyList.hpp"

namespace experis {

template<typename KeyT, typename ValueT>
class HashIterator {
private:
	typedef Item<KeyT, ValueT> ItemT;
    typedef std::vector<UniqueKeyList<KeyT, ValueT> > Vec;
    typedef typename Vec::const_iterator VectorCIter;
    typedef typename std::list<ItemT>::const_iterator ListCIter;
    //typedef typename std::list<ItemT>::iterator ListIter;

public:
    HashIterator(VectorCIter a_vecItr, VectorCIter a_vecEnd, VectorCIter a_vecBegin);
    //~HashIterator = default;
    //HashIterator(const HashIterator&) = default;
    //HashIterator& operator=(const HashIterator&) = default;

    HashIterator Next();
    HashIterator Prev();
    HashIterator operator++() { return Next(); }
    HashIterator operator--() { return Prev(); }
    HashIterator operator++(int) { return Next(); }
    HashIterator operator--(int) { return Prev(); }

    const ItemT& Get() const { return *m_listItr; }
    const ItemT& operator*() const { return Get(); }

    ValueT* operator->() const { return &operator*(); }
    bool operator==(const HashIterator& a_it) const;
    bool operator!=(const HashIterator& a_it) const;

private:
    VectorCIter m_vecItr;
    VectorCIter m_vecEnd;
    VectorCIter m_vecBegin;
    ListCIter m_listItr;
};

// TODO send size - 1 of vector
// for ( ; (a_index <= a_uklVec.size()) && a_uklVec.at(a_index).empty() ; ++a_index)
//    ;

template<typename KeyT, typename ValueT>
HashIterator<KeyT, ValueT>::HashIterator(VectorCIter a_vecItr, VectorCIter a_vecEnd, VectorCIter a_vecBegin) 
: m_vecItr(a_vecItr)
, m_vecEnd(a_vecEnd)
, m_vecBegin(a_vecBegin)
, m_listItr(a_vecItr->Begin()) {
    while(m_listItr == m_vecItr->End() && m_vecItr != m_vecEnd){
        m_vecItr ++;
        m_listItr = m_vecItr->Begin();
    }
}

template<typename KeyT, typename ValueT>
HashIterator<KeyT, ValueT> HashIterator<KeyT, ValueT>::Next() {
	if(m_vecItr != m_vecEnd) {
    	m_listItr++;
    }
    while(m_listItr == m_vecItr->End() && m_vecItr != m_vecEnd) {
		m_vecItr ++;
		m_listItr = m_vecItr->Begin();
    }
    return *this;
}

template<typename KeyT, typename ValueT>
HashIterator<KeyT, ValueT> HashIterator<KeyT, ValueT>::Prev() {
	if(m_vecItr == m_vecBegin && m_listItr == m_vecItr->Begin()) { // if already first element
		return *this;
	}
    if(m_listItr == m_vecItr->Begin()) {
        do{
            m_vecItr --;
            m_listItr = m_vecItr->End();
        }
        while(m_listItr == m_vecItr->Begin());
    }
    m_listItr--;
    return *this;
}

template<typename KeyT, typename ValueT>
bool HashIterator<KeyT, ValueT>::operator==(const HashIterator& a_it) const {
    return m_listItr == a_it.m_listItr; // TODO check m_index => same list
}

template<typename KeyT, typename ValueT>
bool HashIterator<KeyT, ValueT>::operator!=(const HashIterator& a_it) const {
    return !(*this == a_it);
}

} // experis

#endif // _HASH_ITERATOR_
