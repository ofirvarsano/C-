#include "hash.hpp"
#include <stdio.h>

namespace experis {

HashTable::HashTable(size_t a_size, HashFunction a_hashFunc, KeyCompare a_compare)
: m_table(a_size), m_hashFunc(a_hashFunc), m_compare(a_compare), m_numItems(0)
{}

size_t HashTable::calcIndex(const KeyT& a_key) const {
    return m_hashFunc(a_key) % m_table.size();
}

void HashTable::Insert(const KeyT &a_key, ValueT &a_value) {
    size_t hashVal = calcIndex(a_key);
    std::list<Item>& iList = m_table[hashVal];
    
    for(std::list<Item>::const_iterator it = iList.begin(); it != iList.end() ; ++it) {
        if(m_compare(it->m_key, a_key)) {
    		throw(std::invalid_argument("Duplicated Keys")) ;
        }
    }

    iList.push_back(Item(a_key, a_value));
    ++m_numItems;
}

HashTable::ValueT HashTable::Remove(const KeyT &a_key) {
	size_t hashVal = calcIndex(a_key);
    std::list<Item>& iList = m_table[hashVal];
    
    for(std::list<Item>::iterator it = iList.begin(); it != iList.end() ; ++it) {
        if(m_compare(it->m_key, a_key)) {
            ValueT removed = it->m_value;
            iList.erase(it);
            --m_numItems;
            return removed;
        }
    }
    throw(std::out_of_range("Key not found"));
}

bool HashTable::Exists(const KeyT &a_key) const {
	try {
		Find(a_key);
		return true;
	}
	catch(std::out_of_range ex) {
		return false;
	}
}

HashTable::ValueT& HashTable::Find(const KeyT &a_key) const {
	size_t hashVal = calcIndex(a_key);
    const std::list<Item>& iList = m_table[hashVal];
    
    // std::list<Item>::iterator it = const_cast<std::list<Item>&>(m_table[hashVal]).begin();
    for(std::list<Item>::const_iterator it = iList.begin(); it != iList.end() ; ++it) {
        if(m_compare(it->m_key, a_key)) {
            return const_cast<ValueT&>(it->m_value);
        }
    }
    throw(std::out_of_range("Key not found"));
}

} // experis
