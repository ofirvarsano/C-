#ifndef _ITEM_
#define _ITEM_

namespace experis {

template<typename KeyT, typename ValueT>
class Item {
public:
	Item(KeyT a_key, ValueT a_value) : m_key(a_key), m_value(a_value) {}
	//~Item() = default;
	//Item(const Item&) = default;
	//Item& operator=(const Item&) = default;

    bool operator==(const KeyT& a_key) const { return m_key == a_key; }
    
    const KeyT& GetKey() const { return m_key; }
    ValueT& GetValue() { return m_value; }
    const ValueT& GetValue() const { return m_value; }

private:
    const KeyT m_key; // CONCEPT of KeyT: operator==
    ValueT m_value;
};

} // experis

#endif // _ITEM_
