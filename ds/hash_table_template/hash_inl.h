#ifndef _HASHINL_
#define _HASHINL_

#include "hash.hpp"
#include <stdio.h>
#include <algorithm>

namespace experis {

template<typename KeyT, typename ValueT>
HashTable<KeyT, ValueT>::HashTable(size_t a_size, HashFunction a_hashFunc, KeyCompare a_compare)
: vec(a_size), m_hashFunc(a_hashFunc), m_compare(a_compare), m_numItems(0)
{}

template<typename KeyT, typename ValueT>
size_t HashTable<KeyT, ValueT>::calcIndex(const KeyT& a_key) const {
    return m_hashFunc(a_key) % this->size();
}

template<typename KeyT, typename ValueT>
void HashTable<KeyT, ValueT>::Insert(const KeyT &a_key, ValueT &a_value) {
    size_t hashVal = calcIndex(a_key);
    std::list<Item<KeyT, ValueT> >& iList = (*this)[hashVal];
    
    for(typename std::list<Item<KeyT, ValueT> >::const_iterator it = iList.begin(); it != iList.end() ; ++it) {
        if(m_compare(it->m_key, a_key)) {
    		throw(std::invalid_argument("Duplicated Keys"));
        }
    }

    iList.push_back(Item<KeyT, ValueT>(a_key, a_value));
    ++m_numItems;
}

template<typename KeyT, typename ValueT>
ValueT HashTable<KeyT, ValueT>::Remove(const KeyT &a_key) {
	size_t hashVal = calcIndex(a_key);
    std::list<Item<KeyT, ValueT> >& iList = (*this)[hashVal];
    
    for(typename std::list<Item<KeyT, ValueT> >::iterator it = iList.begin(); it != iList.end() ; ++it) {
        if(m_compare(it->m_key, a_key)) {
            ValueT removed = it->m_value;
            iList.erase(it);
            --m_numItems;
            return removed;
        }
    }
    throw(std::out_of_range("Key not found"));
}

template<typename KeyT, typename ValueT>
bool HashTable<KeyT, ValueT>::Exists(const KeyT &a_key) const {
	size_t hashVal = calcIndex(a_key);
    const std::list<Item<KeyT, ValueT> >& iList = (*this)[hashVal];

    typename std::list<Item<KeyT, ValueT> >::const_iterator it = get(a_key);
    if(it == iList.end()) {
        return false;
    }
    return true;
}

template<typename KeyT, typename ValueT>
ValueT& HashTable<KeyT, ValueT>::Find(const KeyT &a_key) const {
    
	size_t hashVal = calcIndex(a_key);
    const std::list<Item<KeyT, ValueT> >& iList = (*this)[hashVal];

    typename std::list<Item<KeyT, ValueT> >::const_iterator it = get(a_key);
    if(it == iList.end()) {
        throw(std::out_of_range("Key not found"));
    }
    return const_cast<ValueT&>(it->m_value);
}

template<typename KeyT, typename ValueT>
typename std::list<Item<KeyT, ValueT> >::const_iterator HashTable<KeyT, ValueT>::get(const KeyT &a_key) const {
	size_t hashVal = calcIndex(a_key);
    const std::list<Item<KeyT, ValueT> >& iList = (*this)[hashVal];
    
    return find(iList.begin(), iList.end(), a_key);
}

template<typename KeyT, typename ValueT>
HashIterator<KeyT, ValueT> HashTable<KeyT, ValueT>::Begin() const {
    return HashIterator<KeyT, ValueT>(this->begin(), this->end());
}

template<typename KeyT, typename ValueT>
HashIterator<KeyT, ValueT> HashTable<KeyT, ValueT>::End() const {
    //return HashIterator<KeyT, ValueT>(this->end());
}

} // experis

#endif //_HASHINL_
