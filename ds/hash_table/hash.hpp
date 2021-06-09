#ifndef _HASHTABLE_
#define _HASHTABLE_

#include <iostream>
#include <vector>
#include <list>

namespace experis {

class HashTable {
public:
    typedef std::string KeyT;
    typedef long ValueT;

    typedef size_t (*HashFunction)(const KeyT& _key);
    typedef bool (*KeyCompare)(const KeyT& ,const KeyT&);

    HashTable(size_t a_size, HashFunction a_hashFunc, KeyCompare a_compare);
    //~HashTable() = default;
    //HashTable(const HashTable&) = default;
    //HashTable& operator=(const HashTable&) = default;

    size_t NumItems() const { return m_numItems; }
    void Insert(const KeyT &a_key, ValueT &a_value); //throws std::invalid_argument exeption on duplicated keys
    ValueT Remove(const KeyT &a_key); //throws std::out_of_range exeption if key not found
    bool Exists(const KeyT &a_key) const;
    ValueT& Find(const KeyT &a_key) const; //throws std::out_of_range exeption if key not found

private:
    class Item {
    public:
		Item(KeyT a_key, ValueT a_value) : m_key(a_key), m_value(a_value) {}
		//~Item() = default;
    	//Item(const Item&) = default;
    	//Item& operator=(const Item&) = default;

        KeyT m_key;
        ValueT m_value;
    };
	
    std::vector<std::list< Item > > m_table;
    size_t calcIndex(const KeyT& a_key) const;

    HashFunction m_hashFunc;
    KeyCompare m_compare;
    size_t m_numItems;
};

} // experis

#endif //_HASHTABLE_

