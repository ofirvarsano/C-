#ifndef _BITSET_INL_HPP_
#define _BITSET_INL_HPP_

#include "bitset.hpp"
#include "functors.hpp"

//namespace experis {

template<size_t NumBits>
Bitset<NumBits>::Bitset() 
: m_arr()
{}

template<size_t NumBits>
Bitset<NumBits>::Bitset(const Bitset& a_copyFrom) {
    std::copy(a_copyFrom.m_arr.begin(), a_copyFrom.m_arr.end(), m_arr.begin());
}

template<size_t NumBits>
const unsigned long Bitset<NumBits>::TurnOn(const size_t a_idx) {
    if (a_idx >= NumBits) {
        throw std::out_of_range("Bit index is out of range ");
    }
    size_t indexInArr = calcArrIndex(a_idx);
    size_t bitIdxInIdxArr = calcBitIndex(a_idx);
    m_arr[indexInArr] |= ONE_MASK << bitIdxInIdxArr;
    return m_arr[indexInArr];
}

template<size_t NumBits>
const unsigned long Bitset<NumBits>::TurnOff(const size_t a_idx) {
    if (a_idx >= NumBits) {
        throw std::out_of_range("Bit index is out of range ");
    }
    size_t indexInArr = calcArrIndex(a_idx);
    size_t bitIdxInIdxArr = calcBitIndex(a_idx);
    m_arr[indexInArr] &= ~(ONE_MASK << bitIdxInIdxArr);
    return m_arr[indexInArr];
}

template<size_t NumBits>
const unsigned long Bitset<NumBits>::Set(const size_t a_idx, const bool a_value) {
	if (a_idx >= NumBits) {
        throw std::out_of_range("Bit index is out of range ");
    }
    if (a_value) {
        return TurnOn(a_idx);
    }

    return TurnOff(a_idx);
}

template<size_t NumBits>
const unsigned long Bitset<NumBits>::Flip(const size_t a_idx) {
	if (a_idx >= NumBits) {
        throw std::out_of_range("Bit index is out of range ");
    }
    size_t indexInArr = calcArrIndex(a_idx);
    size_t bitIdxInIdxArr = calcBitIndex(a_idx);
 	m_arr[indexInArr] ^= (ONE_MASK << bitIdxInIdxArr);
	
    return m_arr[indexInArr];
}

template<size_t NumBits>
bool Bitset<NumBits>::IsOn(const size_t a_idx) const {
	if (a_idx >= NumBits) {
        return false;
    }
    size_t indexInArr = calcArrIndex(a_idx);
    size_t bitIdxInIdxArr = calcBitIndex(a_idx);
    unsigned long result = m_arr[indexInArr] & (ONE_MASK << bitIdxInIdxArr);
    return result;
}

template<size_t NumBits>
bool Bitset<NumBits>::AreAllOn() const {
    bool result = std::all_of(m_arr.begin() , m_arr.begin() + m_arr.size() - 1, FuncIsAllOn());
    unsigned int sum = 0;
    
	unsigned long numInIdx = *m_arr.rbegin();
	int range = NumBits % SIZE_BITS_OF_UL;
	while (numInIdx > 0) {
		if (range <= 0) { break; }
		sum += numInIdx & experis::ONE_MASK;
		numInIdx >>= 1;
		--range;
	}
	result = result && (NumBits % SIZE_BITS_OF_UL == sum);
    return result;
}

template<size_t NumBits>
bool Bitset<NumBits>::AreAllOff() const{
    bool result = std::all_of(m_arr.begin() , m_arr.begin() + m_arr.size() - 1, FuncIsAllOff());
    unsigned int sum = 0;
    
	unsigned long numInIdx = *m_arr.rbegin();
	int range = NumBits % SIZE_BITS_OF_UL;
	while (numInIdx > 0) {
		if (range <= 0) { break; }
		sum += numInIdx & experis::ONE_MASK;
		numInIdx >>= 1;
		--range;
	}

	result = result && (0 == sum);
    return result;
}

template<size_t NumBits>
const unsigned long Bitset<NumBits>::SizeInBits() const {
    return NumBits;
}

template<size_t NumBits>
void Bitset<NumBits>::Clear() {
    std::fill(m_arr.begin(), m_arr.end(), 0);
}

template<size_t NumBits>
void Bitset<NumBits>::Fill() {
    std::fill(m_arr.begin(), m_arr.end(), ~0ul);
}

template<size_t NumBits>
void Bitset<NumBits>::FlipAll() {
    std::for_each(m_arr.begin(), m_arr.end(), FilpAllBits());
    // transform
}

template<size_t NumBits>
Bitset<NumBits> Bitset<NumBits>::operator&(const Bitset& a_secondBitset) const {
    Bitset<NumBits> newBitset;
    std::transform(m_arr.begin(), m_arr.end(), a_secondBitset.m_arr.begin(), newBitset.GetArr().begin(), FirstAndSecond());
    return newBitset;
}

template<size_t NumBits>
bool Bitset<NumBits>::operator==(const Bitset& a_b2) const {
    return std::equal(m_arr.begin(), m_arr.end(), a_b2.m_arr.begin());
}

template<size_t NumBits>
bool Bitset<NumBits>::operator!=(const Bitset& a_b2) const {
    return !(*this == a_b2);
}

