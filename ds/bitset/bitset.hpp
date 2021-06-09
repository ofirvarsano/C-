#ifndef _BITSET_HPP_
#define _BITSET_HPP_

#include <stddef.h> //size_t
#include <algorithm>                         
#include <array>
#include <iostream>
#include <exception>

#define SIZE_BITS_OF_UL ((sizeof(unsigned long)) * (__CHAR_BIT__))
#define SIZE_BYTES_OF_UL ((sizeof(unsigned long)))

namespace experis{

template<size_t NumBits>
class Bitset {
public:
	static const unsigned long ONE_MASK = 1;
	class BitReference;
    Bitset();
    Bitset(const Bitset& a_copyFrom);
    //~Bitset() = default;
    //Bitset& operator=(const Bitset& a_otherBitset) = default;

    const unsigned long TurnOn(const size_t a_idx); // throws std::out_of_range on invalid index
    const unsigned long TurnOff(const size_t a_adx);  // throws std::out_of_range on invalid index
    const unsigned long Set(const size_t a_idx, const bool a_value);  // throws std::out_of_range on invalid index
    const unsigned long Flip(const size_t a_adx);  // throws std::out_of_range on invalid index
    bool IsOn(const size_t a_adx) const;  // returns false on invalid index

    bool AreAllOn() const;
    bool AreAllOff() const;
    unsigned long CountOnBits() const;
    
    const unsigned long SizeInBits() const;
    void Clear();
    void Fill();
    void FlipAll();
    void Print() const;
	
    Bitset operator&(const Bitset& a_secondBitset) const;
    Bitset operator|(const Bitset& a_secondBitset) const;
    Bitset operator^(const Bitset& a_secondBitset) const;

    Bitset& operator&=(const Bitset& a_secondBitset);
    Bitset& operator|=(const Bitset& a_secondBitset);
    Bitset& operator^=(const Bitset& a_secondBitset);
    Bitset& operator~();

    bool operator==(const Bitset& a_b2) const;
    bool operator!=(const Bitset& a_b2) const;
    bool operator[](const size_t a_idx) const;
    //Bitset::BitReference operator[](size_t a_idx);
    
	static const size_t ARR_SIZE = (NumBits / ((sizeof(unsigned long)) * __CHAR_BIT__)) + ((NumBits % ((sizeof(unsigned long)) * __CHAR_BIT__)) != 0);
	
    const std::array<unsigned long, ARR_SIZE>& GetArr() const { return m_arr; }
    std::array<unsigned long, ARR_SIZE>& GetArr() { return m_arr; }
    
    //static const std::array<size_t, SIZE_BITS_OF_UL * SIZE_BITS_OF_UL> lut;
    
	class BitReference {
	public:
		BitReference(bool a_val);
		BitReference &operator=(bool a_val);

	private:
		bool m_bit;
    };
private:
    const size_t calcArrIndex(const size_t a_idx) const;
    const size_t calcBitIndex(const size_t a_idx) const;

    std::array<unsigned long, ARR_SIZE> m_arr;
}; 

#include "bitset_inl.hpp"

template<size_t NumBits>
std::ostream& operator << (std::ostream& os, const Bitset<NumBits>& a_bit);

} // namespace experis


#endif //_BITSET_HPP_
