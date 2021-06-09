#ifndef _UNIQUE_KEY_LIST_
#define _UNIQUE_KEY_LIST_
#include <iostream>
#include <list>
#include "item.hpp"
#include <algorithm>

namespace experis {

template <typename KeyT, typename ValueT>
class UniqueKeyList {
public:
    typedef Item<KeyT, ValueT> ItemT;
	typedef bool (*KeyCompare)(const KeyT& ,const KeyT&);
    typedef typename std::list<ItemT>::const_iterator ListCIter;
    typedef typename std::list<ItemT>::iterator ListIter;

    //UniqueKeyList() = default;
    //~UniqueKeyList() = default;
    //UniqueKeyList(const UniqueKeyList&) = default;
    //UniqueKeyList& operator=(const UniqueKeyList&) = default;

	void Insert(const KeyT& a_key, ValueT& a_value); //throws std::invalid_argument exeption on duplicated keys
    ValueT Remove(const KeyT& a_key); //throws std::out_of_range exeption if key not found
    bool Exists(const KeyT& a_key) const;
    ValueT& Find(const KeyT& a_key) const; //throws std::out_of_range exeption if key not found
    
    ListCIter Begin() const { return m_uniqueList.begin(); }
    ListCIter End() const { return m_uniqueList.end(); }
    
    ListIter Begin() { return m_uniqueList.begin(); }
    ListIter End() { return m_uniqueList.end(); }

private:
	ListCIter get(const KeyT& a_key) const;

    std::list<ItemT> m_uniqueList;
};

template <typename KeyT, typename ValueT>
void UniqueKeyList<KeyT, ValueT>::Insert(const KeyT& a_key, ValueT& a_value) {
	ListCIter it = get(a_key);
	if(it != m_uniqueList.end()) {
		throw(std::invalid_argument("Duplicated Keys")) ;
	}
	m_uniqueList.push_back(ItemT(a_key, a_value));
}

template <typename KeyT, typename ValueT>
ValueT UniqueKeyList<KeyT, ValueT>::Remove(const KeyT& a_key) {
    ListCIter it = get(a_key);
	if(it == m_uniqueList.end()) {
		throw(std::out_of_range("Key not found"));
	}
	//ValueT removed = (const_cast<ItemT&>(*it)).GetValue();
	ValueT removed = it->GetValue();
	m_uniqueList.erase(it);
	return removed;
}

template <typename KeyT, typename ValueT>
ValueT& UniqueKeyList<KeyT, ValueT>::Find(const KeyT& a_key) const {
	ListCIter it = get(a_key);
	if(it == m_uniqueList.end()) {
		throw(std::out_of_range("Key not found"));
	}
	return (const_cast<ItemT&>(*it)).GetValue();
}

template <typename KeyT, typename ValueT>
bool UniqueKeyList<KeyT, ValueT>::Exists(const KeyT &a_key) const {
	return (get(a_key) != m_uniqueList.end());
}

template<typename KeyT, typename ValueT>
typename UniqueKeyList<KeyT, ValueT>::ListCIter UniqueKeyList<KeyT, ValueT>::get(const KeyT& a_key) const {
    return find(m_uniqueList.begin(), m_uniqueList.end(), a_key);
}

} // experis

#endif // _UNIQUE_KEY_LIST_
