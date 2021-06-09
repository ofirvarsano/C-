#ifndef _HASHTABLE_
#define _HASHTABLE_

#include <iostream>
#include <vector>
#include <list>

namespace experis {

////////////////////////////////////////////////////////////////

template<typename KeyT, typename ValueT>
class Item {
public:
	Item(KeyT a_key, ValueT a_value) : m_key(a_key), m_value(a_value) {}
	//~Item() = default;
	//Item(const Item&) = default;
	//Item& operator=(const Item&) = default;

    bool operator==(const KeyT& a_key) const { return m_key == a_key; }

    const KeyT m_key;
    ValueT m_value;
}; // TODO in file item

////////////////////////////////////////////////////////////////

template<typename KeyT, typename ValueT>
class HashIterator {
public:
	typedef typename std::list<Item<KeyT, ValueT> >::const_iterator list_citer_t;
    typedef typename std::vector<std::list< Item<KeyT, ValueT> > >::const_iterator vector_citer_t;
    HashIterator(vector_citer_t a_vecItr, vector_citer_t a_vecEnd);
    //~HashIterator = default;
    //HashIterator(const HashIterator&) = default;
    //HashIterator& operator=(const HashIterator&) = default;

    HashIterator Next();
    HashIterator Prev();
    HashIterator operator++() { return Next(); }
    HashIterator operator--() { return Prev(); }

    const Item<KeyT, ValueT>& operator*() const { return *m_listItr; }

    bool operator!=(const HashIterator& a_it) const { return !(*this == a_it); }

private:
    vector_citer_t	m_vecItr;
    vector_citer_t	m_vecEnd;
    list_citer_t	m_listItr;
};  // TODO in file iterator

template<typename KeyT, typename ValueT>
HashIterator<KeyT, ValueT>::HashIterator(vector_citer_t a_vecItr, vector_citer_t a_vecEnd)
: m_vecItr(a_vecItr)
, m_vecEnd(a_vecEnd)
, m_listItr((*a_vecItr).begin())
{
	while(m_vecItr != m_vecEnd && m_listItr == (*m_vecItr).end()) {
		m_vecItr ++;
		if(m_vecItr != m_vecEnd) {
		m_listItr = (*m_vecItr).begin();
		}	
	}
}

template<typename KeyT, typename ValueT>
HashIterator<KeyT, ValueT> HashIterator<KeyT, ValueT>::Next() {
    m_listItr++;
    if(m_listItr == (*m_vecItr).end() && m_vecItr != m_vecEnd) {
        do {
            m_vecItr++;
            if(m_vecItr != m_vecEnd) {
            m_listItr = (*m_vecItr).begin();
            }
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

////////////////////////////////////////////////////////////////

template<typename KeyT, typename ValueT>
class HashTable : public std::vector<std::list< Item<KeyT, ValueT> > > {
public:
    //typedef std::string KeyT;
    //typedef long ValueT;
    typedef HashIterator<KeyT, ValueT> Iterator;
    // typedef HashIterator<Item<KeyT, ValueT> > Iterator;
    typedef size_t (*HashFunction)(const KeyT& _key);
    typedef bool (*KeyCompare)(const KeyT& ,const KeyT&);
    typedef std::vector<std::list< Item<KeyT, ValueT> > > vec;
    
    HashTable(size_t a_size, HashFunction a_hashFunc, KeyCompare a_compare);
    //~HashTable() = default;
    //HashTable(const HashTable&) = default;
    //HashTable& operator=(const HashTable&) = default;

    size_t NumItems() const { return m_numItems; }
    void Insert(const KeyT &a_key, ValueT &a_value); //throws std::invalid_argument exeption on duplicated keys
    ValueT Remove(const KeyT &a_key); //throws std::out_of_range exeption if key not found
    bool Exists(const KeyT &a_key) const;
    ValueT& Find(const KeyT &a_key) const; //throws std::out_of_range exeption if key not found
    
    Iterator Begin() const;
    Iterator End() const;

private:
	size_t calcIndex(const KeyT& a_key) const;
    typename std::list<Item<KeyT, ValueT> >::const_iterator get(const KeyT &a_key) const;
    HashFunction m_hashFunc;
    KeyCompare m_compare;
    size_t m_numItems;
};

} // experis

#include "hash_inl.h"

#endif //_HASHTABLE_

