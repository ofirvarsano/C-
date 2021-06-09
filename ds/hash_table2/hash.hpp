#ifndef _HASHTABLE_
#define _HASHTABLE_

#include <iostream>
#include "table.hpp"

namespace experis {

template<typename KeyT, typename ValueT>
class HashTable {
public:
    typedef HashIterator<KeyT, ValueT> Iterator;
    typedef Table<KeyT, ValueT> TableT;
    typedef size_t (*HashFunction)(const KeyT& _key);
    typedef std::vector<std::list< Item<KeyT, ValueT> > > Vec;
    
    HashTable(size_t a_size, HashFunction a_hashFunc);
    //~HashTable() = default;
    //HashTable(const HashTable&) = default;
    //HashTable& operator=(const HashTable&) = default;

    size_t NumItems() const { return m_table.NumItems(); }
    void Insert(const KeyT &a_key, ValueT &a_value); //throws std::invalid_argument exeption on duplicated keys
    ValueT Remove(const KeyT &a_key); //throws std::out_of_range exeption if key not found
    bool Exists(const KeyT &a_key) const;
    ValueT& Find(const KeyT &a_key) const; //throws std::out_of_range exeption if key not found
    
    Iterator Begin() const;
    Iterator End() const;

private:
    typename std::list<Item<KeyT, ValueT> >::const_iterator get(const KeyT &a_key) const;
    
	TableT m_table;
};

template<typename KeyT, typename ValueT>
HashTable<KeyT, ValueT>::HashTable(size_t a_size, HashFunction a_hashFunc)
: m_table(a_size, a_hashFunc) {
//: m_table(std::max(a_size, 1), a_hashFunc) {
    // TODO assert(a_size > 0);
}

template<typename KeyT, typename ValueT>
void HashTable<KeyT, ValueT>::Insert(const KeyT &a_key, ValueT &a_value) {
	try {
    	m_table.Insert(a_key, a_value);
    }
    catch(const std::invalid_argument& ex) {
    	throw;
    }
}

template<typename KeyT, typename ValueT>
ValueT HashTable<KeyT, ValueT>::Remove(const KeyT &a_key) {
	try {
    	m_table.Remove(a_key);
    }
    catch(const std::invalid_argument& ex) {
    	throw;
    }
}

template<typename KeyT, typename ValueT>
bool HashTable<KeyT, ValueT>::Exists(const KeyT &a_key) const {
	return m_table.Exists(a_key);
}

template<typename KeyT, typename ValueT>
ValueT& HashTable<KeyT, ValueT>::Find(const KeyT &a_key) const {
    try {
    	return m_table.Find(a_key);
    }
	catch(const std::out_of_range& ex) {
    	throw;
    }
}

template<typename KeyT, typename ValueT>
HashIterator<KeyT, ValueT> HashTable<KeyT, ValueT>::Begin() const {
    return m_table.Begin();
}

template<typename KeyT, typename ValueT>
HashIterator<KeyT, ValueT> HashTable<KeyT, ValueT>::End() const {
    return m_table.End();
}

} // experis

#endif //_HASHTABLE_
