#ifndef _TABLE_
#define _TABLE_
#include <vector>
#include "UniqueKeyList.hpp"
#include "hash_iterator.hpp"

namespace experis {

template<typename KeyT, typename ValueT>
class Table : public std::vector<UniqueKeyList<KeyT, ValueT> > {
public:
	typedef size_t (*HashFunction)(const KeyT& _key);
	typedef std::vector<UniqueKeyList<KeyT, ValueT> > Vec;
	typedef typename std::vector<UniqueKeyList<KeyT, ValueT> >::iterator VecIter;
    typedef typename std::vector<UniqueKeyList<KeyT, ValueT> >::const_iterator VecCIter;
    
	Table(size_t a_size,  HashFunction a_hashFunc);
	//~Table() = default;
	//Table(const Table&) = default;
	//Table& operator=(const Table&) = default;
    
    size_t NumItems() const { return m_numItems; }
    void Insert(const KeyT& a_key, ValueT &a_value); //throws std::invalid_argument exeption on duplicated keys
    ValueT Remove(const KeyT& a_key); //throws std::out_of_range exeption if key not found
    bool Exists(const KeyT& a_key) const;
    ValueT& Find(const KeyT& a_key) const; //throws std::out_of_range exeption if key not found
    
    HashIterator<KeyT, ValueT> Begin() const;
    HashIterator<KeyT, ValueT> End() const;
    /*
    HashIterator<KeyT, ValueT> Begin();
    HashIterator<KeyT, ValueT> End();
	*/
private:
    size_t calcIndex(const KeyT& a_key) const;
	
    typename std::vector<UniqueKeyList<KeyT, ValueT> >::const_iterator get(const KeyT &a_key) const;
    
    HashFunction m_hashFunc;
    size_t m_numItems;
};

template<typename KeyT, typename ValueT>
Table<KeyT, ValueT>::Table(size_t a_size, HashFunction a_hashFunc)
: Vec(a_size)
, m_hashFunc(a_hashFunc)
, m_numItems(0)
{}

template<typename KeyT, typename ValueT>
size_t Table<KeyT, ValueT>::calcIndex(const KeyT& a_key) const {
    return m_hashFunc(a_key) % this->size();
}

template<typename KeyT, typename ValueT>
void Table<KeyT, ValueT>::Insert(const KeyT& a_key, ValueT& a_value) {
    size_t index = calcIndex(a_key);
    try {
    	(*this)[index].Insert(a_key, a_value);
    }
    catch(const std::invalid_argument& ex) {
    	throw;
    }
    ++m_numItems;
}

template<typename KeyT, typename ValueT>
ValueT Table<KeyT, ValueT>::Remove(const KeyT& a_key) {
	size_t index = calcIndex(a_key);
    UniqueKeyList<KeyT, ValueT>& idxList = (*this)[index];
    
    try {
    	ValueT removed = (*this)[index].Remove(a_key);
    	--m_numItems;
    	return removed;
    }
    catch(const std::invalid_argument& ex) {
    	throw;
    }
}

template<typename KeyT, typename ValueT>
bool Table<KeyT, ValueT>::Exists(const KeyT& a_key) const {
	size_t index = calcIndex(a_key);
    UniqueKeyList<KeyT, ValueT> idxList = (*this)[index];
	return idxList.Exists(a_key);
}

template<typename KeyT, typename ValueT>
ValueT& Table<KeyT, ValueT>::Find(const KeyT& a_key) const {
	size_t index = calcIndex(a_key);
    UniqueKeyList<KeyT, ValueT> idxList = (*this)[index];
	
	try {
		return idxList.Find(a_key);
	}
	catch(const std::out_of_range& ex) {
		throw;
	}
}

template<typename KeyT, typename ValueT>
HashIterator<KeyT, ValueT> Table<KeyT, ValueT>::Begin() const {
    return HashIterator<KeyT, ValueT>(this->begin(), this->end(), this->begin());
}


template<typename KeyT, typename ValueT>
HashIterator<KeyT, ValueT> Table<KeyT, ValueT>::End() const {
    return HashIterator<KeyT, ValueT>(this->end(), this->end(), this->begin());
}
/*
template<typename KeyT, typename ValueT>
HashIterator<KeyT, ValueT> Table<KeyT, ValueT>::Begin() {
    return HashIterator<KeyT, ValueT>(this->begin());
}

template<typename KeyT, typename ValueT>
HashIterator<KeyT, ValueT> Table<KeyT, ValueT>::End() {
    return HashIterator<KeyT, ValueT>(this->end());
}
*/

} // experis

#endif // _TABLE_