template<size_t NumBits>
Bitset<NumBits> Bitset<NumBits>::operator|(const Bitset& a_secondBitset) const { 
    experis::Bitset<NumBits> newBitset;
    std::transform(m_arr.begin(), m_arr.end(), a_secondBitset.m_arr.begin(), newBitset.m_arr.begin(), FirstOrSecond());
    return newBitset;
}   

template<size_t NumBits>
Bitset<NumBits> Bitset<NumBits>::operator^(const Bitset& a_secondBitset) const { 
    experis::Bitset<NumBits> newBitset;
    std::transform(m_arr.begin(), m_arr.end(), a_secondBitset.m_arr.begin(), newBitset.m_arr.begin(), FirstXOrSecond());
    return newBitset;
}

template<size_t NumBits>
Bitset<NumBits>& Bitset<NumBits>::operator&=(const Bitset& a_secondBitset) { 
    *this = *this & a_secondBitset;
    return *this;
}

template<size_t NumBits>
Bitset<NumBits>& Bitset<NumBits>::operator|=(const Bitset& a_secondBitset) { 
    *this = *this | a_secondBitset;
    return *this;
}

template<size_t NumBits>
Bitset<NumBits>& Bitset<NumBits>::operator^=(const Bitset& a_secondBitset) { 
    *this = *this ^ a_secondBitset;
    return *this;
}

template<size_t NumBits>
Bitset<NumBits>& Bitset<NumBits>::operator~() { 
    this->FlipAll();
    return *this;
}

template<size_t NumBits>
unsigned long Bitset<NumBits>::CountOnBits() const {
    FuncCountOnBits s = std::for_each(m_arr.begin() , m_arr.begin() + m_arr.size() - 1, FuncCountOnBits());

    unsigned int sum = 0;
    
	unsigned long numInIdx = *m_arr.rbegin();
	int range = NumBits % SIZE_BITS_OF_UL;
	while (numInIdx > 0) {
		if (range <= 0) { break; }
		sum += numInIdx & experis::ONE_MASK;
		numInIdx >>= 1;
		--range;
	}
	unsigned long result = s.sum + sum;
    return result;
}

template<size_t NumBits>
const size_t Bitset<NumBits>::calcArrIndex(const size_t a_idx) const {
    return a_idx / ((sizeof(unsigned long)) * __CHAR_BIT__);
}

template<size_t NumBits>
const size_t Bitset<NumBits>::calcBitIndex(const size_t a_idx) const {
    return a_idx % ((sizeof(unsigned long)) * __CHAR_BIT__);
}

template<size_t NumBits>
void Bitset<NumBits>::Print() const {
    std::array<unsigned long, ARR_SIZE> m_arrTemp(m_arr);
    int k = 0;
    int range = NumBits;

    if (ARR_SIZE == 0){
        k = -1;
    }
	
    for (k; k < ARR_SIZE; ++k) {
        for (int j = 0; j < SIZE_BYTES_OF_UL; ++j) {
       	if (range <= 0) { break; }
            for (int i = 0; i < __CHAR_BIT__; ++i) {
             	if (range <= 0) { break; }
                if ((m_arrTemp[k] & experis::ONE_MASK) == 0) {
                    std::cout << 0;
                }
                else {
                    std::cout << 1;
                }
                m_arrTemp[k] >>= 1;
                --range;
            }
            std::cout << " ";
        }
    }
    std::cout << std::endl;
}

template<size_t NumBits>
std::ostream& operator<<(std::ostream& os, const Bitset<NumBits>& a_bit) {
	int range = NumBits;
	std::array<unsigned long, a_bit.ARR_SIZE> m_arrTemp(a_bit.GetArr());
	
    for (int k = 0; k < a_bit.ARR_SIZE; ++k) {
		for (int j = 0; j < SIZE_BYTES_OF_UL; ++j) {
			if (range <= 0) { break; }
		    for (int i = 0; i < __CHAR_BIT__; ++i) {
		    	if (range <= 0) { break; }
		        if ((m_arrTemp[k] & experis::ONE_MASK) == 0) {
		            os << 0;
		        }
		        else {
		            os << 1;
		        }
		        m_arrTemp[k] >>= 1;
		        --range;
		    }
		    os << " ";
		}
	}
	return os;
}

template<size_t NumBits>
bool Bitset<NumBits>::operator[](const size_t a_idx) const {
    return IsOn(a_idx);
}
/*
template<size_t NumBits>
typename Bitset<NumBits>::BitReference Bitset<NumBits>::operator[](size_t a_idx) {
    Bitset<NumBits>::BitReference bit(IsOn(a_idx), m_arr[calcArrIndex(a_idx)], ((size_t)1 << calcBitIndex(a_idx)));
    return bit;
}

//class BitReference

template<size_t NumBits> 
Bitset<NumBits>::BitReference::BitReference(bool a_val, size_t& a_arr, size_t a_mask)
: m_bit(a_val)
, m_arrElem(a_arr)
, m_mask(a_mask) {
}

template<size_t NumBits> 
typename Bitset<NumBits>::BitReference& Bitset<NumBits>::BitReference::operator=(bool a_val) {
	if (m_bit != a_val) {
        m_arrElem ^= m_mask;
        m_bit = a_val;
    }
    return *this;
}

template<size_t NumBits>
std::ostream& operator<<(std::ostream& os, const Bitset<NumBits>::BitReference& a_bit) {
	os << a_bit.m_bit;
	return os;
}
*/
// namespace experis

#endif //_BITSET_INL_HPP
